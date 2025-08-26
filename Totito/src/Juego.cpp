#include "Juego.h"
#include <iostream>
using namespace std;

Juego::Juego(Configuracion* config) : config(config), tablero(nullptr), gestor(nullptr) {}

Juego::~Juego() {
    delete tablero;
    delete gestor;
}

// función auxiliar: convierte "A0" a fila y columna
static bool parseCoordenada(const string& coord, int& fila, int& col) {
    if (coord.size() < 2) return false;
    col = coord[0] - 'A';  // letra → columna
    try {
        fila = stoi(coord.substr(1)); // número → fila
    } catch (...) {
        return false;
    }
    return true;
}

void Juego::inicializar() {
    // crear tablero
    tablero = new Tablero(config->getFilas(), config->getColumnas());
    gestor = new GestorLineas(tablero->getLineas(), tablero);

    // cargar jugadores en la cola
    for (int i = 0; i < config->getCantidadJugadores(); i++) {
        colaTurnos.encolar(config->getJugador(i));
    }
}

void Juego::jugar() {
    bool continuar = true;

    while (continuar) {
        system("clear");
        tablero->debugCeldas();
        tablero->imprimir();
        config->mostrarJugadores();

        // Mostrar todas las líneas antes del turno
        std::cout << "\n=== DEBUG: Líneas actuales ===\n";
        gestor->mostrarLineas();
        std::cout << "==============================\n";

        Jugador* jugadorActual = colaTurnos.desencolar();
        if (!jugadorActual) break;

        std::cout << "\nTurno de: " << jugadorActual->getNombre() 
                  << " (" << jugadorActual->getInicial() << ")\n";

        std::string entrada1, entrada2;
        std::cout << "Ingrese primera coordenada (ej: A0 o 'salir'): ";
        std::cin >> entrada1;
        if (entrada1 == "salir") break;

        std::cout << "Ingrese segunda coordenada (ej: A1): ";
        std::cin >> entrada2;
        if (entrada2 == "salir") break;

        int f1, c1, f2, c2;
        if (parseCoordenada(entrada1, f1, c1) && parseCoordenada(entrada2, f2, c2)) {
            gestor->colocarLinea(f1, c1, f2, c2, jugadorActual);

            //para ver el estado actual de las celdas
            std::cout << " \n=== debug del estado de las celdas tras cada jugada ==\n";
            tablero->debugCeldas();
            std::cout << "====================================================\n";
        } else {
            std::cout << "Coordenadas inválidas.\n";
        }

        // Mostrar todas las líneas después del turno
        std::cout << "\n=== DEBUG: Líneas después del turno ===\n";
        gestor->mostrarLineas();
        std::cout << "=======================================\n";

        colaTurnos.encolar(jugadorActual);
    }

    std::cout << "\nJuego terminado.\n";
}


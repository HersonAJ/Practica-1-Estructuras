#include "Juego.h"
#include <iostream>
#include "Utilidades.h"
#include <limits>
#include "CondicionesDeVictoria/EvaludadorCondiciones.h"
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
        limpiarPantalla(); 

        // Mostrar estado actual
        tablero->imprimir();
        config->mostrarJugadores();

        if (colaTurnos.esVacio()) {
            std::cout << "No hay más jugadores.\n";
            break;
        }

        // Sacamos al jugador actual
        Jugador* jugadorActual = colaTurnos.desencolar();

        std::cout << "\nTurno de: " << jugadorActual->getNombre()
                  << " (" << jugadorActual->getInicial() << ")\n";

        jugadorActual->mostrarPowerUps();

        std::string entrada1, entrada2;
        std::cout << "Ingrese primera coordenada (ej: A0 o 'salir'): ";
        std::cin >> entrada1;
        if (entrada1 == "salir") break;

        std::cout << "Ingrese segunda coordenada (ej: A1): ";
        std::cin >> entrada2;
        if (entrada2 == "salir") break;

        int f1, c1, f2, c2;
        if (!parseCoordenada(entrada1, f1, c1) || !parseCoordenada(entrada2, f2, c2)) {
            std::cout << "Coordenadas inválidas.\n";
            std::cout << "Presione Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            colaTurnos.encolar(jugadorActual); // turno pasa al siguiente
            continue;
        }

        // Intentar colocar la línea
        if (!gestor->colocarLinea(f1, c1, f2, c2, jugadorActual)) {
            // Mensaje ya mostrado dentro de colocarLinea
            std::cout << "Presione Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            colaTurnos.encolar(jugadorActual); // turno pasa al siguiente
            continue;
        }

        // Jugada válida → turno pasa al siguiente
        colaTurnos.encolar(jugadorActual);

        // Validar si ya no quedan líneas libres
        if (gestor->todasLasLineasColocadas()) {
            limpiarPantalla();
            tablero->imprimir();
            config->mostrarJugadores();
            std::cout << "\nTodas las líneas han sido colocadas. ¡Fin del juego!\n";
            break;
        }
    }

        std::cout << "\nJuego terminado.\n";

        // Evaluar condiciones de victoria
        Jugador* ganador = evaluarGanador(tablero, *config->getListaJugadores());

        std::cout << "\nResultado final:\n";
        if (ganador != nullptr) {
            std::cout << "\nGanador: " << ganador->getNombre()
                    << " (" << ganador->getInicial() << ") con "
                    << ganador->getPuntos() << " puntos.\n";
        } else {
            std::cout << "\nEmpate técnico: no se pudo determinar un ganador.\n";
        }

}

#include "Juego.h"
#include <iostream>
#include "Utilidades.h"
#include <limits>
#include "CondicionesDeVictoria/EvaludadorCondiciones.h"
#include "Tablero.h" 
using namespace std;

Juego::Juego(Configuracion* config) : config(config), tablero(nullptr), gestor(nullptr) {}

Juego::~Juego() {
    delete tablero;
    delete gestor;
}

bool Juego::parseCoordenada(const string& coord, int& fila, int& col) {
    if (coord.size() < 2) return false;
    col = coord[0] - 'A';
    try {
        fila = stoi(coord.substr(1));
    } catch (...) {
        return false;
    }
    return true;
}

void Juego::inicializar() {
    tablero = new Tablero(config->getFilas(), config->getColumnas());
    gestor = new GestorLineas(tablero->getLineas(), tablero);

    for (int i = 0; i < config->getCantidadJugadores(); i++) {
        colaTurnos.encolar(config->getJugador(i));
    }
}

void Juego::devolverTurno(Jugador* jugador) {
    colaTurnos.encolarFrente(jugador);
}

void Juego::jugar() {
    bool continuar = true;
    bool seUsoPowerUp = false;

    while (continuar) {
        limpiarPantalla(); 
        tablero->imprimir();
        config->mostrarJugadores();

        if (colaTurnos.esVacio()) {
            cout << "No hay más jugadores.\n";
            break;
        }

        Jugador* jugadorActual = colaTurnos.desencolar();

        cout << "\nTurno de: " << jugadorActual->getNombre() << " (" << jugadorActual->getInicial() << ")\n";
        jugadorActual->mostrarPowerUps();

        string respuesta;
        if (!jugadorActual->tienePowerUps()) {
            respuesta = "no";
        } else {
            cout << "¿Desea usar un PowerUp? (si/no): ";
            cin >> respuesta;
        }

        seUsoPowerUp = false;
        if (respuesta == "si") {
            seUsoPowerUp = true;
            PowerUp* powerUpUsado = jugadorActual->usarPowerUp();

            cout << "\n¡Has usado el PowerUp " << powerUpUsado->getSimbolo() << "!\n";
            
            // Llamada polimórfica: el PowerUp se aplica a sí mismo.
            powerUpUsado->aplicarEfecto(this, jugadorActual);
            
            delete powerUpUsado;

            limpiarPantalla();
            tablero->imprimir();
            config->mostrarJugadores();
            
            cout << "Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

        string entrada1, entrada2;
        cout << "Ingrese primera coordenada (ej: A0 o 'salir'): ";
        cin >> entrada1;
        if (entrada1 == "salir") break;

        cout << "Ingrese segunda coordenada (ej: A1): ";
        cin >> entrada2;
        if (entrada2 == "salir") break;

        int f1, c1, f2, c2;
        if (!parseCoordenada(entrada1, f1, c1) || !parseCoordenada(entrada2, f2, c2)) {
            cout << "Coordenadas inválidas.\n";
            cout << "Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            colaTurnos.encolar(jugadorActual);
            continue;
        }

        if (!gestor->colocarLinea(f1, c1, f2, c2, jugadorActual)) {
            cout << "Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            colaTurnos.encolar(jugadorActual);
            continue;
        }

        if (!seUsoPowerUp) {
            colaTurnos.encolar(jugadorActual);
        }

        if (gestor->todasLasLineasColocadas()) {
            limpiarPantalla();
            tablero->imprimir();
            config->mostrarJugadores();
            cout << "\nTodas las líneas han sido colocadas. ¡Fin del juego!\n";
            break;
        }
    }

    cout << "\nJuego terminado.\n";
    Jugador* ganador = evaluarGanador(tablero, *config->getListaJugadores());

    cout << "\nResultado final:\n";
    if (ganador != nullptr) {
        cout << "\nGanador: " << ganador->getNombre() << " (" << ganador->getInicial() << ") con " << ganador->getPuntos() << " puntos.\n";
    } else {
        cout << "\nEmpate técnico: no se pudo determinar un ganador.\n";
    }
}

int Juego::getFilas() const {
    return tablero->getFilas();
}

int Juego::getColumnas() const {
    return tablero->getColumnas();
}

bool Juego::estaEnBorde(int fila, int columna) const {
    return (fila == 0 || fila == tablero->getFilas() - 1 || columna == 0 || columna == tablero->getColumnas() - 1);
}

void Juego::expandirAbajo() {
    tablero->expandirAbajo();
}

void Juego::expandirDerecha() {
    tablero->expandirDerecha();
}
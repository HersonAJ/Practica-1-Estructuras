#include "Configuracion.h"

Configuracion::Configuracion() : filas(0), columnas(0), cantidadJugadores(0) {
    for (int i = 0; i < MAX_JUGADORES; i++) {
        jugadores[i] = nullptr;
    }
}

Configuracion::~Configuracion() {
    for (int i = 0; i < cantidadJugadores; i++) {
        delete jugadores[i];
    }
}

void Configuracion::pedirDatos() {
    do {
        std::cout << "Ingrese cantidad de puntos de FILAS (min 3): ";
        std::cin >> filas;
    } while (filas < 3);

    do {
        std::cout << "Ingrese cantidad de puntos de COLUMNAS (min 3): ";
        std::cin >> columnas;
    } while (columnas < 3);
}

void Configuracion::pedirJugadores() {
    do {
        std::cout << "Ingrese número de jugadores (1-" << MAX_JUGADORES << "): ";
        std::cin >> cantidadJugadores;
    } while (cantidadJugadores < 1 || cantidadJugadores > MAX_JUGADORES);

    std::cin.ignore(); // limpiar buffer

    for (int i = 0; i < cantidadJugadores; i++) {
        std::string nombre;
        std::cout << "Nombre del jugador " << (i+1) << ": ";
        std::getline(std::cin, nombre);
        jugadores[i] = new Jugador(nombre);
    }
}

void Configuracion::mostrarJugadores() const {
    std::cout << "\n=== Jugadores ===\n";
    for (int i = 0; i < cantidadJugadores; i++) {
        std::cout << jugadores[i]->getInicial() 
                  << " - " << jugadores[i]->getNombre()
                  << " (Puntos: " << jugadores[i]->getPuntos() << ")\n";
    }
}

int Configuracion::getFilas() const { return filas; }
int Configuracion::getColumnas() const { return columnas; }
int Configuracion::getCantidadJugadores() const { return cantidadJugadores; }
Jugador* Configuracion::getJugador(int i) const { return jugadores[i]; }

#include "Configuracion.h"

Configuracion::Configuracion()
    : filas(0), columnas(0), inicio(nullptr), cantidadJugadores(0) {
    for (int i = 0; i < MAX_JUGADORES; ++i) {
        jugadores[i] = nullptr;
    }
}

Configuracion::~Configuracion() {
    liberarMemoria();
    // Liberar jugadores
    for (int i = 0; i < cantidadJugadores; ++i) {
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

    pedirJugadores(); // ← nueva llamada
}

void Configuracion::pedirJugadores() {
    do {
        std::cout << "Ingrese cantidad de jugadores (1 a " << MAX_JUGADORES << "): ";
        std::cin >> cantidadJugadores;
    } while (cantidadJugadores < 1 || cantidadJugadores > MAX_JUGADORES);

    std::cin.ignore(); // Limpiar buffer

    for (int i = 0; i < cantidadJugadores; ++i) {
        std::string nombre;
        std::cout << "Nombre del jugador " << (i + 1) << ": ";
        std::getline(std::cin, nombre);

        jugadores[i] = new Jugador(nombre);
    }
}

void Configuracion::construirTablero() {
    inicio = nullptr;
    Punto* filaAnterior = nullptr;

    for (int i = 0; i < filas; i++) {
        Punto* filaActual = nullptr;
        Punto* anterior = nullptr;
        Punto* arriba = filaAnterior;

        for (int j = 0; j < columnas; j++) {
            Punto* nuevo = new Punto(i, j);

            if (i == 0 && j == 0) {
                inicio = nuevo;
            }

            if (anterior != nullptr) {
                anterior->setRight(nuevo);
                nuevo->setLeft(anterior);
            }
            anterior = nuevo;

            if (arriba != nullptr) {
                arriba->setDown(nuevo);
                nuevo->setUp(arriba);
                arriba = arriba->getRight();
            }

            if (j == 0) {
                filaActual = nuevo;
            }
        }
        filaAnterior = filaActual;
    }
}

void Configuracion::mostrarTableroVacio() const {
    std::cout << "\nTABLERO VACIO (Listas enlazadas):\n";
    Punto* fila = inicio;
    while (fila != nullptr) {
        Punto* actual = fila;
        while (actual != nullptr) {
            std::cout << actual->toString();
            if (actual->getRight() != nullptr) std::cout << "   ";
            actual = actual->getRight();
        }
        std::cout << "\n\n";
        fila = fila->getDown();
    }

    mostrarJugadores(); // ← nueva llamada
}

void Configuracion::mostrarJugadores() const {
    std::cout << "\nJUGADORES:\n";
    for (int i = 0; i < cantidadJugadores; ++i) {
        const Jugador* j = jugadores[i];
        std::cout << "Jugador " << (i + 1) << ": "
                  << j->getNombre() << " ("
                  << j->getInicial() << ") - "
                  << j->getPuntos() << " puntos\n";
    }
}

void Configuracion::liberarMemoria() {
    Punto* fila = inicio;
    while (fila != nullptr) {
        Punto* actual = fila;
        fila = fila->getDown();
        while (actual != nullptr) {
            Punto* siguiente = actual->getRight();
            delete actual;
            actual = siguiente;
        }
    }
    inicio = nullptr;
}

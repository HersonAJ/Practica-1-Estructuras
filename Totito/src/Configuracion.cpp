#include "Configuracion.h"

Configuracion::Configuracion()
    : filas(0), columnas(0), inicio(nullptr) {}

Configuracion::~Configuracion() {
    liberarMemoria();
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

void Configuracion::construirTablero() {
    inicio = nullptr;
    Punto* filaAnterior = nullptr; // primer punto de la fila anterior

    for (int i = 0; i < filas; i++) {
        Punto* filaActual = nullptr;    // primer punto de la fila actual
        Punto* anterior = nullptr;      // último punto creado en esta fila
        Punto* arriba = filaAnterior;   // punto justo arriba

        for (int j = 0; j < columnas; j++) {
            Punto* nuevo = new Punto(i, j);

            // Guardar primer punto del tablero
            if (i == 0 && j == 0) {
                inicio = nuevo;
            }

            // Enlace horizontal
            if (anterior != nullptr) {
                anterior->setRight(nuevo);
                nuevo->setLeft(anterior);
            }
            anterior = nuevo;

            // Enlace vertical
            if (arriba != nullptr) {
                arriba->setDown(nuevo);
                nuevo->setUp(arriba);
                arriba = arriba->getRight(); // avanzar en la fila de arriba
            }

            // Guardar primer punto de la fila actual
            if (j == 0) {
                filaActual = nuevo;
            }
        }
        // La fila actual pasa a ser la anterior en la siguiente iteración
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
}

void Configuracion::liberarMemoria() {
    // Liberar todos los puntos recorriendo la malla
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

#include "Tablero.h"

Tablero::Tablero(int f, int c) : filas(f), columnas(c), inicio(nullptr) {}

Tablero::~Tablero() {
    liberarMemoria();
}

void Tablero::construir() {
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
                arriba = arriba->getRight();
            }

            if (j == 0) filaActual = nuevo;
        }
        filaAnterior = filaActual;
    }
}

void Tablero::mostrarVacio() const {
    std::cout << "\nTABLERO VACIO:\n";
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

void Tablero::liberarMemoria() {
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

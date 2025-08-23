#include "Tablero.h"

//constructor
Tablero::Tablero(int f, int c) : filas(f), columnas(c) {}

//desctructor
Tablero::~Tablero(){}

void Tablero::construir() {
    //crear puntos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            Punto* nuevo = new Punto(i, j);
            puntos.agregarFinal(nuevo);
        }
    }

    //lineas
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            Punto* actual = buscarPunto(i , j);

            //linea horizontal hacia la derecha
            if (j < columnas -1) {
                Punto* derecha = buscarPunto(i, j + 1);
                Linea* l = new Linea(actual, derecha, Orientacion::HORIZONTAL);
                lineas.agregarFinal(l);

                actual->setRight(derecha);
                derecha->setLeft(actual);

                actual->setLineaDerecha(l);
                derecha->setLineaIzquierda(l);
            }

            //linea vertical hacia abajo
            if (i < filas - 1 ){
                Punto* abajo = buscarPunto(i + 1, j);
                Linea* l = new Linea(actual, abajo, Orientacion::VERTICAL);
                lineas.agregarFinal(l);

                actual->setDown(abajo);
                abajo->setUp(actual);

                actual->setLineaAbajo(l);
                abajo->setLineaArriba(l);
            }
        }
    }

    //reconocimiento de celdas asociadas a cuatro lineas
    for (int i = 0; i < filas -1; i++) {
        for (int j = 0; j < columnas - 1; j++) {
            Celda* celda = new Celda(i, j);
            celdas.agregarFinal(celda);

            Punto* supIzq = buscarPunto(i, j);
            Punto* supDer = buscarPunto(i, j + 1);
            Punto* infIzq = buscarPunto(i + 1, j);
            Punto* infDer = buscarPunto(i + 1, j + 1);

            Linea* arriba = buscarLinea(supIzq, supDer);
            Linea* abajo = buscarLinea(infIzq, infDer);
            Linea* izq = buscarLinea(supIzq, infIzq);
            Linea* der = buscarLinea(supDer, infDer);

            celda->setLineaArriba(arriba);
            celda->setLineaAbajo(abajo);
            celda->setLineaIzquierda(izq);
            celda->setLineaDerecha(der);

            if (arriba) arriba->setCeldaA(celda);
            if (abajo) abajo->setCeldaB(celda);
            if (izq) izq->setCeldaA(celda);
            if (der) der->setCeldaB(celda);
        }
    }
}

//mostrar tablero con coordenadas alineadas
void Tablero::mostrar() const {
    std::cout << "\n  "; // espacio inicial para alinear con índice de filas

    // Encabezado columnas (alineado a los puntos)
    for (int j = 0; j < columnas; j++) {
        char letra = 'A' + j;
        std::cout << letra << "   "; // letra y un espacio
    }
    std::cout << "\n";

    for (int i = 0; i < filas; i++) {
        std::cout << i << " "; // índice de fila al inicio

        for (int j = 0; j < columnas; j++) {
            Punto* p = buscarPunto(i, j);
            std::cout << p->toString();

            if (j < columnas - 1) {
                Linea* l = buscarLinea(p, buscarPunto(i, j + 1));
                std::cout << (l ? l->toString() : " ");
            }
        }
        std::cout << "\n";

        //lineas verticales + celdas
        if (i < filas - 1) {
            std::cout << "  "; // espacio bajo índice de fila
            for (int j = 0; j < columnas; j++) {
                Punto* p = buscarPunto(i, j);
                Linea* l = buscarLinea(p, buscarPunto(i + 1, j));
                std::cout << (l ? l->toString() : " ");

                if (j < columnas - 1) {
                    Celda* c = buscarCelda(i, j);
                    std::cout << (c ? c->toString() : " ");
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

//busquedas
Punto* Tablero::buscarPunto(int fila, int col) const {
    for (auto nodo = puntos.getCabeza(); nodo != nullptr; nodo = nodo->getSiguiente()) {
        Punto* p = nodo->getDato();
        if (p->getRow() == fila && p->getCol() == col) return p;
    }
    return nullptr;
}

Linea* Tablero::buscarLinea(Punto* p1, Punto* p2) const {
    if (!p1 || !p2) return nullptr;
    for (auto nodo = lineas.getCabeza(); nodo != nullptr; nodo = nodo->getSiguiente()) {
        Linea* l = nodo->getDato();
        if ((l->getP1() == p1 && l->getP2() == p2) || (l->getP1() == p2 && l->getP2() == p1)) {
            return l;
        }
    }
    return nullptr;
}

Celda* Tablero::buscarCelda(int fila, int col) const {
    for (auto nodo = celdas.getCabeza(); nodo != nullptr; nodo = nodo->getSiguiente()) {
        Celda* c = nodo->getDato();
        if (c->getRow() == fila && c->getCol() == col) return c;
    }
    return nullptr;
}

int Tablero::getFilas() const {
    return filas;
}

int Tablero::getColumnas() const {
    return columnas;
}


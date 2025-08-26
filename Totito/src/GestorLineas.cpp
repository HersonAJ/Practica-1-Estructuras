#include "GestorLineas.h"
#include <iostream>

GestorLineas::GestorLineas(ListaEnlazada<Linea*>* lineas, Tablero* tablero)
    : lineas(lineas), tablero(tablero) {}

// Buscar una línea entre dos puntos
Linea* GestorLineas::buscarLinea(int fila1, int col1, int fila2, int col2) const {
    Nodo4<Linea*>* lineaPtr = lineas->obtenerCabeza();
    while (lineaPtr) {
        Linea* l = lineaPtr->obtenerDato();
        if ((l->getP1()->getFila() == fila1 && l->getP1()->getColumna() == col1 &&
             l->getP2()->getFila() == fila2 && l->getP2()->getColumna() == col2) ||
            (l->getP1()->getFila() == fila2 && l->getP1()->getColumna() == col2 &&
             l->getP2()->getFila() == fila1 && l->getP2()->getColumna() == col1)) {
            return l;
        }
        lineaPtr = lineaPtr->obtenerDerecha();
    }
    return nullptr;
}

// Colocar una línea y verificar celdas
void GestorLineas::colocarLinea(int f1, int c1, int f2, int c2, Jugador* jugador) {
    Linea* l = buscarLinea(f1, c1, f2, c2);
    if (l) {
        if (!l->estaColocada()) {
            l->colocar(jugador->getInicial());
            std::cout << "Línea colocada entre (" << f1 << "," << c1 
                      << ") y (" << f2 << "," << c2 << ")\n";

            // Verificar si alguna celda se completó con esta línea
            tablero->verificarCeldasPorLinea(l, jugador);
        } else {
            std::cout << "Esa línea ya está colocada.\n";
        }
    } else {
        std::cout << "No existe una línea entre esas coordenadas.\n";
    }
}

// Mostrar todas las líneas
void GestorLineas::mostrarLineas() const {
    Nodo4<Linea*>* actual = lineas->obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        std::cout << "(" << l->getP1()->getFila() << "," << l->getP1()->getColumna()
                  << ") <-> (" << l->getP2()->getFila() << "," << l->getP2()->getColumna()
                  << ") "
                  << (l->estaColocada() ? "[X]" : "[ ]")
                  << " " << l->toString()
                  << "\n";
        actual = actual->obtenerDerecha();
    }
}

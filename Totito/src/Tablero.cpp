#include "Tablero.h"
#include "ListaEnlazada.h"
#include <iostream>
using namespace std;

Tablero::Tablero(int filas, int columnas)
    : filas(filas), columnas(columnas), inicio(nullptr) {
    crearMalla();
}

Tablero::~Tablero() {
    Nodo4<Punto>* filaPtr = inicio;
    while (filaPtr) {
        Nodo4<Punto>* colPtr = filaPtr;
        filaPtr = filaPtr->obtenerAbajo();
        while (colPtr) {
            Nodo4<Punto>* temp = colPtr;
            colPtr = colPtr->obtenerDerecha();
            delete temp;
        }
    }
}

void Tablero::crearMalla() {
    if (filas <= 0 || columnas <= 0) {
        inicio = nullptr;
        return;
    }

    // Lista de filas
    ListaEnlazada< ListaEnlazada<Punto>* > filasLista;

    // Crear cada fila
    for (int f = 0; f < filas; ++f) {
        auto* filaActual = new ListaEnlazada<Punto>();
        for (int c = 0; c < columnas; ++c) {
            filaActual->insertarFinal(Punto(f, c));
        }
        filasLista.insertarFinal(filaActual);
    }

    // Enlazar verticalmente
    Nodo4< ListaEnlazada<Punto>* >* nodoFila = filasLista.obtenerCabeza();
    Nodo4< ListaEnlazada<Punto>* >* nodoFilaAbajo = nodoFila ? nodoFila->obtenerDerecha() : nullptr;

    while (nodoFila && nodoFilaAbajo) {
        Nodo4<Punto>* nodoCol = nodoFila->obtenerDato()->obtenerCabeza();
        Nodo4<Punto>* nodoColAbajo = nodoFilaAbajo->obtenerDato()->obtenerCabeza();

        while (nodoCol && nodoColAbajo) {
            nodoCol->establecerAbajo(nodoColAbajo);
            nodoColAbajo->establecerArriba(nodoCol);

            nodoCol = nodoCol->obtenerDerecha();
            nodoColAbajo = nodoColAbajo->obtenerDerecha();
        }

        nodoFila = nodoFilaAbajo;
        nodoFilaAbajo = nodoFilaAbajo->obtenerDerecha();
    }

    // Guardar inicio
    if (filasLista.obtenerCabeza()) {
        inicio = filasLista.obtenerCabeza()->obtenerDato()->obtenerCabeza();
    }
}

void Tablero::imprimir() const {
    // Encabezado de columnas (letras)
    cout << "    "; // espacio inicial para alinear con números de filas
    for (int c = 0; c < columnas; c++) {
        char letra = 'A' + c;
        cout << letra << "   ";
    }
    cout << "\n\n";

    // Recorrido por filas
    Nodo4<Punto>* filaPtr = inicio;
    int filaIndice = 0;
    while (filaPtr) {
        cout << filaIndice << "   "; // imprimir número de fila

        Nodo4<Punto>* colPtr = filaPtr;
        while (colPtr) {
            cout << colPtr->obtenerDato().simbolo() << "   ";
            colPtr = colPtr->obtenerDerecha();
        }
        cout << "\n\n";
        filaPtr = filaPtr->obtenerAbajo();
        filaIndice++;
    }
}

//localizar un nodo para ver si estan enlazados 
Nodo4<Punto>* Tablero::obtenerNodo(int fila, int columna) const {
    Nodo4<Punto>* filaPtr = inicio;
    for (int f = 0; f < fila && filaPtr; ++f) {
        filaPtr = filaPtr->obtenerAbajo();
    }
    if (!filaPtr) return nullptr;

    Nodo4<Punto>* colPtr = filaPtr;
    for (int c = 0; c < columna && colPtr; ++c) {
        colPtr = colPtr->obtenerDerecha();
    }
    return colPtr;
}

void Tablero::mostrarVecinos(int fila, int columna) const {
    Nodo4<Punto>* nodo = obtenerNodo(fila, columna);
    if (!nodo) {
        cout << "No existe el nodo en (" << fila << "," << columna << ")\n";
        return;
    }

    cout << "Vecinos de (" << fila << "," << columna << "):\n";
    if (nodo->obtenerArriba()) 
        cout << "  Arriba -> (" << nodo->obtenerArriba()->obtenerDato().getFila()
             << "," << nodo->obtenerArriba()->obtenerDato().getColumna() << ")\n";
    if (nodo->obtenerAbajo()) 
        cout << "  Abajo -> (" << nodo->obtenerAbajo()->obtenerDato().getFila()
             << "," << nodo->obtenerAbajo()->obtenerDato().getColumna() << ")\n";
    if (nodo->obtenerIzquierda()) 
        cout << "  Izquierda -> (" << nodo->obtenerIzquierda()->obtenerDato().getFila()
             << "," << nodo->obtenerIzquierda()->obtenerDato().getColumna() << ")\n";
    if (nodo->obtenerDerecha()) 
        cout << "  Derecha -> (" << nodo->obtenerDerecha()->obtenerDato().getFila()
             << "," << nodo->obtenerDerecha()->obtenerDato().getColumna() << ")\n";
}
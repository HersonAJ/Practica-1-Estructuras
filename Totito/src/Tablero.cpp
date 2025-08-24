#include "Tablero.h"
#include "ListaEnlazada.h"
#include "Linea.h"
#include <iostream>
using namespace std;

Tablero::Tablero(int filas, int columnas)
    : filas(filas), columnas(columnas), inicio(nullptr) {
    crearMalla();
    generarLineas();//ahora para generar las lineas
}

Tablero::~Tablero() {
    // Liberar memoria de la malla
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

    // Liberar memoria de las líneas
    Nodo4<Linea*>* lineaPtr = lineas.obtenerCabeza();
    while (lineaPtr) {
        delete lineaPtr->obtenerDato();
        lineaPtr = lineaPtr->obtenerDerecha();
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

//metodo para generar las lineas en el tablero
void Tablero::generarLineas() {
    Nodo4<Punto>* filaPtr = inicio;

    while (filaPtr) {
        Nodo4<Punto>* colPtr = filaPtr;

        while (colPtr) {
            // Línea horizontal (punto con su derecha)
            if (colPtr->obtenerDerecha()) {
                Linea* l = new Linea(&(colPtr->obtenerDato()), &(colPtr->obtenerDerecha()->obtenerDato()), Orientacion::HORIZONTAL);
                lineas.insertarFinal(l);
            }
            // Línea vertical (punto con su abajo)
            if (colPtr->obtenerAbajo()) {
                Linea* l = new Linea(&(colPtr->obtenerDato()), &(colPtr->obtenerAbajo()->obtenerDato()), Orientacion::VERTICAL);
                lineas.insertarFinal(l);
            }
            colPtr = colPtr->obtenerDerecha();
        }
        filaPtr = filaPtr->obtenerAbajo();
    }
}

// Buscar una línea entre dos puntos
Linea* Tablero::buscarLinea(int fila1, int col1, int fila2, int col2) const {
    Nodo4<Punto>* nodo1 = obtenerNodo(fila1, col1);
    Nodo4<Punto>* nodo2 = obtenerNodo(fila2, col2);

    if (!nodo1 || !nodo2) return nullptr;

    Nodo4<Linea*>* lineaPtr = lineas.obtenerCabeza();
    while (lineaPtr) {
        Linea* l = lineaPtr->obtenerDato();
        if ((l->getP1() == &(nodo1->obtenerDato()) && l->getP2() == &(nodo2->obtenerDato())) ||
            (l->getP1() == &(nodo2->obtenerDato()) && l->getP2() == &(nodo1->obtenerDato()))) {
            return l;
        }
        lineaPtr = lineaPtr->obtenerDerecha();
    }
    return nullptr;
}

// Colocar una línea entre dos puntos
void Tablero::colocarLinea(int f1, int c1, int f2, int c2, char jugador) {
    Nodo4<Punto>* n1 = obtenerNodo(f1, c1);
    Nodo4<Punto>* n2 = obtenerNodo(f2, c2);

    if (!n1 || !n2) {
        cout << "Coordenadas inválidas.\n";
        return;
    }

    // Buscar la línea en la lista
    Nodo4<Linea*>* actual = lineas.obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        if ((l->getP1() == &n1->obtenerDato() && l->getP2() == &n2->obtenerDato()) ||
            (l->getP1() == &n2->obtenerDato() && l->getP2() == &n1->obtenerDato())) {
            l->colocar(jugador);
            cout << "Linea colocada entre (" << f1 << "," << c1 
                 << ") y (" << f2 << "," << c2 << ")\n";
            return;
        }
        actual = actual->obtenerDerecha();
    }

    cout << "No existe una línea entre esas coordenadas.\n";
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
// Mostrar todas las líneas de la lista
void Tablero::mostrarLineas() const {
    Nodo4<Linea*>* actual = lineas.obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        cout << "(" << l->getP1()->getFila() << "," << l->getP1()->getColumna()
             << ") <-> (" << l->getP2()->getFila() << "," << l->getP2()->getColumna()
             << ") "
             << (l->estaColocada() ? "[X]" : "[ ]")
             << " " << l->toString()
             << "\n";
        actual = actual->obtenerDerecha();
    }
}
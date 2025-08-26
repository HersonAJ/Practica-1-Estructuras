#include "Tablero.h"
#include "ListaEnlazada.h"
#include "Linea.h"
#include <iostream>
using namespace std;

Tablero::Tablero(int filas, int columnas)
    : filas(filas), columnas(columnas), inicio(nullptr) {

        std::cout << "DEBUG_TABLERO: constructor simplificado" << std::endl;
    crearMalla();
    generarLineas(); // Genera las líneas que pertenecen al tablero
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

    // Lista temporal de filas
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

        // Avanzar UNA fila hacia abajo
        nodoFila = nodoFilaAbajo;
        nodoFilaAbajo = nodoFilaAbajo->obtenerDerecha();
    }

    // Guardar inicio (primer punto de la primera fila)
    if (filasLista.obtenerCabeza()) {
        inicio = filasLista.obtenerCabeza()->obtenerDato()->obtenerCabeza();
    }
}



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

void Tablero::imprimir() const {
    // Encabezado de columnas
    cout << "    ";
    for (int c = 0; c < columnas; ++c) {
        cout << char('A' + c) << "   ";
    }
    cout << "\n\n";

    for (int f = 0; f < filas; ++f) {
        // Fila de puntos + horizontales
        cout << f << "   ";
        for (int c = 0; c < columnas; ++c) {
            cout << "o";
            if (c < columnas - 1) {
                cout << (existeLineaColocada(f, c, f, c + 1) ? "---" : "   ");
            }
        }
        cout << "\n";

        // Fila de verticales (solo si no es la última fila)
        if (f < filas - 1) {
            cout << "    ";
            for (int c = 0; c < columnas; ++c) {
                cout << (existeLineaColocada(f, c, f + 1, c) ? "|" : " ");
                if (c < columnas - 1) cout << "   ";
            }
            cout << "\n\n";
        }
    }
}


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

bool Tablero::existeLineaColocada(int f1, int c1, int f2, int c2) const {
    Nodo4<Linea*>* actual = lineas.obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        int lf1 = l->getP1()->getFila();
        int lc1 = l->getP1()->getColumna();
        int lf2 = l->getP2()->getFila();
        int lc2 = l->getP2()->getColumna();

        if (((lf1 == f1 && lc1 == c1 && lf2 == f2 && lc2 == c2) ||
             (lf1 == f2 && lc1 == c2 && lf2 == f1 && lc2 == c1))
            && l->estaColocada()) {
            return true;
        }
        actual = actual->obtenerDerecha();
    }
    return false;
}

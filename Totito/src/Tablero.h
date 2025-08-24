#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo4.h"
#include "Punto.h"
#include "Linea.h"
#include "ListaEnlazada.h"

class Tablero {
private:
    int filas;
    int columnas;
    Nodo4<Punto>* inicio; // nodo de la esquina superior izquierda

    ListaEnlazada<Linea*> lineas; // TODAS las posibles líneas del tablero

    void crearMalla();

    Nodo4<Punto>* obtenerNodo(int fila, int columna) const;

public:
    Tablero(int filas, int columnas);
    ~Tablero();

    void imprimir() const;
    void mostrarVecinos(int fila, int columna) const;

    // === Gestión de líneas ===
    Linea* buscarLinea(int fila1, int col1, int fila2, int col2) const;
    void colocarLinea(int fila1, int col1, int fila2, int col2, char jugador);
    void generarLineas(); // genera todas las lineas horizontales y verticales
    void mostrarLineas() const;
};

#endif

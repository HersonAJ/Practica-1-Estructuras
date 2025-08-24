#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo4.h"
#include "Punto.h"

class Tablero {
    private:
    int filas;
    int columnas;
    Nodo4<Punto>* inicio;//nodo de la esquina superior izquierda

    void crearMalla();
    Nodo4<Punto>* obtenerNodo(int fila, int columna) const;

    public:
    Tablero(int filas, int columnas);
    ~Tablero();

    void imprimir() const;
    void mostrarVecinos(int fila, int columna) const;

};

#endif
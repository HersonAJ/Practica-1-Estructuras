#ifndef TABLERO_H
#define TABLERO_H

#include "Punto.h"
#include <iostream>

class Tablero {
    private:
    int filas;
    int columnas;
    Punto* inicio;

    public:
    Tablero(int filas, int columnas);
    ~Tablero();

    void construir();
    void mostrarVacio() const;
    void liberarMemoria();
};

#endif
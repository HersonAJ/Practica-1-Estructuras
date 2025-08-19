#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <string>
#include "Lista.h"
#include "Punto.h"
#include "Linea.h"
#include "Celda.h"

class Tablero {
private:
    int filas;
    int columnas;

    Lista<Punto> puntos;
    Lista<Linea> lineas;
    Lista<Celda> celdas;

public:
    Tablero(int f, int c);
    ~Tablero();

    // Construcción
    void construir();

    // Mostrar tablero
    void mostrar() const;

    // Métodos de acceso
    Punto* buscarPunto(int fila, int col) const;
    Linea* buscarLinea(Punto* p1, Punto* p2) const;
    Celda* buscarCelda(int fila, int col) const;

    int getFilas() const;
    int getColumnas() const;

    bool agregarLinea(const std::string& c1, const std::string& c2, char jugador);
};

#endif // TABLERO_H

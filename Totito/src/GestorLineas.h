#ifndef GESTORLINEAS_H
#define GESTORLINEAS_H

#include "Linea.h"
#include "ListaEnlazada.h"
#include "Punto.h"
#include "Nodo4.h"
#include <iostream>
#include "Tablero.h"

class GestorLineas {
    private:
    ListaEnlazada<Linea*>* lineas; //lista de lineas del tablero
    Tablero* tablero;

    public:
    //constructor que recibe la lista de lineas que genera el tablero
    //eliminar el tablero del constructor si falla
    GestorLineas(ListaEnlazada<Linea*>* lineas, Tablero* tablero);

    //metodos de gestion
    Linea* buscarLinea(int fila1, int col1, int fila2, int col2) const;
    void colocarLinea(int fila1, int col1, int fila2, int col2, Jugador* jugador);
    void mostrarLineas() const;
};

#endif
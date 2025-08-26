#ifndef GESTORLINEAS_H
#define GESTORLINEAS_H

#include "Linea.h"
#include "ListaEnlazada.h"
#include "Punto.h"
#include "Nodo4.h"
#include <iostream>

class GestorLineas {
    private:
    ListaEnlazada<Linea*>* lineas; //lista de lineas del tablero

    public:
    //constructor que recibe la lista de lineas que genera el tablero
    GestorLineas(ListaEnlazada<Linea*>* lineas);

    //metodos de gestion
    Linea* buscarLinea(int fila1, int col1, int fila2, int col2) const;
    void colocarLinea(int fila1, int col1, int fila2, int col2, char jugador);
    void mostrarLineas() const;
};

#endif
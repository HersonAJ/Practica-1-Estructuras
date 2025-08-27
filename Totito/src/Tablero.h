#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo4.h"
#include "Punto.h"
#include "Linea.h"
#include "ListaEnlazada.h"
#include "Celda.h"

class Tablero {
private:
    int filas;
    int columnas;
    Nodo4<Punto>* inicio; // nodo de la esquina superior izquierda

    ListaEnlazada<Linea*> lineas; // TODAS las posibles líneas del tablero
    Nodo4<Celda>* inicioCeldas;

    void crearMalla();

    //Nodo4<Punto>* obtenerNodo(int fila, int columna) const;

    //metodo para verificar si una lista ya esta colocada 
    bool existeLineaColocada(int f1, int c1, int f2, int c2) const;
    Linea* buscarLinea(Punto* p1, Punto* p2);

public:
    Tablero(int filas, int columnas);
    ~Tablero();

    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
    void imprimir() const;
    //void mostrarVecinos(int fila, int columna) const;
    void generarLineas(); // genera todas las lineas horizontales y verticales
    void generarCeldas();// hasta aqui esta funcionando bien 

    ListaEnlazada<Linea*>* getLineas() { return &lineas; }
    //void debugCeldas() const;

    //eliminar si algo falla
    void verificarCeldasPorLinea(Linea* linea, Jugador* jugador);
    //metodos de depuracion 
    //void debugPuntosDeCelda(int filaCelda, int colCelda) const;
    Nodo4<Celda>* getInicioCeldas() const { return inicioCeldas;}

    void expandirAbajo();
    void expandirDerecha();
    void explotarPunto(int fila, int columna);
    Nodo4<Punto>* buscarPunto(int fila, int columna) const;
};

#endif

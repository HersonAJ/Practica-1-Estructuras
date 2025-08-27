#include "Punto.h"

Punto::Punto(int fila, int columna) 
    : fila(fila), columna(columna), destruido(false) {}


    void Punto::destruir() {
        destruido = true;
    }

    bool Punto::estaDestruido() const {
        return destruido;
    }
    int Punto::getFila() const { return fila; }
    int Punto::getColumna() const { return columna; }

    char Punto::simbolo() const { return destruido ? 'X' : 'o'; }

#include "Punto.h"

Punto::Punto(int fila, int columna) 
    : fila(fila), columna(columna) {}

int Punto::getFila() const { return fila; }
int Punto::getColumna() const { return columna; }

char Punto::simbolo() const { return 'o'; }

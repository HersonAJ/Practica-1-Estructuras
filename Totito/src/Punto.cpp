#include "Punto.h"
#include "Linea.h"
#include <sstream>

// Constructor
Punto::Punto(int fila, int columna)
    : row(fila), col(columna), exists(true),
      up(nullptr), down(nullptr), left(nullptr), right(nullptr),
      lineaArriba(nullptr), lineaAbajo(nullptr),
      lineaIzquierda(nullptr), lineaDerecha(nullptr) {}

// Getters y Setters 
int Punto::getRow() const { return row; }
int Punto::getCol() const { return col; }

bool Punto::isActive() const { return exists; }
void Punto::setActive(bool estado) { exists = estado; }

// Vecinos
void Punto::setUp(Punto* p) { up = p; }
void Punto::setDown(Punto* p) { down = p; }
void Punto::setLeft(Punto* p) { left = p; }
void Punto::setRight(Punto* p) { right = p; }

Punto* Punto::getUp() const { return up; }
Punto* Punto::getDown() const { return down; }
Punto* Punto::getLeft() const { return left; }
Punto* Punto::getRight() const { return right; }

// Líneas incidentes
void Punto::setLineaArriba(Linea* l) { lineaArriba = l; }
void Punto::setLineaAbajo(Linea* l) { lineaAbajo = l; }
void Punto::setLineaIzquierda(Linea* l) { lineaIzquierda = l; }
void Punto::setLineaDerecha(Linea* l) { lineaDerecha = l; }

Linea* Punto::getLineaArriba() const { return lineaArriba; }
Linea* Punto::getLineaAbajo() const { return lineaAbajo; }
Linea* Punto::getLineaIzquierda() const { return lineaIzquierda; }
Linea* Punto::getLineaDerecha() const { return lineaDerecha; }

std::string Punto::toString() const {
    return exists ? "o" : " "; 
}

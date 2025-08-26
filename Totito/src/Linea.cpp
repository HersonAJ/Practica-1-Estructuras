#include "Linea.h"
#include "Punto.h" 

// Constructor
Linea::Linea(Punto* inicio, Punto* fin, Orientacion ori)
    : p1(inicio), p2(fin), orientacion(ori),
      colocada(false), jugadorColoco(' ') {}

// Getters
Punto* Linea::getP1() const { return p1; }
Punto* Linea::getP2() const { return p2; }
Orientacion Linea::getOrientacion() const { return orientacion; }
bool Linea::estaColocada() const { return colocada; }
char Linea::getJugadorColoco() const { return jugadorColoco; }

// Acciones
void Linea::colocar(char inicialJugador) {
    colocada = true;
    jugadorColoco = inicialJugador;
}

void Linea::quitar() {
    colocada = false;
    jugadorColoco = ' ';
}

// Representación visual
std::string Linea::toString() const {
    if (!colocada) {
        return (orientacion == Orientacion::HORIZONTAL) ? "   " : " ";
    }
    return (orientacion == Orientacion::HORIZONTAL) ? "---" : "|";
}
//hasta aqui esta funcionando bien 
bool Linea::conecta(const Punto* a, const Punto* b) const {
    return ( (p1 == a && p2 == b) || (p1 == b && p2 == a) );
}

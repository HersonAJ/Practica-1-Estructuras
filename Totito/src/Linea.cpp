#include "Linea.h"
#include "Punto.h"
#include "Celda.h"

Linea::Linea(Punto* inicio, Punto* fin, Orientacion ori)
    : p1(inicio), p2(fin), orientacion(ori),
      colocada(false), jugadorColoco(' '),
      powerUp(TipoPowerUp::NINGUNO), powerUpVisible(false),
      celdaA(nullptr), celdaB(nullptr) {}

// Getters
Punto* Linea::getP1() const { return p1; }
Punto* Linea::getP2() const { return p2; }
Orientacion Linea::getOrientacion() const { return orientacion; }
bool Linea::estaColocada() const { return colocada; }
char Linea::getJugadorColoco() const { return jugadorColoco; }

// Setters
void Linea::colocar(char inicialJugador) {
    colocada = true;
    jugadorColoco = inicialJugador;
}

void Linea::quitar() {
    colocada = false;
    jugadorColoco = ' ';
}

// PowerUp
void Linea::asignarPowerUp(TipoPowerUp tipo, bool visible) {
    powerUp = tipo;
    powerUpVisible = visible;
}

TipoPowerUp Linea::getPowerUp() const { return powerUp; }
bool Linea::isPowerUpVisible() const { return powerUpVisible; }
void Linea::setPowerUpVisible(bool estado) { powerUpVisible = estado; }

// Celdas adyacentes
void Linea::setCeldaA(Celda* c) { celdaA = c; }
void Linea::setCeldaB(Celda* c) { celdaB = c; }
Celda* Linea::getCeldaA() const { return celdaA; }
Celda* Linea::getCeldaB() const { return celdaB; }

// Representación visual
std::string Linea::toString() const {
    if (!colocada) {
        if (powerUp != TipoPowerUp::NINGUNO && powerUpVisible) {
            // Mostrar abreviatura del powerup
            switch (powerUp) {
                case TipoPowerUp::DL: return "DL";
                case TipoPowerUp::TS: return "TS";
                case TipoPowerUp::BL: return "BL";
                case TipoPowerUp::PS: return "PS";
                case TipoPowerUp::LS: return "LS";
                case TipoPowerUp::ES: return "ES";
                case TipoPowerUp::UF: return "UF";
                case TipoPowerUp::AC: return "AC";
                case TipoPowerUp::NT: return "NT";
                case TipoPowerUp::EX: return "EX";
                default: return "  ";
            }
        }
        // Si no hay powerup visible, espacio vacío
        return (orientacion == Orientacion::HORIZONTAL) ? "   " : " ";
    }
    // Línea colocada
    return (orientacion == Orientacion::HORIZONTAL) ? "---" : "|";
}

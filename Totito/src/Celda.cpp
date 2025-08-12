#include "Celda.h"
#include "Linea.h"

Celda::Celda(int fila, int columna)
    : row(fila), col(columna),
      lineaArriba(nullptr), lineaAbajo(nullptr),
      lineaIzquierda(nullptr), lineaDerecha(nullptr),
      completada(false), propietario(' '),
      powerUp(TipoPowerUpCelda::NINGUNO), powerUpVisible(false) {}

// Getters
int Celda::getRow() const { return row; }
int Celda::getCol() const { return col; }
bool Celda::estaCompletada() const { return completada; }
char Celda::getPropietario() const { return propietario; }

// Setters
void Celda::setPropietario(char inicialJugador) { propietario = inicialJugador; }
void Celda::setCompletada(bool estado) { completada = estado; }

// Líneas
void Celda::setLineaArriba(Linea* l) { lineaArriba = l; }
void Celda::setLineaAbajo(Linea* l) { lineaAbajo = l; }
void Celda::setLineaIzquierda(Linea* l) { lineaIzquierda = l; }
void Celda::setLineaDerecha(Linea* l) { lineaDerecha = l; }

Linea* Celda::getLineaArriba() const { return lineaArriba; }
Linea* Celda::getLineaAbajo() const { return lineaAbajo; }
Linea* Celda::getLineaIzquierda() const { return lineaIzquierda; }
Linea* Celda::getLineaDerecha() const { return lineaDerecha; }

// PowerUp
void Celda::asignarPowerUp(TipoPowerUpCelda tipo, bool visible) {
    powerUp = tipo;
    powerUpVisible = visible;
}

TipoPowerUpCelda Celda::getPowerUp() const { return powerUp; }
bool Celda::isPowerUpVisible() const { return powerUpVisible; }
void Celda::setPowerUpVisible(bool estado) { powerUpVisible = estado; }

// Verifica si está completa
bool Celda::verificarCompleta() const {
    if (!lineaArriba || !lineaAbajo || !lineaIzquierda || !lineaDerecha) {
        return false;
    }
    return lineaArriba->estaColocada() &&
           lineaAbajo->estaColocada() &&
           lineaIzquierda->estaColocada() &&
           lineaDerecha->estaColocada();
}

// Representación en consola
std::string Celda::toString() const {
    if (completada) {
        return std::string(1, propietario);
    }
    if (powerUp != TipoPowerUpCelda::NINGUNO && powerUpVisible) {
        switch (powerUp) {
            case TipoPowerUpCelda::DL: return "DL";
            case TipoPowerUpCelda::TS: return "TS";
            case TipoPowerUpCelda::BL: return "BL";
            case TipoPowerUpCelda::PS: return "PS";
            case TipoPowerUpCelda::LS: return "LS";
            case TipoPowerUpCelda::ES: return "ES";
            case TipoPowerUpCelda::UF: return "UF";
            case TipoPowerUpCelda::AC: return "AC";
            case TipoPowerUpCelda::NT: return "NT";
            case TipoPowerUpCelda::EX: return "EX";
            default: return "  ";
        }
    }
    return "  "; // vacío
}

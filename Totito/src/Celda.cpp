#include "Celda.h"

Celda::Celda(int fila, int columna,
             Punto* supIzq, Punto* supDer, Punto* infIzq, Punto* infDer,
             Linea* arriba, Linea* derecha, Linea* abajo, Linea* izquierda)
    : fila(fila), columna(columna),
      completada(false), propietario(nullptr), powerUp(nullptr) {

    esquinas[0] = supIzq;
    esquinas[1] = supDer;
    esquinas[2] = infIzq;
    esquinas[3] = infDer;

    lineas[0] = arriba;
    lineas[1] = derecha;
    lineas[2] = abajo;
    lineas[3] = izquierda;
}

// Getters
int Celda::getFila() const { return fila; }
int Celda::getColumna() const { return columna; }
Jugador* Celda::getPropietario() const { return propietario; }
bool Celda::estaCompletada() const { return completada; }
Punto* Celda::getEsquina(int indice) const {
    if (indice < 0 || indice >= 4) return nullptr;
    return esquinas[indice];
}
Linea* Celda::getLinea(int indice) const {
    if (indice < 0 || indice >= 4) return nullptr;
    return lineas[indice];
}

// Verifica si todas las líneas están colocadas
bool Celda::verificarCompletada() const {
    for (int i = 0; i < 4; ++i) {
        if (!lineas[i] || !lineas[i]->estaColocada()) {
            return false;
        }
    }
    return true;
}

// Marca la celda como capturada por un jugador
void Celda::capturar(Jugador* jugador) {
    if (!completada && jugador) {
        completada = true;
        propietario = jugador;
        propietario->sumarPunto();
    }
}

// Comprueba si una línea pertenece a esta celda
bool Celda::contieneLinea(Linea* linea) const {
    for (int i = 0; i < 4; ++i) {
        if (linea == lineas[i]) return true;
    }
    return false;
}

// PowerUp (aún no implementado)
void Celda::asignarPowerUp(PowerUp* p) { powerUp = p; }
PowerUp* Celda::getPowerUp() const { return powerUp; }

// Devuelve la inicial del propietario o espacio si está libre
char Celda::obtenerInicialPropietario() const {
    return propietario ? propietario->getInicial() : ' ';
}

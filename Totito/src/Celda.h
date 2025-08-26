#ifndef CELDA_H
#define CELDA_H

#include "Punto.h"
#include "Linea.h"
#include "Jugador.h"

class PowerUp;

class Celda {
private:
    // Posición lógica de la celda (fila y columna de su esquina superior izquierda)
    int fila;
    int columna;

    Punto* esquinas[4];  // 0: supIzq, 1: supDer, 2: infIzq, 3: infDer

    // Líneas que forman la celda
    Linea* lineas[4];    // 0: arriba, 1: derecha, 2: abajo, 3: izquierda

    // Estado
    bool completada;
    Jugador* propietario;

    // PowerUp (aún no implementado)
    PowerUp* powerUp;

public:
    // Constructor por defecto
    Celda()
        : fila(0), columna(0),
          esquinas{nullptr, nullptr, nullptr, nullptr},
          lineas{nullptr, nullptr, nullptr, nullptr},
          completada(false), propietario(nullptr), powerUp(nullptr) {}

    Celda(int fila, int columna,
          Punto* supIzq, Punto* supDer, Punto* infIzq, Punto* infDer,
          Linea* arriba, Linea* derecha, Linea* abajo, Linea* izquierda);

    // Getters
    int getFila() const;
    int getColumna() const;
    Jugador* getPropietario() const;
    bool estaCompletada() const;
    Punto* getEsquina(int indice) const;
    Linea* getLinea(int indice) const;

    // Lógica
    bool verificarCompletada() const; // Solo verifica, no captura
    void capturar(Jugador* jugador);  // Marca como completada y asigna propietario
    bool contieneLinea(Linea* linea) const;

    // PowerUp
    void asignarPowerUp(PowerUp* p); 
    PowerUp* getPowerUp() const;

    // Representación
    char obtenerInicialPropietario() const;
};

#endif

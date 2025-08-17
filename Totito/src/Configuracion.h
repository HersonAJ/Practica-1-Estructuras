#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "Jugador.h"
#include <iostream>

#define MAX_JUGADORES 10

class Configuracion {
private:
    int filas;
    int columnas;
    Jugador* jugadores[MAX_JUGADORES];
    int cantidadJugadores;

public:
    Configuracion();
    ~Configuracion();

    void pedirDatos();      // pide filas y columnas
    void pedirJugadores();  // pide número de jugadores y sus nombres
    void mostrarJugadores() const;

    // Getters
    int getFilas() const;
    int getColumnas() const;
    int getCantidadJugadores() const;
    Jugador* getJugador(int i) const;
};

#endif // CONFIGURACION_H

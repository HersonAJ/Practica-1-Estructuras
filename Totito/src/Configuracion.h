#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "Punto.h"
#include "Jugador.h"
#include <iostream>

#define MAX_JUGADORES 10

class Configuracion {
private:
    int filas;
    int columnas;
    Punto* inicio; // Primer punto del tablero (arriba-izquierda)

    // Nuevos atributos
    Jugador* jugadores[MAX_JUGADORES];
    int cantidadJugadores;

public:
    Configuracion();
    ~Configuracion();

    void pedirDatos();
    void construirTablero();
    void mostrarTableroVacio() const;

    // Nuevos métodos
    void pedirJugadores();
    void mostrarJugadores() const;

    // Limpieza de memoria
    void liberarMemoria();
};

#endif // CONFIGURACION_H

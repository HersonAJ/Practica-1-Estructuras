#ifndef CONDICIONES_VICTORIA_H
#define CONDICIONES_VICTORIA_H

#include "Tablero.h"
#include "ListaEnlazada.h"
#include "Jugador.h"

class CondicionesVictoria {
private:
    Tablero* tablero;
    ListaEnlazada<Jugador*>* jugadores;

    ListaEnlazada<Jugador*>* filtrarPorPuntos(ListaEnlazada<Jugador*>* candidatos);
    ListaEnlazada<Jugador*> filtrarPorCuadradosTotales(Tablero* tablero, ListaEnlazada<Jugador*> jugadores);
    ListaEnlazada<Jugador*> filtrarPorFilasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores);
    ListaEnlazada<Jugador*> filtrarPorColumnasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores);

public:
    CondicionesVictoria(Tablero* tablero, ListaEnlazada<Jugador*>* jugadores);
    Jugador* obtenerGanador(Tablero* tablero);
};

#endif

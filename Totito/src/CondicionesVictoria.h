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

public:
    CondicionesVictoria(Tablero* tablero, ListaEnlazada<Jugador*>* jugadores);
    Jugador* obtenerGanador();
};

#endif

#ifndef EVALUADOR_CONDICIONES_H
#define EVALUADOR_CONDICIONES_H

#include "Tablero.h"
#include "Jugador.h"
#include "ListaEnlazada.h"

Jugador* evaluarGanador(Tablero* tablero, ListaEnlazada<Jugador*> jugadores);

#endif

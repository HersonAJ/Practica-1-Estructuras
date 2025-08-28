#pragma once
#include "ListaEnlazada.h"
#include "Tablero.h"
#include "Jugador.h"

// Solo necesita la lista
ListaEnlazada<Jugador*> filtrarPorPuntos(ListaEnlazada<Jugador*>* candidatos);

// Necesitan tablero + lista (por valor, no puntero)
ListaEnlazada<Jugador*> filtrarPorCuadrosTotales(Tablero* tablero, ListaEnlazada<Jugador*> candidatos);
ListaEnlazada<Jugador*> filtrarPorFilasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> candidatos);
ListaEnlazada<Jugador*> filtrarPorColumnasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> candidatos);
ListaEnlazada<Jugador*> filtrarPorPowerUpsUsados(ListaEnlazada<Jugador*> candidatos);

// Función principal para decidir ganador
Jugador* evaluarGanador(Tablero* tablero, ListaEnlazada<Jugador*> jugadores);

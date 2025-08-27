#include "CondicionesDeVictoria.h"
#include <iostream>

Jugador* evaluarGanador(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    // Filtro 1: por puntos — solo recibe la lista como puntero
    ListaEnlazada<Jugador*> candidatos = filtrarPorPuntos(&jugadores);
    if (candidatos.obtenerCantidad() == 1) {
        return candidatos.obtenerCabeza()->obtenerDato();
    }

    // Filtro 2: por cuadros totales — requiere tablero
    candidatos = filtrarPorCuadrosTotales(tablero, candidatos);
    if (candidatos.obtenerCantidad() == 1) {
        return candidatos.obtenerCabeza()->obtenerDato();
    }

    // Filtro 3: por filas ganadas
    candidatos = filtrarPorFilasGanadas(tablero, candidatos);
    if (candidatos.obtenerCantidad() == 1) {
        return candidatos.obtenerCabeza()->obtenerDato();
    }

    // Filtro 4: por columnas ganadas
    candidatos = filtrarPorColumnasGanadas(tablero, candidatos);
    if (candidatos.obtenerCantidad() == 1) {
        return candidatos.obtenerCabeza()->obtenerDato();
    }

    std::cout << "Empate técnico: no se pudo determinar un ganador tras aplicar todos los criterios." << std::endl;
    return nullptr;
}

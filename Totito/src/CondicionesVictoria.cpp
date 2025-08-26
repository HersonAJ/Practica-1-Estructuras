#include "CondicionesVictoria.h"
#include <iostream>

CondicionesVictoria::CondicionesVictoria(Tablero* tablero, ListaEnlazada<Jugador*>* jugadores) {
    this->tablero = tablero;
    this->jugadores = jugadores;
}

Jugador* CondicionesVictoria::obtenerGanador() {
    ListaEnlazada<Jugador*>* candidatos = jugadores;

    candidatos = filtrarPorPuntos(candidatos);
    if (candidatos->obtenerCantidad() == 1) {
        Nodo4<Jugador*>* nodoGanador = candidatos->obtenerCabeza();
        return nodoGanador->obtenerDato();
    }

    std::cout << "Empate técnico: no se pudo determinar un ganador solo por puntos." << std::endl;
    return nullptr;
}

ListaEnlazada<Jugador*>* CondicionesVictoria::filtrarPorPuntos(ListaEnlazada<Jugador*>* candidatos) {
    ListaEnlazada<Jugador*>* mejores = new ListaEnlazada<Jugador*>();
    int maxPuntos = -1;

    Nodo4<Jugador*>* actual = candidatos->obtenerCabeza();
    while (actual != nullptr) {
        Jugador* jugador = actual->obtenerDato();
        int puntos = jugador->getPuntos();

        if (puntos > maxPuntos) {
            maxPuntos = puntos;
            mejores->limpiar();
            mejores->insertarFinal(jugador);
        } else if (puntos == maxPuntos) {
            mejores->insertarFinal(jugador);
        }

        actual = actual->obtenerDerecha();
    }

    std::cout << "Filtrado por puntos: " << maxPuntos << " puntos." << std::endl;
    return mejores;
}

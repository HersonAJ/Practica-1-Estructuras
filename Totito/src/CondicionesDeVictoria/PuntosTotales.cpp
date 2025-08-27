#include "CondicionesDeVictoria.h"
#include <iostream>

ListaEnlazada<Jugador*> filtrarPorPuntos(ListaEnlazada<Jugador*>* candidatos) {
    ListaEnlazada<Jugador*> mejores;
    int maxPuntos = -1;

    Nodo4<Jugador*>* actual = candidatos->obtenerCabeza();
    while (actual != nullptr) {
        Jugador* jugador = actual->obtenerDato();
        int puntos = jugador->getPuntos();

        if (puntos > maxPuntos) {
            maxPuntos = puntos;
            mejores.limpiar();
            mejores.insertarFinal(jugador);
        } else if (puntos == maxPuntos) {
            mejores.insertarFinal(jugador);
        }

        actual = actual->obtenerDerecha();
    }

    std::cout << "Filtrado por puntos: " << maxPuntos << " puntos." << std::endl;
    return mejores;
}

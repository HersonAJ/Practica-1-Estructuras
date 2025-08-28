#include "CondicionesDeVictoria.h"
#include <iostream>

ListaEnlazada<Jugador*> filtrarPorPowerUpsUsados(ListaEnlazada<Jugador*> candidatos) {
    ListaEnlazada<Jugador*> ganadoresPowerUps;

    // Si la lista está vacía, no hay nada que evaluar
    if (candidatos.obtenerCantidad() == 0) {
        return ganadoresPowerUps;
    }

    int maxPowerUps = -1;

    // Recorre la lista para encontrar el máximo de power-ups usados
    Nodo4<Jugador*>* actual = candidatos.obtenerCabeza();
    while (actual != nullptr) {
        Jugador* jugador = actual->obtenerDato();
        int powerUps = jugador->getPowerUpsUsados();

        if (powerUps > maxPowerUps) {
            maxPowerUps = powerUps;
            ganadoresPowerUps.limpiar(); // Limpia la lista y empezamos de nuevo con el nuevo máximo
            ganadoresPowerUps.insertarFinal(jugador);
        } else if (powerUps == maxPowerUps) {
            ganadoresPowerUps.insertarFinal(jugador); // Agrega a los jugadores que empatan
        }
        actual = actual->obtenerDerecha();
    }
    
    std::cout << "Filtrado por PowerUps Usados: " << maxPowerUps << " PowerUps." << std::endl;
    return ganadoresPowerUps;
}
#include "CondicionesDeVictoria.h"
#include <iostream>

ListaEnlazada<Jugador*> filtrarPorCuadrosTotales(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    // Crear arreglo paralelo para contar celdas por jugador
    ListaEnlazada<int> conteos;
    Nodo4<Jugador*>* nodoJugador = jugadores.obtenerCabeza();
    while (nodoJugador) {
        conteos.insertarFinal(0); // Inicializar en 0
        nodoJugador = nodoJugador->obtenerDerecha();
    }

    // Recorrer celdas del tablero
    Nodo4<Celda>* filaCelda = tablero->getInicioCeldas();
    while (filaCelda) {
        Nodo4<Celda>* celdaPtr = filaCelda;
        while (celdaPtr) {
            Celda& celda = celdaPtr->obtenerDato();
            if (celda.estaCompletada()) {
                Jugador* propietario = celda.getPropietario();
                // Buscar índice del jugador en la lista
                Nodo4<Jugador*>* jPtr = jugadores.obtenerCabeza();
                Nodo4<int>* cPtr = conteos.obtenerCabeza();
                while (jPtr && cPtr) {
                    if (jPtr->obtenerDato() == propietario) {
                        cPtr->obtenerDato() += 1;
                        break;
                    }
                    jPtr = jPtr->obtenerDerecha();
                    cPtr = cPtr->obtenerDerecha();
                }
            }
            celdaPtr = celdaPtr->obtenerDerecha();
        }
        filaCelda = filaCelda->obtenerAbajo();
    }

    // Buscar máximo
    int maxCuadros = 0;
    Nodo4<int>* cPtr = conteos.obtenerCabeza();
    while (cPtr) {
        if (cPtr->obtenerDato() > maxCuadros) {
            maxCuadros = cPtr->obtenerDato();
        }
        cPtr = cPtr->obtenerDerecha();
    }

    // Filtrar ganadores
    ListaEnlazada<Jugador*> ganadores;
    Nodo4<Jugador*>* jPtr = jugadores.obtenerCabeza();
    cPtr = conteos.obtenerCabeza();
    while (jPtr && cPtr) {
        if (cPtr->obtenerDato() == maxCuadros) {
            ganadores.insertarFinal(jPtr->obtenerDato());
        }
        jPtr = jPtr->obtenerDerecha();
        cPtr = cPtr->obtenerDerecha();
    }

    std::cout << "Filtrado por cuadros capturados: " << maxCuadros << " cuadros." << std::endl;
    return ganadores;
}

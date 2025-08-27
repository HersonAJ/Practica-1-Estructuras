#include "CondicionesDeVictoria.h"
#include <iostream>

ListaEnlazada<Jugador*> filtrarPorFilasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    ListaEnlazada<int> filasGanadas;
    Nodo4<Jugador*>* jugadorPtr = jugadores.obtenerCabeza();
    while (jugadorPtr) {
        filasGanadas.insertarFinal(0);
        jugadorPtr = jugadorPtr->obtenerDerecha();
    }

    Nodo4<Celda>* filaCelda = tablero->getInicioCeldas();
    int totalFilas = 0;

    while (filaCelda) {
        totalFilas++;

        ListaEnlazada<int> conteoFila;
        jugadorPtr = jugadores.obtenerCabeza();
        while (jugadorPtr) {
            conteoFila.insertarFinal(0);
            jugadorPtr = jugadorPtr->obtenerDerecha();
        }

        Nodo4<Celda>* celdaPtr = filaCelda;
        while (celdaPtr) {
            Celda& celda = celdaPtr->obtenerDato();
            if (celda.estaCompletada()) {
                Jugador* propietario = celda.getPropietario();

                Nodo4<Jugador*>* jPtr = jugadores.obtenerCabeza();
                Nodo4<int>* cPtr = conteoFila.obtenerCabeza();
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

        int maxCeldas = -1;
        int cantidadMaximos = 0;
        Nodo4<int>* cPtr = conteoFila.obtenerCabeza();
        while (cPtr) {
            if (cPtr->obtenerDato() > maxCeldas) {
                maxCeldas = cPtr->obtenerDato();
                cantidadMaximos = 1;
            } else if (cPtr->obtenerDato() == maxCeldas) {
                cantidadMaximos++;
            }
            cPtr = cPtr->obtenerDerecha();
        }

        if (cantidadMaximos == 1 && maxCeldas > 0) {
            Nodo4<int>* fPtr = filasGanadas.obtenerCabeza();
            cPtr = conteoFila.obtenerCabeza();
            while (fPtr && cPtr) {
                if (cPtr->obtenerDato() == maxCeldas) {
                    fPtr->obtenerDato() += 1;
                    break;
                }
                fPtr = fPtr->obtenerDerecha();
                cPtr = cPtr->obtenerDerecha();
            }
        }

        filaCelda = filaCelda->obtenerAbajo();
    }

    std::cout << "Total de filas evaluadas: " << totalFilas << std::endl;

    int maxFilas = -1;
    Nodo4<int>* fPtr = filasGanadas.obtenerCabeza();
    while (fPtr) {
        if (fPtr->obtenerDato() > maxFilas) {
            maxFilas = fPtr->obtenerDato();
        }
        fPtr = fPtr->obtenerDerecha();
    }

    ListaEnlazada<Jugador*> ganadores;
    jugadorPtr = jugadores.obtenerCabeza();
    fPtr = filasGanadas.obtenerCabeza();
    while (jugadorPtr && fPtr) {
        if (fPtr->obtenerDato() == maxFilas) {
            ganadores.insertarFinal(jugadorPtr->obtenerDato());
        }
        jugadorPtr = jugadorPtr->obtenerDerecha();
        fPtr = fPtr->obtenerDerecha();
    }

    std::cout << "Filtrado por filas ganadas: " << maxFilas << " filas." << std::endl;
    return ganadores;
}

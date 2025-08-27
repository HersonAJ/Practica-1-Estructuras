#include "CondicionesDeVictoria.h"
#include <iostream>

ListaEnlazada<Jugador*> filtrarPorColumnasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    ListaEnlazada<int> columnasGanadas;
    Nodo4<Jugador*>* jugadorPtr = jugadores.obtenerCabeza();
    while (jugadorPtr) {
        columnasGanadas.insertarFinal(0);
        jugadorPtr = jugadorPtr->obtenerDerecha();
    }

    Nodo4<Celda>* columnaInicio = tablero->getInicioCeldas();
    int totalColumnas = 0;

    while (columnaInicio) {
        totalColumnas++;

        ListaEnlazada<int> conteoColumna;
        jugadorPtr = jugadores.obtenerCabeza();
        while (jugadorPtr) {
            conteoColumna.insertarFinal(0);
            jugadorPtr = jugadorPtr->obtenerDerecha();
        }

        Nodo4<Celda>* celdaPtr = columnaInicio;
        while (celdaPtr) {
            Celda& celda = celdaPtr->obtenerDato();
            if (celda.estaCompletada()) {
                Jugador* propietario = celda.getPropietario();

                Nodo4<Jugador*>* jPtr = jugadores.obtenerCabeza();
                Nodo4<int>* cPtr = conteoColumna.obtenerCabeza();
                while (jPtr && cPtr) {
                    if (jPtr->obtenerDato() == propietario) {
                        cPtr->obtenerDato() += 1;
                        break;
                    }
                    jPtr = jPtr->obtenerDerecha();
                    cPtr = cPtr->obtenerDerecha();
                }
            }
            celdaPtr = celdaPtr->obtenerAbajo();
        }

        int maxCeldas = -1;
        int cantidadMaximos = 0;
        Nodo4<int>* cPtr = conteoColumna.obtenerCabeza();
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
            Nodo4<int>* gPtr = columnasGanadas.obtenerCabeza();
            cPtr = conteoColumna.obtenerCabeza();
            while (gPtr && cPtr) {
                if (cPtr->obtenerDato() == maxCeldas) {
                    gPtr->obtenerDato() += 1;
                    break;
                }
                gPtr = gPtr->obtenerDerecha();
                cPtr = cPtr->obtenerDerecha();
            }
        }

        columnaInicio = columnaInicio->obtenerDerecha();
    }

    std::cout << "Total de columnas evaluadas: " << totalColumnas << std::endl;

    int maxColumnas = -1;
    Nodo4<int>* gPtr = columnasGanadas.obtenerCabeza();
    while (gPtr) {
        if (gPtr->obtenerDato() > maxColumnas) {
            maxColumnas = gPtr->obtenerDato();
        }
        gPtr = gPtr->obtenerDerecha();
    }

    ListaEnlazada<Jugador*> ganadores;
    jugadorPtr = jugadores.obtenerCabeza();
    gPtr = columnasGanadas.obtenerCabeza();
    while (jugadorPtr && gPtr) {
        if (gPtr->obtenerDato() == maxColumnas) {
            ganadores.insertarFinal(jugadorPtr->obtenerDato());
        }
        jugadorPtr = jugadorPtr->obtenerDerecha();
        gPtr = gPtr->obtenerDerecha();
    }

    std::cout << "Filtrado por columnas ganadas: " << maxColumnas << " columnas." << std::endl;
    return ganadores;
}

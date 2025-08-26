#include "CondicionesVictoria.h"
#include <iostream>

CondicionesVictoria::CondicionesVictoria(Tablero* tablero, ListaEnlazada<Jugador*>* jugadores) {
    this->tablero = tablero;
    this->jugadores = jugadores;
}

Jugador* CondicionesVictoria::obtenerGanador(Tablero* tablero) {
    ListaEnlazada<Jugador*>* candidatos = jugadores;

    // Primer filtro: por puntos
    candidatos = filtrarPorPuntos(candidatos);
    if (candidatos->obtenerCantidad() == 1) {
        return candidatos->obtenerCabeza()->obtenerDato();
    }

    // Segundo filtro: por cantidad de celdas capturadas
    ListaEnlazada<Jugador*> candidatosPorCuadros = filtrarPorCuadradosTotales(tablero, *candidatos);
    if (candidatosPorCuadros.obtenerCantidad() == 1) {
        return candidatosPorCuadros.obtenerCabeza()->obtenerDato();
    }

    std::cout << "Empate técnico: no se pudo determinar un ganador por puntos ni por cuadros." << std::endl;
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

ListaEnlazada<Jugador*> CondicionesVictoria::filtrarPorCuadradosTotales(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
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

    return ganadores;
}

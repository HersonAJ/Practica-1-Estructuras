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

ListaEnlazada<Jugador*> CondicionesVictoria::filtrarPorFilasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    // Inicializar contador de filas ganadas por jugador
    ListaEnlazada<int> filasGanadas;
    Nodo4<Jugador*>* jugadorPtr = jugadores.obtenerCabeza();
    while (jugadorPtr) {
        filasGanadas.insertarFinal(0); // todos empiezan con 0
        jugadorPtr = jugadorPtr->obtenerDerecha();
    }

    Nodo4<Celda>* filaCelda = tablero->getInicioCeldas();
    int totalFilas = 0;

    while (filaCelda) {
        totalFilas++;

        // Contador de celdas por jugador en esta fila
        ListaEnlazada<int> conteoFila;
        jugadorPtr = jugadores.obtenerCabeza();
        while (jugadorPtr) {
            conteoFila.insertarFinal(0);
            jugadorPtr = jugadorPtr->obtenerDerecha();
        }

        // Recorrer la fila actual
        Nodo4<Celda>* celdaPtr = filaCelda;
        while (celdaPtr) {
            Celda& celda = celdaPtr->obtenerDato();
            if (celda.estaCompletada()) {
                Jugador* propietario = celda.getPropietario();

                // Buscar índice del jugador
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

        // Determinar ganador de la fila
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

        // Si hay un único ganador, sumarle una fila ganada
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

    // Buscar máximo de filas ganadas
    int maxFilas = -1;
    Nodo4<int>* fPtr = filasGanadas.obtenerCabeza();
    while (fPtr) {
        if (fPtr->obtenerDato() > maxFilas) {
            maxFilas = fPtr->obtenerDato();
        }
        fPtr = fPtr->obtenerDerecha();
    }

    // Filtrar jugadores con ese máximo
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

ListaEnlazada<Jugador*> CondicionesVictoria::filtrarPorColumnasGanadas(Tablero* tablero, ListaEnlazada<Jugador*> jugadores) {
    ListaEnlazada<int> columnasGanadas;
    Nodo4<Jugador*>* jugadorPtr = jugadores.obtenerCabeza();
    while (jugadorPtr) {
        columnasGanadas.insertarFinal(0);
        jugadorPtr = jugadorPtr->obtenerDerecha();
    }

    Nodo4<Celda>* columnaInicio = tablero->getInicioCeldas();
    int totalColumnas = 0;

    // Avanzar por columnas desde la primera fila
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

        // Determinar ganador de la columna
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

    // Buscar máximo de columnas ganadas
    int maxColumnas = -1;
    Nodo4<int>* gPtr = columnasGanadas.obtenerCabeza();
    while (gPtr) {
        if (gPtr->obtenerDato() > maxColumnas) {
            maxColumnas = gPtr->obtenerDato();
        }
        gPtr = gPtr->obtenerDerecha();
    }

    // Filtrar jugadores con ese máximo
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

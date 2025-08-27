#include "DobleLinea.h"
#include "Juego.h"
#include <iostream>

void DobleLinea::aplicarEfecto(Juego* juego, Jugador* jugador) {
    juego->devolverTurno(jugador);
    std::cout << "Tienes un turno extra por el uso de el PowerUp DL Doble Linea. \n";
} 
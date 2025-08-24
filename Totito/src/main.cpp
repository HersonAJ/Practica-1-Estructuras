/*#include "Configuracion.h"
#include "Tablero.h"

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Tablero tablero(config.getFilas(), config.getColumnas());
    tablero.construir();
    tablero.mostrar();

    return 0;
}
    */

#include "Juego.h"
#include "Configuracion.h"
#include <iostream>
#include "Tablero.h"

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Tablero tablero(config.getFilas(), config.getColumnas());

    tablero.imprimir();

    std::cout << "\n====prueba de los vecinos del nodo=====\n";
    tablero.mostrarVecinos(0,0);
    tablero.mostrarVecinos(2, 2);
    tablero.mostrarVecinos(4, 4);


    return 0;
}

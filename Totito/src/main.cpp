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
using namespace std;

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Juego juego(&config);
    juego.inicializar();
    juego.jugar();

    return 0;
}


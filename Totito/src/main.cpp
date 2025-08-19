#include "Configuracion.h"
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
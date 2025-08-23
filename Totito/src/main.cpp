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

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Juego juego(config.getFilas(), config.getColumnas());
    juego.iniciar();

    std::string c1, c2;
    std::cout << "Ingrese primera coordenada (ej: A0): ";
    std::cin >> c1;
    std::cout << "Ingrese segunda coordenada (ej: A1): ";
    std::cin >> c2;

    juego.colocarLinea(c1, c2);

    return 0;
}

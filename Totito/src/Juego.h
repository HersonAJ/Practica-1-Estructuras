#ifndef JUEGO_H
#define JUEGO_h

#include "Tablero.h"
#include <string>

class Juego {
    private:
    Tablero tablero;

    public:
    Juego(int filas, int columnas);

    void iniciar();
    void colocarLinea(const std::string& coord1, const std::string& coord2);

    private:
    Punto* parseCoordenada(const std::string& coord);
};

#endif
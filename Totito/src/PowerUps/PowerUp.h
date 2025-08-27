#ifndef POWERUP_H
#define POWERUP_H

#include <string>

class Jugador;

class PowerUp {
    protected:
    std::string simbolo;
    bool afectaLinea;

    public:
    //constructor base
    PowerUp(const std::string& simbolo, bool afectaLinea) : simbolo(simbolo), afectaLinea(afectaLinea) {}

    //destructor
    virtual ~PowerUp() {}

    //getters
    std::string getSimbolo() const {
        return simbolo;
    }

    bool getAfectaLinea() const {
        return afectaLinea;
    }

    virtual void activar() = 0;

    virtual void aplicarEfecto(class Juego* juego, Jugador* jugador) = 0;
};

#endif
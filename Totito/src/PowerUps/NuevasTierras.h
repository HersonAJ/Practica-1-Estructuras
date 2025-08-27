#ifndef NUEVASTIERRAS_H
#define NUEVASTIERRAS_H

#include "PowerUp.h"
#include <iostream>

class NuevasTierras : public PowerUp {
    public:
    NuevasTierras() : PowerUp("NT", true) {}

    //sobrescribiendo el metodo virtual
    void aplicarEfecto(class Juego* juego, Jugador* jugador) override;

    void activar() override;
};

#endif
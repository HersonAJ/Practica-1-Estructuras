#ifndef EXPLOSIVO_H
#define EXPLOSIVO_H

#include "PowerUp.h"
#include <string>

class Juego;
class Jugador;

class Explosivo : public PowerUp {
public:
    // Constructor
    Explosivo();
    
    // Destructor
    virtual ~Explosivo() override;
    
    // Implementación de métodos virtuales puros
    virtual void activar() override;
    virtual void aplicarEfecto(Juego* juego, Jugador* jugador) override;
};

#endif
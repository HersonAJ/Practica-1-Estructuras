#ifndef JUEGO_H
#define JUEGO_H

#include "Configuracion.h"
#include "Tablero.h"
#include "GestorLineas.h"
#include "Cola.h"

class Juego {
private:
    Configuracion* config;
    Tablero* tablero;
    GestorLineas* gestor;
    Cola<Jugador> colaTurnos; // cola de jugadores

public:
    Juego(Configuracion* config);
    ~Juego();

    void inicializar();
    void jugar(); // bucle principal
};

#endif

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
    void devolverTurno(Jugador* jugador);
    void expandirTablero(int fila, int columna, int direccion); //metodo para nuevas tierras

    int getFilas() const;
    int getColumnas() const;
    bool estaEnBorde(int fila, int columna) const;
    void expandirArriba();
    void expandirAbajo();
    void expandirIzquierda();
    void expandirDerecha();
    bool parseCoordenada(const std::string& coord, int& fila, int& col);
};

#endif

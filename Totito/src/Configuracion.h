#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "Punto.h"
#include <iostream>

class Configuracion {
private:
    int filas;
    int columnas;
    Punto* inicio; // Primer punto del tablero (arriba-izquierda)

public:
    Configuracion();
    ~Configuracion();

    void pedirDatos();
    void construirTablero();
    void mostrarTableroVacio() const;

    // Limpieza de memoria
    void liberarMemoria();
};

#endif // CONFIGURACION_H

#ifndef LINEA_H
#define LINEA_H

#include <string>

class Punto;  

// Orientación de la línea
enum class Orientacion { HORIZONTAL, VERTICAL };

class Linea {
private:
    Punto* p1;
    Punto* p2;
    Orientacion orientacion;
    bool colocada;
    char jugadorColoco;

public:
    // Constructor
    Linea(Punto* inicio, Punto* fin, Orientacion ori);

    // Getters
    Punto* getP1() const;
    Punto* getP2() const;
    Orientacion getOrientacion() const;
    bool estaColocada() const;
    char getJugadorColoco() const;

    // Acciones
    void colocar(char inicialJugador);
    void quitar();

    // Representación visual
    std::string toString() const;
};

#endif // LINEA_H

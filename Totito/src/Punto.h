#ifndef PUNTO_H
#define PUNTO_H

#include <string>

class Linea;

class Punto {
private:
    int row;  
    int col;  
    bool exists; 

    // Vecinos directos (malla enlazada)
    Punto* up;
    Punto* down;
    Punto* left;
    Punto* right;

    // Líneas incidentes
    Linea* lineaArriba;
    Linea* lineaAbajo;
    Linea* lineaIzquierda;
    Linea* lineaDerecha;

public:
    // Constructor
    Punto(int fila, int columna);

    // Getters y Setters
    int getRow() const;
    int getCol() const;
    bool isActive() const;
    void setActive(bool estado);

    // Vecinos
    void setUp(Punto* p);
    void setDown(Punto* p);
    void setLeft(Punto* p);
    void setRight(Punto* p);

    Punto* getUp() const;
    Punto* getDown() const;
    Punto* getLeft() const;
    Punto* getRight() const;

    // Líneas incidentes
    void setLineaArriba(Linea* l);
    void setLineaAbajo(Linea* l);
    void setLineaIzquierda(Linea* l);
    void setLineaDerecha(Linea* l);

    Linea* getLineaArriba() const;
    Linea* getLineaAbajo() const;
    Linea* getLineaIzquierda() const;
    Linea* getLineaDerecha() const;

    std::string toString() const;
};

#endif // PUNTO_H

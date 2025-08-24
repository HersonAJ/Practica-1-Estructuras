#ifndef PUNTO_H
#define PUNTO_H

class Punto {
private:
    int fila;
    int columna;

public:
    Punto(int fila = 0, int columna = 0);

    int getFila() const;
    int getColumna() const;

    char simbolo() const; // representación en el tablero
};

#endif

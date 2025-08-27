#ifndef PUNTO_H
#define PUNTO_H

class Punto {
private:
    int fila;
    int columna;
    bool destruido; // nueva propiedad para explosion

public:
    Punto(int fila = 0, int columna = 0);

    //metodos 
    void destruir();
    bool estaDestruido() const;

    int getFila() const;
    int getColumna() const;

    char simbolo() const; // representación en el tablero
};

#endif

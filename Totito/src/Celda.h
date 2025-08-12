#ifndef CELDA_H
#define CELDA_H

#include <string>

class Linea;

// Tipos de PowerUp que pueden estar en una celda
enum class TipoPowerUpCelda {
    NINGUNO,
    DL, TS, BL, PS, LS, ES, UF, AC, NT, EX
};

class Celda {
private:
    int row; 
    int col; 

    // Líneas que forman el cuadro
    Linea* lineaArriba;
    Linea* lineaAbajo;
    Linea* lineaIzquierda;
    Linea* lineaDerecha;

    // Estado de la celda
    bool completada;
    char propietario; // inicial del jugador

    // PowerUp (si existe dentro de la celda)
    TipoPowerUpCelda powerUp;
    bool powerUpVisible;

public:
    Celda(int fila, int columna);

    // Getters y setters
    int getRow() const;
    int getCol() const;
    bool estaCompletada() const;
    char getPropietario() const;

    void setPropietario(char inicialJugador);
    void setCompletada(bool estado);

    // Asignación de líneas
    void setLineaArriba(Linea* l);
    void setLineaAbajo(Linea* l);
    void setLineaIzquierda(Linea* l);
    void setLineaDerecha(Linea* l);

    Linea* getLineaArriba() const;
    Linea* getLineaAbajo() const;
    Linea* getLineaIzquierda() const;
    Linea* getLineaDerecha() const;

    // PowerUp
    void asignarPowerUp(TipoPowerUpCelda tipo, bool visible = true);
    TipoPowerUpCelda getPowerUp() const;
    bool isPowerUpVisible() const;
    void setPowerUpVisible(bool estado);


    bool verificarCompleta() const;


    std::string toString() const;
};

#endif // CELDA_H

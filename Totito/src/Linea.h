#ifndef LINEA_H
#define LINEA_H

#include <string>

class Punto;
class Celda;

//orientacion
enum class Orientacion{
    HORIZONTAL, VERTICAL
};

enum class TipoPowerUp {
    NINGUNO,
    DL, //DOBLE LINEA
    TS, //TRAMPA SECRETA
    BL, //BLOQUEO
    PS, //PASE
    LS, //LLAVE SECRETA
    ES, //ESCURRIDIZO
    UF, //UNION A FUTURO
    AC, //A QUE COSTO
    NT, //NUEVAS TIERRAS
    EX //EXPLOSIVOS
};

class Linea {
    private:
    Punto* p1;
    Punto* p2;

    Orientacion orientacion;
    bool colocada;
    char jugadorColoco;

    TipoPowerUp powerUp;
    bool powerUpVisible;

    Celda* celdaA;
    Celda* celdaB;

    public:
    Linea(Punto* inicio, Punto* fin, Orientacion ori);

    Punto* getP1() const;
    Punto* getP2() const;
    Orientacion getOrientacion() const;

    bool estaColocada() const;
    char getJugadorColoco() const;

    // Setters 
    void colocar(char inicialJugador);
    void quitar();

    // PowerUp
    void asignarPowerUp(TipoPowerUp tipo, bool visible = true);
    TipoPowerUp getPowerUp() const;
    bool isPowerUpVisible() const;
    void setPowerUpVisible(bool estado);

    // Celdas adyacentes
    void setCeldaA(Celda* c);
    void setCeldaB(Celda* c);
    Celda* getCeldaA() const;
    Celda* getCeldaB() const;

    std::string toString() const;

};

#endif
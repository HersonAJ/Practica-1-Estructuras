#ifndef JUGADOR_H
#define JUGADOR_H

#include "Linea.h"
#include <string>

#define MAX_POWERUPS 10
#define COLOR_DEFAULT 0

class Jugador {
private:
    std::string nombre;
    char inicial;
    int puntos;
    //TipoPowerUp powerUps[MAX_POWERUPS];
    int cantidadPowerUps;
    int color;

    // Método privado para calcular inicial 
    char calcularInicial(const std::string& nombre);

public:
    Jugador(const std::string& nombre, int color = COLOR_DEFAULT);
    
    // Getters
    const std::string& getNombre() const;
    char getInicial() const;
    int getPuntos() const;
    int getColor() const;
    int getCantidadPowerUps() const;
    
    // Manejo de puntos
    void sumarPunto();
    void restarPunto();
    
    // Manejo de power-ups
    //bool agregarPowerUp(TipoPowerUp powerUp);
    //TipoPowerUp usarPowerUp();
    bool tienePowerUps() const;
    //TipoPowerUp verSiguientePowerUp() const;
    
    // Método para cambiar color
    void setColor(int nuevoColor);
};

#endif // JUGADOR_H
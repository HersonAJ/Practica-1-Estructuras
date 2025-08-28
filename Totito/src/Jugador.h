#ifndef JUGADOR_H
#define JUGADOR_H

#include "Linea.h"
#include "Pila.h"
#include "PowerUps/PowerUp.h"
#include <string>

#define MAX_POWERUPS 10
#define COLOR_DEFAULT 0

class Jugador {
private:
    std::string nombre;
    char inicial;
    int puntos;
    Pila<PowerUp> pilaPowerUps; //pila personal del jugador
    int color;
    int powerUpsUsados;

    // Método privado para calcular inicial 
    char calcularInicial(const std::string& nombre);

public:
    Jugador(const std::string& nombre, int color = COLOR_DEFAULT);
    
    // Getters
    const std::string& getNombre() const;
    char getInicial() const;
    int getPuntos() const;
    int getColor() const;
    int getPowerUpsUsados() const;
    
    // Manejo de puntos
    void sumarPunto();
    void restarPunto();
    
    // Manejo de power-ups
    void agregarPowerUp(PowerUp* powerUp);
    PowerUp* usarPowerUp();
    bool tienePowerUps() const;
    PowerUp* verSiguientePowerUp() const;
    void mostrarPowerUps() const;
    
    // Método para cambiar color
    void setColor(int nuevoColor);
};

#endif // JUGADOR_H
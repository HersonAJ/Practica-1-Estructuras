#include "Jugador.h"
#include <cctype>
#include <iostream>

//metodo para calcular la inicial 
char Jugador::calcularInicial(const std::string& nombre) {
    if(nombre.empty()) return '?' ;

    for(char c: nombre) {
        if(isalpha(c)) {
            return toupper(c);
        }
    }
    return '?';
}

//constructor
Jugador::Jugador(const std::string& nombre, int color)
    : nombre(nombre),
      inicial(calcularInicial(nombre)),
      puntos(0),
      color(color) {
}


//getters y setters
const std::string& Jugador::getNombre() const { return nombre;} 
char Jugador::getInicial() const { return inicial; }
int Jugador::getPuntos() const { return puntos; }
int Jugador::getColor() const { return color; }

void Jugador::sumarPunto() {
    puntos++;
}
 
void Jugador::restarPunto() {
    if(puntos > 0) {
        puntos--;
    }
}

//manejo de powerups
void Jugador::agregarPowerUp(PowerUp* powerUp) {
    if (powerUp != nullptr) {
        pilaPowerUps.apilar(powerUp);
    }
}

PowerUp* Jugador::usarPowerUp() {
    return pilaPowerUps.desapilar();
}
bool Jugador::tienePowerUps() const {
    return !pilaPowerUps.estaVacia();
}

PowerUp* Jugador::verSiguientePowerUp() const {
    return pilaPowerUps.verTope();
}

// Color del jugador
void Jugador::setColor(int nuevoColor) {
    color = nuevoColor;
}

void Jugador::mostrarPowerUps() const {
    if (pilaPowerUps.estaVacia()) {
        std::cout  << "No tienes PowerUps. \n";
        return;
    }
    std::cout << "  - PowerUps disponibles: ";
    pilaPowerUps.imprimirPila();
}
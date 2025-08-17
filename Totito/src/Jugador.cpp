#include "Jugador.h"
#include <cctype>

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
      cantidadPowerUps(0),
      color(color) {
}


//getters y setters
const std::string& Jugador::getNombre() const { return nombre;} 
char Jugador::getInicial() const { return inicial; }
int Jugador::getPuntos() const { return puntos; }
int Jugador::getColor() const { return color; }
int Jugador:: getCantidadPowerUps() const { return cantidadPowerUps; }

void Jugador::sumarPunto() {
    puntos++;
}
 
void Jugador::restarPunto() {
    if(puntos > 0) {
        puntos--;
    }
}

//manejo de puntos
bool Jugador::agregarPowerUp(TipoPowerUp powerUp) {
    if (cantidadPowerUps >= MAX_POWERUPS) {
        return false;
    }
    powerUps[cantidadPowerUps++] = powerUp;
    return true;
}


TipoPowerUp Jugador::usarPowerUp() {
    if(cantidadPowerUps <= 0) return TipoPowerUp::NINGUNO;
    return powerUps[--cantidadPowerUps];
}

bool Jugador::tienePowerUps() const {
    return cantidadPowerUps > 0;
}

TipoPowerUp Jugador::verSiguientePowerUp() const {
    if(cantidadPowerUps <= 0) return TipoPowerUp::NINGUNO;
    return powerUps[cantidadPowerUps - 1];
}

//color del jugador
void Jugador::setColor(int nuevoColor) {
    color = nuevoColor;
}

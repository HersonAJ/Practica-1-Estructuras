/*#include "Juego.h"
#include <iostream>
#include <cctype>

// Constructor
Juego::Juego(int filas, int columnas) : tablero(filas, columnas) {
    tablero.construir();
}

// Inicia el juego mostrando el tablero vacío
void Juego::iniciar() {
    tablero.mostrar();
}

// Recibe dos coordenadas, coloca la línea si existe y actualiza el tablero
void Juego::colocarLinea(const std::string& coord1, const std::string& coord2) {
    Punto* p1 = parseCoordenada(coord1);
    Punto* p2 = parseCoordenada(coord2);

    if (!p1 || !p2) {
        std::cout << "Coordenadas inválidas.\n";
        return;
    }

    Linea* l = tablero.buscarLinea(p1, p2);
    if (!l) {
        std::cout << "No existe línea entre esos puntos.\n";
        return;
    }

    if (l->estaColocada()) {
        std::cout << "Esa línea ya está ocupada.\n";
        return;
    }

    l->colocar('*'); // por ahora siempre coloca con un marcador fijo

    tablero.mostrar();
}

// Convierte coordenadas tipo "A0" en Punto*
Punto* Juego::parseCoordenada(const std::string& coord) {
    if (coord.size() < 2) return nullptr;

    char letra = std::toupper(coord[0]);
    int col = letra - 'A';

    int fila = coord[1] - '0';
    if (coord.size() == 3 && isdigit(coord[2])) { // soportar dos dígitos (ej: A10)
        fila = fila * 10 + (coord[2] - '0');
    }

    return tablero.buscarPunto(fila, col);
}
*/
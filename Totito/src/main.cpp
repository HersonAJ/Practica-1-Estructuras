/*#include "Configuracion.h"
#include "Tablero.h"

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Tablero tablero(config.getFilas(), config.getColumnas());
    tablero.construir();
    tablero.mostrar();

    return 0;
}
    */

#include "Juego.h"
#include "Configuracion.h"
#include <iostream>
#include "Tablero.h"

using namespace std;

// función auxiliar: convierte "A0" a fila y columna
bool parseCoordenada(const string& coord, int& fila, int& col) {
    if (coord.size() < 2) return false;
    col = coord[0] - 'A';  // letra → columna
    fila = stoi(coord.substr(1)); // número → fila
    return true;
}

int main() {
    Configuracion config;
    config.pedirDatos();
    config.pedirJugadores();
    config.mostrarJugadores();

    Tablero tablero(config.getFilas(), config.getColumnas());

    tablero.imprimir();

    cout << "\n==== prueba de los vecinos del nodo =====\n";
    tablero.mostrarVecinos(0,0);
    tablero.mostrarVecinos(2, 2);
    tablero.mostrarVecinos(4, 4);

    // Generar todas las líneas posibles
    tablero.generarLineas();

    // Pedir coordenadas al usuario
    string c1, c2;
    cout << "\nIngrese primera coordenada (ej: A0): ";
    cin >> c1;
    cout << "Ingrese segunda coordenada (ej: A1): ";
    cin >> c2;

    int f1, col1, f2, col2;
    if (parseCoordenada(c1, f1, col1) && parseCoordenada(c2, f2, col2)) {
    
        tablero.colocarLinea(f1, col1, f2, col2, 'H'); 
    } else {
        cout << "Coordenadas inválidas.\n";
    }

    // Imprimir tablero actualizado
    cout << "\n=== Tablero actualizado ===\n";
    tablero.imprimir();

    // Mostrar todas las líneas de prueba
    cout << "\n=== Contenido de la lista de líneas ===\n";
    tablero.mostrarLineas();

    return 0;
}

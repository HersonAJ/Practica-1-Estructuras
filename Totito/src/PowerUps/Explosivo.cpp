#include "Explosivo.h"
#include "Juego.h"
#include "Jugador.h"
#include "Tablero.h"
#include <iostream>
#include <limits>
Explosivo::Explosivo() 
    : PowerUp("EX", false) { // "EX" como símbolo, no afecta línea directamente
}

Explosivo::~Explosivo() {
    // Destructor vacio porque si elimino dejo las referencias del nodo en nullptr y da error
}

void Explosivo::activar() {
    // Método de activación básico
    std::cout << "PowerUp Explosivo activado - Listo para usar" << std::endl;
}

void Explosivo::aplicarEfecto(Juego* juego, Jugador* jugador) {
    if (!juego || !jugador) {
        std::cout << "Error: Juego o Jugador no válido" << std::endl;
        return;
    }
    
    std::cout << "\n " << jugador->getNombre() << " usa POWER-UP EXPLOSIVO!" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // Mostrar el tablero actual para referencia
    Tablero* tablero = juego->obtenerTablero();
    if (tablero) {
        tablero->imprimir();
    }
    
    std::cout << "Selecciona un punto para destruir (formato: fila columna)" << std::endl;
    std::cout << "Ejemplo: '1 2' para el punto en fila 1, columna 2" << std::endl;
    std::cout << "Coordenadas: ";
    
    int fila, columna;
    std::cin >> fila >> columna;
    
    // Validar coordenadas
    if (tablero) {
        if (fila >= 0 && columna >= 0 && 
            fila < tablero->getFilas() && columna < tablero->getColumnas()) {
            
            // Llamar al método del tablero para explotar el punto
            tablero->explotarPunto(fila, columna);
            
            std::cout << "Efecto de explosivo aplicado correctamente" << std::endl;
            
        } else {
            std::cout << " Error: Coordenadas fuera de rango del tablero" << std::endl;
            std::cout << "El tablero tiene " << tablero->getFilas() << " filas y " 
                      << tablero->getColumnas() << " columnas" << std::endl;
        }
    } else {
        std::cout << "Error: No se pudo acceder al tablero" << std::endl;
    }
    
    std::cout << "==============================================" << std::endl;
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
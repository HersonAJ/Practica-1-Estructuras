#include "GestorLineas.h"
#include <iostream>

GestorLineas::GestorLineas(ListaEnlazada<Linea*>* lineas, Tablero* tablero)
    : lineas(lineas), tablero(tablero) {}

// Buscar una línea entre dos puntos
Linea* GestorLineas::buscarLinea(int fila1, int col1, int fila2, int col2) const {
    Nodo4<Linea*>* lineaPtr = lineas->obtenerCabeza();
    while (lineaPtr) {
        Linea* l = lineaPtr->obtenerDato();
        
        // Verificar si la línea conecta los puntos especificados
        if ((l->getP1()->getFila() == fila1 && l->getP1()->getColumna() == col1 &&
             l->getP2()->getFila() == fila2 && l->getP2()->getColumna() == col2) ||
            (l->getP1()->getFila() == fila2 && l->getP1()->getColumna() == col2 &&
             l->getP2()->getFila() == fila1 && l->getP2()->getColumna() == col1)) {
            
            // Verificación adicional: puntos no destruidos
            if (l->getP1()->estaDestruido() || l->getP2()->estaDestruido()) {
                lineaPtr = lineaPtr->obtenerDerecha();
                continue; // Saltar líneas con puntos destruidos
            }
            
            return l;
        }
        lineaPtr = lineaPtr->obtenerDerecha();
    }
    return nullptr;
}

// Colocar una línea y verificar celdas
bool GestorLineas::colocarLinea(int f1, int c1, int f2, int c2, Jugador* jugador) {
    // Obtener los NODOS primero
    Nodo4<Punto>* nodo1 = tablero->buscarPunto(f1, c1);
    Nodo4<Punto>* nodo2 = tablero->buscarPunto(f2, c2);
    
    if (!nodo1 || !nodo2) {
        std::cout << "Error: Coordenadas no válidas.\n";
        return false;
    }
    
    //Obtener los PUNTOS desde los nodos y luego verificar
    Punto& punto1 = nodo1->obtenerDato(); 
    Punto& punto2 = nodo2->obtenerDato();
    
    if (punto1.estaDestruido() || punto2.estaDestruido()) {  //verificacion para po poder poner linea si el estado del punto es destruido
        std::cout << "No se puede colocar línea - Puntos destruidos.\n";
        std::cout << "Punto (" << f1 << "," << c1 << "): " 
                  << (punto1.estaDestruido() ? "DESTRUIDO" : "OK") << "\n";
        std::cout << "Punto (" << f2 << "," << c2 << "): " 
                  << (punto2.estaDestruido() ? "DESTRUIDO" : "OK") << "\n";
        return false;
    }
    
    Linea* l = buscarLinea(f1, c1, f2, c2);
    if (!l) {
        std::cout << "No existe una línea entre esas coordenadas.\n";
        return false;
    }
    
    if (l->estaColocada()) {
        std::cout << "Esa línea ya está colocada. Intenta otra en el siguiente turno.\n";
        return false;
    }

    l->colocar(jugador->getInicial());
    std::cout << "Línea colocada entre (" << f1 << "," << c1 
              << ") y (" << f2 << "," << c2 << ")\n";
    tablero->verificarCeldasPorLinea(l, jugador);
    return true;
}

// Mostrar todas las líneas
void GestorLineas::mostrarLineas() const {
    Nodo4<Linea*>* actual = lineas->obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        std::cout << "(" << l->getP1()->getFila() << "," << l->getP1()->getColumna()
                  << ") <-> (" << l->getP2()->getFila() << "," << l->getP2()->getColumna()
                  << ") "
                  << (l->estaColocada() ? "[X]" : "[ ]")
                  << " " << l->toString()
                  << "\n";
        actual = actual->obtenerDerecha();
    }
}

bool GestorLineas::todasLasLineasColocadas() const {
    Nodo4<Linea*>* actual = lineas->obtenerCabeza();
    while (actual) {
        if (!actual->obtenerDato()->estaColocada()) {
            return false;
        }
        actual = actual->obtenerDerecha();
    }
    return true;
}

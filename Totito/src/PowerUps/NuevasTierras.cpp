#include "NuevasTierras.h"
#include "Juego.h" 

void NuevasTierras::aplicarEfecto(Juego* juego, Jugador* jugador) {
    std::string entrada1;
    int f1, c1;

    // 1. Solicitar una coordenada en el borde del tablero
    std::cout << "Has usado el PowerUp 'Nuevas Tierras'." << std::endl;
    std::cout << "Ingresa una coordenada de punto en el borde derecho o inferior del tablero (ej: A0): ";
    std::cin >> entrada1;
    
    // 2. Validar la coordenada
    if (!juego->parseCoordenada(entrada1, f1, c1)) {
        std::cout << "Coordenada inválida. No se aplica el PowerUp." << std::endl;
        return;
    }

    // 3. Determinar la dirección de expansión
    int filas = juego->getFilas();
    int columnas = juego->getColumnas();
    
    // Validar si la coordenada está en el borde o esquina
    if (!juego->estaEnBorde(f1, c1)) {
        std::cout << "El punto no está en el borde del tablero. No se aplica el PowerUp." << std::endl;
        return;
    }
    
    // Solo permitimos expandir abajo o a la derecha
    if (f1 == filas - 1 && c1 == columnas - 1) { // Esquina inferior derecha
        std::cout << "Estás en la esquina. ¿Deseas expandir hacia abajo (1) o a la derecha (2)? ";
        int opcion;
        std::cin >> opcion;
        if (opcion == 1) {
            juego->expandirAbajo();
        } else if (opcion == 2) {
            juego->expandirDerecha();
        } else {
            std::cout << "Opción inválida. No se aplica el PowerUp." << std::endl;
            return;
        }
    } else if (f1 == filas - 1) { // Borde inferior (no esquina)
        juego->expandirAbajo();
    } else if (c1 == columnas - 1) { // Borde derecho (no esquina)
        juego->expandirDerecha();
    } else {
        std::cout << "El punto no está en un borde que pueda ser expandido. No se aplica el PowerUp." << std::endl;
        return;
    }
    
    // 4. Devolver el turno extra al jugador
    std::cout << "¡El tablero ha sido expandido! Tienes un turno extra." << std::endl;
    juego->devolverTurno(jugador);
}

void NuevasTierras::activar() {

}
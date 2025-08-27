#include "Tablero.h"
#include "ListaEnlazada.h"
#include "Linea.h"
#include <iostream>
#include "PowerUps/DobleLinea.h"
#include <cstdlib> // para random
#include <ctime>
using namespace std;

Tablero::Tablero(int filas, int columnas)
    : filas(filas), columnas(columnas), inicio(nullptr) {

        std::cout << "DEBUG_TABLERO: constructor simplificado" << std::endl;
    crearMalla();
    generarLineas(); // Genera las líneas que pertenecen al tablero
    generarCeldas();
}

Tablero::~Tablero() {
    // Liberar memoria de la malla
    Nodo4<Punto>* filaPtr = inicio;
    while (filaPtr) {
        Nodo4<Punto>* colPtr = filaPtr;
        filaPtr = filaPtr->obtenerAbajo();
        while (colPtr) {
            Nodo4<Punto>* temp = colPtr;
            colPtr = colPtr->obtenerDerecha();
            delete temp;
        }
    }

    // Liberar memoria de las líneas
    Nodo4<Linea*>* lineaPtr = lineas.obtenerCabeza();
    while (lineaPtr) {
        delete lineaPtr->obtenerDato();
        lineaPtr = lineaPtr->obtenerDerecha();
    }
}

void Tablero::crearMalla() {
    if (filas <= 0 || columnas <= 0) {
        inicio = nullptr;
        return;
    }

    // Lista temporal de filas
    ListaEnlazada< ListaEnlazada<Punto>* > filasLista;

    // Crear cada fila
    for (int f = 0; f < filas; ++f) {
        auto* filaActual = new ListaEnlazada<Punto>();
        for (int c = 0; c < columnas; ++c) {
            filaActual->insertarFinal(Punto(f, c));
        }
        filasLista.insertarFinal(filaActual);
    }

    // Enlazar verticalmente
    Nodo4< ListaEnlazada<Punto>* >* nodoFila = filasLista.obtenerCabeza();
    Nodo4< ListaEnlazada<Punto>* >* nodoFilaAbajo = nodoFila ? nodoFila->obtenerDerecha() : nullptr;

    while (nodoFila && nodoFilaAbajo) {
        Nodo4<Punto>* nodoCol = nodoFila->obtenerDato()->obtenerCabeza();
        Nodo4<Punto>* nodoColAbajo = nodoFilaAbajo->obtenerDato()->obtenerCabeza();

        while (nodoCol && nodoColAbajo) {
            nodoCol->establecerAbajo(nodoColAbajo);
            nodoColAbajo->establecerArriba(nodoCol);

            nodoCol = nodoCol->obtenerDerecha();
            nodoColAbajo = nodoColAbajo->obtenerDerecha();
        }

        // Avanzar UNA fila hacia abajo
        nodoFila = nodoFilaAbajo;
        nodoFilaAbajo = nodoFilaAbajo->obtenerDerecha();
    }

    // Guardar inicio (primer punto de la primera fila)
    if (filasLista.obtenerCabeza()) {
        inicio = filasLista.obtenerCabeza()->obtenerDato()->obtenerCabeza();
    }
}



void Tablero::generarLineas() {
    Nodo4<Punto>* filaPtr = inicio;

    while (filaPtr) {
        Nodo4<Punto>* colPtr = filaPtr;

        while (colPtr) {
            // Línea horizontal (punto con su derecha)
            if (colPtr->obtenerDerecha()) {
                Linea* l = new Linea(&(colPtr->obtenerDato()), &(colPtr->obtenerDerecha()->obtenerDato()), Orientacion::HORIZONTAL);
                lineas.insertarFinal(l);
            }
            // Línea vertical (punto con su abajo)
            if (colPtr->obtenerAbajo()) {
                Linea* l = new Linea(&(colPtr->obtenerDato()), &(colPtr->obtenerAbajo()->obtenerDato()), Orientacion::VERTICAL);
                lineas.insertarFinal(l);
            }
            colPtr = colPtr->obtenerDerecha();
        }
        filaPtr = filaPtr->obtenerAbajo();
    }
}

void Tablero::imprimir() const {
    cout << "    ";
    for (int c = 0; c < columnas -1; ++c) {
        cout << char('A' + c) << "   ";
    }
    cout << "\n\n";

    Nodo4<Celda>* filaCelda = inicioCeldas;
    Nodo4<Punto>* filaPunto = inicio;

    for (int f = 0; f < filas; ++f) {
        // Fila de puntos + horizontales
        cout << f << "   ";
        Nodo4<Punto>* colPunto = filaPunto;
        for (int c = 0; c < columnas; ++c) {
            cout << "o";
            if (c < columnas - 1) {
                cout << (existeLineaColocada(colPunto->obtenerDato().getFila(), colPunto->obtenerDato().getColumna(), colPunto->obtenerDerecha()->obtenerDato().getFila(), colPunto->obtenerDerecha()->obtenerDato().getColumna()) ? "---" : "   ");
            }
            colPunto = colPunto->obtenerDerecha();
        }
        cout << "\n";

        // Fila de verticales + iniciales de propietario
        if (f < filas - 1) {
            cout << "    ";
            Nodo4<Celda>* celdaPtr = filaCelda;
            Nodo4<Punto>* colPuntoVert = filaPunto;

            for (int c = 0; c < columnas; ++c) {
                // Línea vertical
                cout << (existeLineaColocada(colPuntoVert->obtenerDato().getFila(), colPuntoVert->obtenerDato().getColumna(), colPuntoVert->obtenerAbajo()->obtenerDato().getFila(), colPuntoVert->obtenerAbajo()->obtenerDato().getColumna()) ? "|" : " ");

                // Espacio central de la celda
                if (c < columnas - 1) {
                    if (celdaPtr) {
                        if (celdaPtr->obtenerDato().estaCompletada()) {
                             cout << " " << celdaPtr->obtenerDato().obtenerInicialPropietario() << " ";
                        } else if (celdaPtr->obtenerDato().getPowerUp() != nullptr) {
                            cout << " " << celdaPtr->obtenerDato().getPowerUp()->getSimbolo() << " ";
                        } else {
                            cout << "   ";
                        }
                    } else {
                        cout << "   ";
                    }
                    celdaPtr = celdaPtr ? celdaPtr->obtenerDerecha() : nullptr;
                }
                colPuntoVert = colPuntoVert->obtenerDerecha();
            }
            cout << "\n\n";
        }
        filaPunto = filaPunto->obtenerAbajo();
        if (filaCelda) filaCelda = filaCelda->obtenerAbajo();
    }
}

bool Tablero::existeLineaColocada(int f1, int c1, int f2, int c2) const {
    Nodo4<Linea*>* actual = lineas.obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        int lf1 = l->getP1()->getFila();
        int lc1 = l->getP1()->getColumna();
        int lf2 = l->getP2()->getFila();
        int lc2 = l->getP2()->getColumna();

        if (((lf1 == f1 && lc1 == c1 && lf2 == f2 && lc2 == c2) ||
             (lf1 == f2 && lc1 == c2 && lf2 == f1 && lc2 == c1))
            && l->estaColocada()) {
            return true;
        }
        actual = actual->obtenerDerecha();
    }
    return false;
}

//hasta aqui esta funcionando bien 
/*void Tablero::generarCeldas() {
    if (filas < 2 || columnas < 2) {
        inicioCeldas = nullptr;
        return;
    }

    Nodo4<Punto>* filaPunto = inicio;
    Nodo4<Celda>* filaCeldaInicio = nullptr;
    Nodo4<Celda>* filaCeldaAnterior = nullptr;

    // Lógica para colocar un PowerUp en una celda aleatoria
    srand(time(nullptr));
    int filaAleatoria = rand() % (filas - 1);
    int colAleatoria = rand() % (columnas - 1);
    bool powerUpColocado = false;

    for (int f = 0; f < filas - 1; ++f) {
        Nodo4<Punto>* colPunto = filaPunto;
        Nodo4<Celda>* nodoCeldaAnterior = nullptr;

        for (int c = 0; c < columnas - 1; ++c) {
            Punto* supIzq = &(colPunto->obtenerDato());
            Punto* supDer = &(colPunto->obtenerDerecha()->obtenerDato());
            Punto* infIzq = &(colPunto->obtenerAbajo()->obtenerDato());
            Punto* infDer = &(colPunto->obtenerAbajo()->obtenerDerecha()->obtenerDato());

            Linea* arriba = nullptr;
            Linea* derecha = nullptr;
            Linea* abajo = nullptr;
            Linea* izquierda = nullptr;

            Nodo4<Linea*>* actual = lineas.obtenerCabeza();
            while (actual) {
                Linea* l = actual->obtenerDato();
                if (l->conecta(supIzq, supDer)) arriba = l;
                else if (l->conecta(supDer, infDer)) derecha = l;
                else if (l->conecta(infIzq, infDer)) abajo = l;
                else if (l->conecta(supIzq, infIzq)) izquierda = l;
                actual = actual->obtenerDerecha();
            }

            Celda nuevaCelda(f, c, supIzq, supDer, infIzq, infDer, arriba, derecha, abajo, izquierda);
            Nodo4<Celda>* nodoCelda = new Nodo4<Celda>(nuevaCelda);

            // Se verifica si esta celda es la que debe contener el PowerUp
            if (!powerUpColocado && f == filaAleatoria && c == colAleatoria) {
                PowerUp* dl = new DobleLinea();
                nodoCelda->obtenerDato().asignarPowerUp(dl);
                powerUpColocado = true;
                std::cout << "PowerUp Doble Línea colocado en la celda: [" << f << "][" << c << "]" << std::endl;
            }

            if (nodoCeldaAnterior) {
                nodoCeldaAnterior->establecerDerecha(nodoCelda);
                nodoCelda->establecerIzquierda(nodoCeldaAnterior);
            } else if (!filaCeldaInicio) {
                filaCeldaInicio = nodoCelda;
            }

            if (filaCeldaAnterior) {
                Nodo4<Celda>* nodoArriba = filaCeldaAnterior;
                for (int k = 0; k < c; ++k) nodoArriba = nodoArriba->obtenerDerecha();
                nodoArriba->establecerAbajo(nodoCelda);
                nodoCelda->establecerArriba(nodoArriba);
            }

            nodoCeldaAnterior = nodoCelda;
            colPunto = colPunto->obtenerDerecha();
        }

        filaCeldaAnterior = filaCeldaInicio;
        for (int k = 0; k < f; ++k) filaCeldaAnterior = filaCeldaAnterior->obtenerAbajo();
        filaPunto = filaPunto->obtenerAbajo();
    }

    inicioCeldas = filaCeldaInicio;
}*/

void Tablero::generarCeldas() {
    if (filas < 2 || columnas < 2) {
        inicioCeldas = nullptr;
        return;
    }

    Nodo4<Punto>* filaPunto = inicio;
    Nodo4<Celda>* filaCeldaInicio = nullptr;
    Nodo4<Celda>* filaCeldaAnterior = nullptr;

    // Lógica para colocar un PowerUp en una celda aleatoria
    srand(time(nullptr));
    int filaAleatoria = rand() % (filas - 1);
    int colAleatoria = rand() % (columnas - 1);
    bool powerUpColocado = false;

    for (int f = 0; f < filas - 1; ++f) {
        Nodo4<Punto>* colPunto = filaPunto;
        Nodo4<Celda>* nodoCeldaAnterior = nullptr;

        for (int c = 0; c < columnas - 1; ++c) {
            Punto* supIzq = &(colPunto->obtenerDato());
            Punto* supDer = &(colPunto->obtenerDerecha()->obtenerDato());
            Punto* infIzq = &(colPunto->obtenerAbajo()->obtenerDato());
            Punto* infDer = &(colPunto->obtenerAbajo()->obtenerDerecha()->obtenerDato());

            Linea* arriba = nullptr;
            Linea* derecha = nullptr;
            Linea* abajo = nullptr;
            Linea* izquierda = nullptr;

            Nodo4<Linea*>* actual = lineas.obtenerCabeza();
            while (actual) {
                Linea* l = actual->obtenerDato();
                if (l->conecta(supIzq, supDer)) arriba = l;
                else if (l->conecta(supDer, infDer)) derecha = l;
                else if (l->conecta(infIzq, infDer)) abajo = l;
                else if (l->conecta(supIzq, infIzq)) izquierda = l;
                actual = actual->obtenerDerecha();
            }

            Celda nuevaCelda(f, c, supIzq, supDer, infIzq, infDer, arriba, derecha, abajo, izquierda);
            Nodo4<Celda>* nodoCelda = new Nodo4<Celda>(nuevaCelda);

            // Se verifica si esta celda es la que debe contener el PowerUp
            if (!powerUpColocado && f == filaAleatoria && c == colAleatoria) {
                PowerUp* dl = new DobleLinea();
                nodoCelda->obtenerDato().asignarPowerUp(dl);
                powerUpColocado = true;
                std::cout << "PowerUp Doble Línea colocado en la celda: [" << f << "][" << c << "]" << std::endl;
            }

            if (nodoCeldaAnterior) {
                nodoCeldaAnterior->establecerDerecha(nodoCelda);
                nodoCelda->establecerIzquierda(nodoCeldaAnterior);
            } else if (!filaCeldaInicio) {
                filaCeldaInicio = nodoCelda;
            }

            if (filaCeldaAnterior) {
                Nodo4<Celda>* nodoArriba = filaCeldaAnterior;
                for (int k = 0; k < c; ++k) nodoArriba = nodoArriba->obtenerDerecha();
                nodoArriba->establecerAbajo(nodoCelda);
                nodoCelda->establecerArriba(nodoArriba);
            }

            nodoCeldaAnterior = nodoCelda;
            colPunto = colPunto->obtenerDerecha();
        }

        filaCeldaAnterior = filaCeldaInicio;
        for (int k = 0; k < f; ++k) filaCeldaAnterior = filaCeldaAnterior->obtenerAbajo();
        filaPunto = filaPunto->obtenerAbajo();
    }

    inicioCeldas = filaCeldaInicio;
}

void Tablero::verificarCeldasPorLinea(Linea* linea, Jugador* jugador) {
    Nodo4<Celda>* filaCelda = inicioCeldas;
    while (filaCelda) {
        Nodo4<Celda>* celdaPtr = filaCelda;
        while (celdaPtr) {
            Celda& celda = celdaPtr->obtenerDato();
            if (celda.contieneLinea(linea) && !celda.estaCompletada()) {
                if (celda.verificarCompletada()) {
                    celda.capturar(jugador);
                    // Lógica para obtener el PowerUp si la celda lo tenía
                    PowerUp* p = celda.getPowerUp();
                    if (p != nullptr) {
                        jugador->agregarPowerUp(p);
                        celda.asignarPowerUp(nullptr);
                    }
                }
            }
            celdaPtr = celdaPtr->obtenerDerecha();
        }
        filaCelda = filaCelda->obtenerAbajo();
    }
}
//metodos auxiliares para pruebas
/*
//metodo de debug para ver enlazamiento
void Tablero::debugPuntosDeCelda(int filaCelda, int colCelda) const {
    // Navegar hasta la celda solicitada
    Nodo4<Celda>* filaPtr = inicioCeldas;
    for (int f = 0; f < filaCelda && filaPtr; ++f) {
        filaPtr = filaPtr->obtenerAbajo();
    }
    if (!filaPtr) {
        std::cout << "Fila de celda fuera de rango.\n";
        return;
    }

    Nodo4<Celda>* celdaPtr = filaPtr;
    for (int c = 0; c < colCelda && celdaPtr; ++c) {
        celdaPtr = celdaPtr->obtenerDerecha();
    }
    if (!celdaPtr) {
        std::cout << "Columna de celda fuera de rango.\n";
        return;
    }

    const Celda& celda = celdaPtr->obtenerDato();

    std::cout << "=== DEBUG: Celda (" << celda.getFila() << "," << celda.getColumna() << ") ===\n";

    // Esquinas
    for (int i = 0; i < 4; ++i) {
        Punto* p = celda.getEsquina(i);
        if (p) {
            std::cout << "Esquina[" << i << "]: (" << p->getFila() << "," << p->getColumna() << ")\n";
        } else {
            std::cout << "Esquina[" << i << "]: nullptr\n";
        }
    }

    // Líneas
    static const char* nombresLineas[4] = {"Arriba", "Derecha", "Abajo", "Izquierda"};
    for (int i = 0; i < 4; ++i) {
        Linea* l = celda.getLinea(i);
        if (l) {
            std::cout << "Linea " << nombresLineas[i] << ": (" 
                      << l->getP1()->getFila() << "," << l->getP1()->getColumna() << ") <-> ("
                      << l->getP2()->getFila() << "," << l->getP2()->getColumna() << ")\n";
        } else {
            std::cout << "Linea " << nombresLineas[i] << ": nullptr\n";
        }
    }

    std::cout << "========================================\n";
}
*/
/*
Nodo4<Punto>* Tablero::obtenerNodo(int fila, int columna) const {
    Nodo4<Punto>* filaPtr = inicio;
    for (int f = 0; f < fila && filaPtr; ++f) {
        filaPtr = filaPtr->obtenerAbajo();
    }
    if (!filaPtr) return nullptr;

    Nodo4<Punto>* colPtr = filaPtr;
    for (int c = 0; c < columna && colPtr; ++c) {
        colPtr = colPtr->obtenerDerecha();
    }
    return colPtr;
}*/

/*
Nodo4<Punto>* Tablero::obtenerNodo(int fila, int columna) const {
    Nodo4<Punto>* filaPtr = inicio;
    for (int f = 0; f < fila && filaPtr; ++f) {
        filaPtr = filaPtr->obtenerAbajo();
    }
    if (!filaPtr) return nullptr;

    Nodo4<Punto>* colPtr = filaPtr;
    for (int c = 0; c < columna && colPtr; ++c) {
        colPtr = colPtr->obtenerDerecha();
    }
    return colPtr;
}*/
/*
void Tablero::debugCeldas() const {
    int total = 0;
    Nodo4<Celda>* filaCelda = inicioCeldas;

    cout << "=== DEBUG: Estado de Celdas ===\n";
    while (filaCelda) {
        Nodo4<Celda>* celdaPtr = filaCelda;
        while (celdaPtr) {
            const Celda& celda = celdaPtr->obtenerDato();
            cout << "Celda (" << celda.getFila() << "," << celda.getColumna() << ") "
                 << (celda.estaCompletada() ? "[COMPLETA]" : "[INCOMPLETA]")
                 << " Propietario: '" << celda.obtenerInicialPropietario() << "'\n";
            total++;
            celdaPtr = celdaPtr->obtenerDerecha();
        }
        filaCelda = filaCelda->obtenerAbajo();
    }
    cout << "Total de celdas: " << total << "\n";
    cout << "==============================\n";
}
*/
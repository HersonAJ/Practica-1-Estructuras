#include "Tablero.h"
#include "ListaEnlazada.h"
#include "Linea.h"
#include <iostream>
#include "PowerUps/DobleLinea.h"
#include"PowerUps/NuevasTierras.h"
#include"PowerUps/Explosivo.h"
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
            cout << colPunto->obtenerDato().simbolo();
            if (c < columnas - 1) {
                cout << (existeLineaColocada(colPunto->obtenerDato().getFila(), 
                colPunto->obtenerDato().getColumna(), 
                colPunto->obtenerDerecha()->obtenerDato().getFila(), 
                colPunto->obtenerDerecha()->obtenerDato().getColumna()) ? "---" : "   ");
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
                cout << (existeLineaColocada(colPuntoVert->obtenerDato().getFila(), 
                colPuntoVert->obtenerDato().getColumna(), 
                colPuntoVert->obtenerAbajo()->obtenerDato().getFila(), 
                colPuntoVert->obtenerAbajo()->obtenerDato().getColumna()) ? "|" : " ");

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
        int lf1 = (l->getP1() && !l->getP1()->estaDestruido()) ? l->getP1()->getFila() : -1;
        int lc1 = (l->getP1() && !l->getP1()->estaDestruido()) ? l->getP1()->getColumna() : -1;
        int lf2 = (l->getP2() && !l->getP2()->estaDestruido()) ? l->getP2()->getFila() : -1;
        int lc2 = (l->getP2() && !l->getP2()->estaDestruido()) ? l->getP2()->getColumna() : -1;

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
void Tablero::generarCeldas() {
    if (filas < 2 || columnas < 2) {
        inicioCeldas = nullptr;
        return;
    }

    // Lógica para colocar un PowerUp en una celda aleatoria
    srand(time(nullptr));
    //int totalCeldas = (filas - 1) * (columnas - 1);
    int celdasConPowerUp = 3; // Cantidad fija de PowerUps a distribuir

    Nodo4<Punto>* filaPunto = inicio;
    Nodo4<Celda>* filaCeldaInicio = nullptr;
    Nodo4<Celda>* filaCeldaAnterior = nullptr;
    
    // Lista para guardar las coordenadas aleatorias de los PowerUps
    int celdasAleatorias[celdasConPowerUp][2]; 
    bool existeCoordenada;
    for (int i = 0; i < celdasConPowerUp; i++) {
        do {
            existeCoordenada = false;
            celdasAleatorias[i][0] = rand() % (filas - 1);
            celdasAleatorias[i][1] = rand() % (columnas - 1);
            
            // Verificar si la coordenada ya existe
            for(int j = 0; j < i; j++){
                if (celdasAleatorias[i][0] == celdasAleatorias[j][0] && celdasAleatorias[i][1] == celdasAleatorias[j][1]){
                    existeCoordenada = true;
                    break;
                }
            }
        } while(existeCoordenada);
    }
    
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
            
            // Lógica para asignar PowerUps a las celdas aleatorias
            for(int i = 0; i < celdasConPowerUp; i++){
                if (f == celdasAleatorias[i][0] && c == celdasAleatorias[i][1]){
                    // Elegir aleatoriamente entre DobleLinea (0) y NuevasTierras (1)
                    int tipoPowerUp = rand() % 3;
                    PowerUp* nuevoPowerUp = nullptr;

                    if (tipoPowerUp == 0) {
                        nuevoPowerUp = new DobleLinea();
                    } else if (tipoPowerUp == 1) {
                        nuevoPowerUp = new NuevasTierras();
                    } else {
                        nuevoPowerUp = new Explosivo();
                    }

                    nodoCelda->obtenerDato().asignarPowerUp(nuevoPowerUp);
                    std::cout << "PowerUp " << nuevoPowerUp->getSimbolo() 
                              << " colocado en la celda: [" << f << "][" << c << "]" << std::endl;
                    break; 
                }
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

void Tablero::expandirAbajo() {
    // 1. Encontrar la última fila de puntos
    Nodo4<Punto>* ultimaFila = inicio;
    while (ultimaFila->obtenerAbajo() != nullptr) {
        ultimaFila = ultimaFila->obtenerAbajo();
    }

    // 2. Crear nueva fila de puntos
    Nodo4<Punto>* nuevaFila = nullptr;
    Nodo4<Punto>* currentNew = nullptr;
    Nodo4<Punto>* currentOld = ultimaFila;
    
    for (int c = 0; c < columnas; ++c) {
        Nodo4<Punto>* nuevoNodo = new Nodo4<Punto>(Punto(filas, c));
        
        if (nuevaFila == nullptr) {
            nuevaFila = nuevoNodo;
            currentNew = nuevaFila;
        } else {
            currentNew->establecerDerecha(nuevoNodo);
            nuevoNodo->establecerIzquierda(currentNew);
            currentNew = nuevoNodo;
        }
        
        // Enlazar verticalmente con la fila anterior
        if (currentOld) {
            currentOld->establecerAbajo(nuevoNodo);
            nuevoNodo->establecerArriba(currentOld);
            currentOld = currentOld->obtenerDerecha();
        }
    }

    // Crear nuevas celdas para la última fila de celdas
    if (filas > 1) { // Solo si ya existían celdas
        Nodo4<Celda>* ultimaFilaCeldas = inicioCeldas;
        while (ultimaFilaCeldas->obtenerAbajo() != nullptr) {
            ultimaFilaCeldas = ultimaFilaCeldas->obtenerAbajo();
        }
        
        Nodo4<Punto>* puntoSuperior = ultimaFila;
        Nodo4<Punto>* puntoInferior = nuevaFila;
        Nodo4<Celda>* nuevaFilaCeldas = nullptr;
        Nodo4<Celda>* currentCeldaNew = nullptr;
        
        for (int c = 0; c < columnas - 1; ++c) {
            if (!puntoSuperior || !puntoInferior) break;
            
            Punto* supIzq = &(puntoSuperior->obtenerDato());
            Punto* supDer = &(puntoSuperior->obtenerDerecha()->obtenerDato());
            Punto* infIzq = &(puntoInferior->obtenerDato());
            Punto* infDer = &(puntoInferior->obtenerDerecha()->obtenerDato());
            
            // Buscar o crear líneas
            Linea* arriba = buscarLinea(supIzq, supDer);
            Linea* abajo = new Linea(infIzq, infDer, Orientacion::HORIZONTAL);
            Linea* izquierda = buscarLinea(supIzq, infIzq);
            Linea* derecha = new Linea(supDer, infDer, Orientacion::VERTICAL);
            
            lineas.insertarFinal(abajo);
            lineas.insertarFinal(derecha);
            
            Celda nuevaCelda(filas - 1, c, supIzq, supDer, infIzq, infDer, 
                            arriba, derecha, abajo, izquierda);
            Nodo4<Celda>* nuevaCeldaNodo = new Nodo4<Celda>(nuevaCelda);
            
            if (nuevaFilaCeldas == nullptr) {
                nuevaFilaCeldas = nuevaCeldaNodo;
                currentCeldaNew = nuevaFilaCeldas;
            } else {
                currentCeldaNew->establecerDerecha(nuevaCeldaNodo);
                nuevaCeldaNodo->establecerIzquierda(currentCeldaNew);
                currentCeldaNew = nuevaCeldaNodo;
            }
            
            // Enlazar verticalmente con la fila de celdas superior
            if (ultimaFilaCeldas) {
                Nodo4<Celda>* celdaArriba = ultimaFilaCeldas;
                for (int i = 0; i < c && celdaArriba; i++) {
                    celdaArriba = celdaArriba->obtenerDerecha();
                }
                if (celdaArriba) {
                    celdaArriba->establecerAbajo(nuevaCeldaNodo);
                    nuevaCeldaNodo->establecerArriba(celdaArriba);
                }
            }
            
            puntoSuperior = puntoSuperior->obtenerDerecha();
            puntoInferior = puntoInferior->obtenerDerecha();
        }
        
    }
    
    // Actualizar dimensiones
    filas++;
    
    std::cout << "Tablero expandido hacia ABAJO. Nuevo tamaño: " << filas << "x" << columnas << std::endl;
}

void Tablero::expandirDerecha() {
    // Encontrar la última columna de puntos
    Nodo4<Punto>* ultimaColumna = inicio;
    while (ultimaColumna->obtenerDerecha() != nullptr) {
        ultimaColumna = ultimaColumna->obtenerDerecha();
    }
    
    // Crear nueva columna de puntos
    Nodo4<Punto>* currentFila = inicio;
    Nodo4<Punto>* nuevaColumnaStart = nullptr;
    Nodo4<Punto>* prevNewNode = nullptr;
    
    for (int f = 0; f < filas; ++f) {
        Nodo4<Punto>* nuevoNodo = new Nodo4<Punto>(Punto(f, columnas));
        
        if (nuevaColumnaStart == nullptr) {
            nuevaColumnaStart = nuevoNodo;
        }
        
        // Enlazar horizontalmente con la columna anterior
        if (currentFila) {
            Nodo4<Punto>* lastInRow = currentFila;
            while (lastInRow->obtenerDerecha() != nullptr) {
                lastInRow = lastInRow->obtenerDerecha();
            }
            lastInRow->establecerDerecha(nuevoNodo);
            nuevoNodo->establecerIzquierda(lastInRow);
        }
        
        // Enlazar verticalmente con nodo de la misma columna
        if (prevNewNode) {
            prevNewNode->establecerAbajo(nuevoNodo);
            nuevoNodo->establecerArriba(prevNewNode);
        }
        
        prevNewNode = nuevoNodo;
        if (currentFila) currentFila = currentFila->obtenerAbajo();
    }
    
    // Crear nuevas celdas para la última columna de celdas
    if (columnas > 1) { // Solo si ya existían celdas
        Nodo4<Punto>* currentFilaForCells = inicio;
        Nodo4<Celda>* currentFilaCeldas = inicioCeldas;
        
        for (int f = 0; f < filas - 1; ++f) {
            if (!currentFilaForCells || !currentFilaCeldas) break;
            
            // Encontrar el último nodo de celda en esta fila
            Nodo4<Celda>* lastCeldaInRow = currentFilaCeldas;
            while (lastCeldaInRow->obtenerDerecha() != nullptr) {
                lastCeldaInRow = lastCeldaInRow->obtenerDerecha();
            }
            
            // Crear nueva celda
            Nodo4<Punto>* puntoSupIzq = currentFilaForCells;
            for (int i = 0; i < columnas - 1 && puntoSupIzq; i++) {
                puntoSupIzq = puntoSupIzq->obtenerDerecha();
            }
            
            if (puntoSupIzq && puntoSupIzq->obtenerDerecha() && 
                puntoSupIzq->obtenerAbajo() && puntoSupIzq->obtenerDerecha()->obtenerAbajo()) {
                
                Punto* supIzq = &(puntoSupIzq->obtenerDato());
                Punto* supDer = &(puntoSupIzq->obtenerDerecha()->obtenerDato());
                Punto* infIzq = &(puntoSupIzq->obtenerAbajo()->obtenerDato());
                Punto* infDer = &(puntoSupIzq->obtenerDerecha()->obtenerAbajo()->obtenerDato());
                
                // Buscar o crear líneas
                Linea* arriba = buscarLinea(supIzq, supDer);
                Linea* abajo = buscarLinea(infIzq, infDer);
                Linea* izquierda = buscarLinea(supIzq, infIzq);
                Linea* derecha = new Linea(supDer, infDer, Orientacion::VERTICAL);
                
                lineas.insertarFinal(derecha);
                
                Celda nuevaCelda(f, columnas - 1, supIzq, supDer, infIzq, infDer, 
                                arriba, derecha, abajo, izquierda);
                Nodo4<Celda>* nuevaCeldaNodo = new Nodo4<Celda>(nuevaCelda);
                
                // Enlazar horizontalmente
                if (lastCeldaInRow) {
                    lastCeldaInRow->establecerDerecha(nuevaCeldaNodo);
                    nuevaCeldaNodo->establecerIzquierda(lastCeldaInRow);
                }
                
                // Enlazar verticalmente si hay celda abajo
                if (f > 0 && currentFilaCeldas->obtenerAbajo()) {
                    Nodo4<Celda>* celdaAbajo = currentFilaCeldas->obtenerAbajo();
                    for (int i = 0; i < columnas - 1 && celdaAbajo; i++) {
                        celdaAbajo = celdaAbajo->obtenerDerecha();
                    }
                    if (celdaAbajo) {
                        celdaAbajo->establecerArriba(nuevaCeldaNodo);
                        nuevaCeldaNodo->establecerAbajo(celdaAbajo);
                    }
                }
            }
            
            currentFilaForCells = currentFilaForCells->obtenerAbajo();
            currentFilaCeldas = currentFilaCeldas->obtenerAbajo();
        }
    }
    
    // Actualizar dimensiones
    columnas++;
    
    std::cout << "Tablero expandido hacia DERECHA. Nuevo tamaño: " << filas << "x" << columnas << std::endl;
}

// Método auxiliar necesario
Linea* Tablero::buscarLinea(Punto* p1, Punto* p2) {
    Nodo4<Linea*>* actual = lineas.obtenerCabeza();
    while (actual) {
        Linea* l = actual->obtenerDato();
        if ((l->getP1() == p1 && l->getP2() == p2) || 
            (l->getP1() == p2 && l->getP2() == p1)) {
            return l;
        }
        actual = actual->obtenerDerecha();
    }
    return nullptr; // No encontrada
}

void Tablero::explotarPunto(int fila, int columna) {
    // 1. Verificar primero si las coordenadas son válidas
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        std::cout << "Error: Coordenadas (" << fila << "," << columna 
                  << ") fuera de rango. Tablero es " << filas << "x" << columnas << std::endl;
        return;
    }

    // 2. Buscar el nodo
    Nodo4<Punto>* nodoVictima = buscarPunto(fila, columna);
    if (!nodoVictima) {
        std::cout << " Error: Punto (" << fila << "," << columna << ") no encontrado" << std::endl;
        return;
    }

    // 3. VERIFICACIÓN: Confirmar que el punto no esté ya destruido
    if (nodoVictima->obtenerDato().estaDestruido()) {
        std::cout << "El punto (" << fila << "," << columna << ") ya estaba destruido" << std::endl;
        return;
    }

    // 4. Marcar el punto como destruido
    nodoVictima->obtenerDato().destruir();
    
    // 5. Buscar celdas afectadas y liberarlas
    Nodo4<Celda>* filaCelda = inicioCeldas;
    ListaEnlazada<Jugador*> jugadoresAfectados;
    Punto* puntoDestruido = &(nodoVictima->obtenerDato());
    
    while (filaCelda) {
        Nodo4<Celda>* celdaActual = filaCelda;
        while (celdaActual) {
            Celda& celda = celdaActual->obtenerDato();
            
            // Verificar si la celda contiene el punto destruido
            bool contienePuntoDestruido = false;
            for (int i = 0; i < 4; i++) {
                if (celda.getEsquina(i) == puntoDestruido) {
                    contienePuntoDestruido = true;
                    break;
                }
            }
            
            if (contienePuntoDestruido && celda.estaCompletada()) {
                // Liberar la celda y registrar jugador afectado
                Jugador* propietario = celda.getPropietario();
                if (propietario) {
                    // Evitar duplicados en la lista de jugadores afectados
                    bool yaListado = false;
                    Nodo4<Jugador*>* actual = jugadoresAfectados.obtenerCabeza();
                    while (actual) {
                        if (actual->obtenerDato() == propietario) {
                            yaListado = true;
                            break;
                        }
                        actual = actual->obtenerDerecha();
                    }
                    if (!yaListado) {
                        jugadoresAfectados.insertarFinal(propietario);
                    }
                }
                // Quitar propietario pero mantener la celda completada
                // (según las reglas: "el cuadrado pierde su dueño, pero el punteo no baja")
                celda.liberar();
            }
            
            celdaActual = celdaActual->obtenerDerecha();
        }
        filaCelda = filaCelda->obtenerAbajo();
    }

    // 6. Mensaje de explosión
    std::cout << " Punto (" << fila << "," << columna << ") marcado como DESTRUIDO!" << std::endl;
    
    // 7. Mostrar jugadores afectados
    if (jugadoresAfectados.obtenerCabeza()) {
        std::cout << "Jugadores afectados: ";
        Nodo4<Jugador*>* jugadorNode = jugadoresAfectados.obtenerCabeza();
        while (jugadorNode) {
            std::cout << jugadorNode->obtenerDato()->getNombre() << " ";
            jugadorNode = jugadorNode->obtenerDerecha();
        }
        std::cout << std::endl;
    } else {
        std::cout << "Ningún jugador fue afectado por la explosión." << std::endl;
    }
}
Nodo4<Punto>* Tablero::buscarPunto(int fila, int columna) const {
    if (!inicio) {
        std::cout << " Error: Tablero no inicializado" << std::endl;
        return nullptr;
    }
    
    Nodo4<Punto>* actual = inicio;
    int filaActual = 0;
    
    while (actual && filaActual <= fila) {
        Nodo4<Punto>* colActual = actual;
        int colActualIndex = 0;
        
        while (colActual && colActualIndex <= columna) {
            if (filaActual == fila && colActualIndex == columna) {
                return colActual;  // Devuelve el NODO, no el Punto
            }
            colActual = colActual->obtenerDerecha();
            colActualIndex++;
        }
        actual = actual->obtenerAbajo();
        filaActual++;
    }
    
    return nullptr;
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
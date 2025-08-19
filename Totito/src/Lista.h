#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class Lista {
    private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamaño;

    public:
    Lista() : cabeza(nullptr), cola(nullptr), tamaño(0) {}
    ~Lista() {
        limpiar();
    }

    void agregarFinal(T* elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        tamaño++;
    }

    void agregarIncicio(T* elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
            cabeza = nuevo;
        }
        tamaño++;
    }

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* temp = actual->siguiente;
            delete actual->dato;
            delete actual;
            actual = temp;
        }
        cabeza = cola = nullptr;
        tamaño = 0;
    }

    Nodo<T>* getCabeza() const {
        return cabeza;
    }

    Nodo<T>* getCola() const {
        return cola;
    }

    int getTamaño() const {
        return tamaño;
    }

    void mostrar(void (*mostrarElemento)(T*)) const {
        Nodo<T>* actual = cabeza;
        while (actual) {
            mostrarElemento(actual->dato);
            actual = actual->siguiente;
        }
    }
};

#endif
#ifndef PILA_H
#define PILA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class Pila {
private:
    Nodo<T>* tope;

public:
    Pila();
    ~Pila();

    void apilar(T* dato);
    T* desapilar();
    T* verTope() const;
    bool estaVacia() const;
};

template <typename T>
Pila<T>::Pila() : tope(nullptr) {}

template <typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        desapilar(); 
    }
}

template <typename T>
void Pila<T>::apilar(T* dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    if (estaVacia()) {
        tope = nuevoNodo;
    } else {
        nuevoNodo->setSiguiente(tope);
        tope->setAnterior(nuevoNodo);
        tope = nuevoNodo;
    }
}

template <typename T>
T* Pila<T>::desapilar() {
    if (estaVacia()) {
        return nullptr;
    }

    Nodo<T>* nodoEliminar = tope;
    T* dato = nodoEliminar->getDato();

    tope = nodoEliminar->getSiguiente();
    if (tope != nullptr) {
        tope->setAnterior(nullptr);
    }

    delete nodoEliminar;
    return dato;
}

template <typename T>
T* Pila<T>::verTope() const {
    if (estaVacia()) {
        return nullptr;
    }
    return tope->getDato();
}

template <typename T>
bool Pila<T>::estaVacia() const {
    return tope == nullptr; 
}

#endif
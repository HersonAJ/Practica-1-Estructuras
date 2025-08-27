#ifndef COLA_H
#define COLA_H

#include "Nodo.h"

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int cantidad;

public:
    Cola() : frente(nullptr), fin(nullptr), cantidad(0) {}

    ~Cola() {
        while (!esVacio()) {
            desencolar();
        }
    }

    void encolar(T* valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (esVacio()) {
            frente = fin = nuevo;
        } else {
            fin->setSiguiente(nuevo);
            nuevo->setAnterior(fin);
            fin = nuevo;
        }
        cantidad++;
    }

    T* desencolar() {
        if (esVacio()) {
            return nullptr;
        }
        Nodo<T>* temp = frente;
        T* valor = temp->getDato();
        frente = frente->getSiguiente();
        if (frente == nullptr) {
            fin = nullptr;
        }
        delete temp;
        cantidad--;
        return valor;
    }

    T* verPrimero() {
        if (esVacio()) {
            return nullptr;
        }
        return frente->getDato();
    }

    bool esVacio() const {
        return frente == nullptr;
    }

    int size() const {
        return cantidad;
    }

    void encolarFrente(T* valor);
};
//metodo para el poder de doble linea
template <typename T>
void Cola<T>::encolarFrente(T* valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    if (esVacio()) {
        frente = fin = nuevoNodo;
    } else {
        nuevoNodo->setSiguiente(frente);
        frente->setAnterior(nuevoNodo);
        frente = nuevoNodo;
    }
    cantidad++;
}

#endif // COLA_H
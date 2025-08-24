#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Nodo4.h"

//template generico para el tipo de listas que se necesiten adelante
template <typename Tipo>

class ListaEnlazada {
    private:
    Nodo4<Tipo>* cabeza; //asignando el primero nodo de la lista
    int cantidad;

    public:
    //constructor
    ListaEnlazada(){
        cabeza = nullptr;
        cantidad = 0;
    }

    //destructor
    ~ListaEnlazada(){
        limpiar();
    }

    //la forma de insertar un nuevo nodo sera al inicio
    void insertarInicio(const Tipo& valor) {
        Nodo4<Tipo>* nuevo = new Nodo4<Tipo>(valor);
        if (cabeza != nullptr) {
            nuevo->establecerDerecha(cabeza);
            cabeza->establecerIzquierda(nuevo);
        }
        cabeza = nuevo;
        cantidad++;
    }

    void insertarFinal(const Tipo& valor) {
        Nodo4<Tipo>* nuevo = new Nodo4<Tipo>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo4<Tipo>* actual = cabeza;
            while(actual->obtenerDerecha() != nullptr) {
                actual = actual->obtenerDerecha();
            }
            actual->establecerDerecha(nuevo);
            nuevo->establecerIzquierda(actual);
        }
        cantidad++;
    }

    //obtener la cabeza
    Nodo4<Tipo>* obtenerCabeza() const {
        return cabeza;
    }

    //obtener cantidad de elementos 
    int obtenerCantidad() const {
        return cantidad;
    }

    //eliminar todos los nodos
    void limpiar() {
        Nodo4<Tipo>* actual = cabeza;
        while (actual != nullptr) {
            Nodo4<Tipo>* siguiente = actual->obtenerDerecha();
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        cantidad = 0;
    }
};

#endif
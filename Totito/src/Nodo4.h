#ifndef NODO4_H
#define NODO4_H

template <typename Tipo>

class Nodo4 {
    private:
    Tipo dato;

    Nodo4<Tipo>* arriba;
    Nodo4<Tipo>* abajo;
    Nodo4<Tipo>* izquierda;
    Nodo4<Tipo>* derecha;

    public:
    //constructor
    Nodo4(const Tipo& valor) {
        dato = valor;
        arriba = nullptr;
        abajo = nullptr;
        izquierda = nullptr;
        derecha = nullptr;
    }

    //getters y setters
    void establecerArriba(Nodo4<Tipo>* nodo) { arriba = nodo; }
    void establecerAbajo(Nodo4<Tipo>* nodo) { abajo = nodo; }
    void establecerIzquierda(Nodo4<Tipo>* nodo) { izquierda = nodo; }
    void establecerDerecha(Nodo4<Tipo>* nodo) { derecha = nodo; }

    Nodo4<Tipo>* obtenerArriba() { return arriba; }
    Nodo4<Tipo>* obtenerAbajo() { return abajo; }
    Nodo4<Tipo>* obtenerIzquierda() { return izquierda; }
    Nodo4<Tipo>* obtenerDerecha() { return derecha; }

    //manejo del dato del nodo
    void establecerDato(const Tipo& valor) {
        dato = valor;
    }
    const Tipo& obtenerDato() { return dato; }
};

#endif
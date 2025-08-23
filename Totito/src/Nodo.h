#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T* dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    // Constructor privado, solo Lista<T> puede crear nodos
    Nodo(T* d) : dato(d), siguiente(nullptr), anterior(nullptr) {}

    template <typename> friend class Lista;

public:
    // Getters
    T* getDato() const { return dato; }
    Nodo<T>* getSiguiente() const { return siguiente; }
    Nodo<T>* getAnterior() const { return anterior; }
    void setSiguiente(Nodo<T>* sig) { siguiente = sig; }
    void setAnterior(Nodo<T>* ant) { anterior = ant; }
};

#endif

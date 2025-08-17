#ifndef COLA_H
#define COLA_H

//nodo generico 

template<typename T> 
class Nodo {
    public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}

};

template <typename T>
class Cola {
    private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int cantidad;

    public:
    //constructor
    Cola() : frente(nullptr), fin(nullptr), cantidad(0){}

    //destructor
    ~Cola() {
        while (!esVacio()) {
            desencolar();
        }
        
    }

    //insertar al final
    void encolar( const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (esVacio()) {
            frente = fin = nuevo;
        } else {
            fin ->siguiente = nuevo;
            fin = nuevo;
        }
        cantidad++;
    }

    //quitar la cabeza
    T desencolar() {
        Nodo<T>* temp = frente;
        T valor = temp->dato;
        frente = frente->siguiente;
        if (frente == nullptr) {
            fin = nullptr; // la cola quedo vacia
        }
        delete temp;
        cantidad--;
        return valor;
    }

    //ver el frente y quitarlo
    T& verPrimero() {
        return frente->dato;
    }

    bool esVacio() const {
        return frente == nullptr;
    }

    //cantidad de elementos
    int size() const {
        return cantidad;
    }
};

#endif //COLA_H
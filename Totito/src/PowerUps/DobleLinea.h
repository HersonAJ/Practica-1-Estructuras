#ifndef DOBLELINEA_H
#define DOBLELINEA_H

#include "PowerUp.h"
#include <iostream>

class DobleLinea : public PowerUp {
public:

    DobleLinea() : PowerUp("DL", true) {}

    // Destructor
    ~DobleLinea() override {}

    // Implementación del método virtual activar() que anuncia la activación del poder.
    void activar() override {
        std::cout << "¡Poder Doble Línea activado! Puedes colocar dos líneas consecutivas." << std::endl;

    }
};

#endif
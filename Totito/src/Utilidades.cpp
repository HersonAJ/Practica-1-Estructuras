#include "Utilidades.h"
#include <cstdlib>

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux / macOS
#endif
}

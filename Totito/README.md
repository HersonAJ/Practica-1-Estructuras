# Totito (Dots and Boxes)

Proyecto académico en **C++** para implementar el clásico juego de *Totito / Dots and Boxes*, utilizando **estructuras de datos dinámicas** (listas enlazadas simples, dobles y malla bidimensional).  

El objetivo es reforzar conceptos de:
- Programación Orientada a Objetos (POO)
- Listas enlazadas personalizadas
- Manejo de memoria dinámica
- Diseño modular
- Uso de `Makefile` para la compilación


## Características principales

- Juego configurable:
  - Tamaño del tablero (`n` filas × `m` columnas, mínimo 3×3).
  - Número de jugadores (1–10).
- Representación del tablero con **malla de nodos enlazados (arriba, abajo, izquierda, derecha)**.
- Manejo de **puntos y líneas** mediante listas enlazadas.
- Representación de **celdas** para verificar cuadros completos y asignar propietario.
- Control de turnos con **cola circular** de jugadores.
- Condiciones de victoria aplicadas en orden:
  1. Puntos acumulados
  2. Número de cuadros capturados
  3. Filas ganadas
  4. Columnas ganadas
- Mensajes de depuración (`DEBUG`) opcionales para inspeccionar líneas y celdas.
- Interfaz de texto en consola.


## Estructura del proyecto

.
├── src/
│ ├── main.cpp
│ ├── Juego.cpp / Juego.h
│ ├── Tablero.cpp / Tablero.h
│ ├── Punto.cpp / Punto.h
│ ├── Linea.cpp / Linea.h
│ ├── Celda.cpp / Celda.h
│ ├── Jugador.cpp / Jugador.h
│ ├── Configuracion.cpp / Configuracion.h
│ ├── GestorLineas.cpp / GestorLineas.h
│ ├── ListaEnlazada.h (genérica)
│ ├── Nodo4.h (para nodos con 4 direcciones)
│ ├── Utilidades.cpp / Utilidades.h
│ └── CondicionesDeVictoria/
│ ├── CondicionesDeVictoria.h
│ ├── PuntosTotales.cpp
│ ├── CuadrosTotales.cpp
│ ├── FilasGanadas.cpp
│ ├── ColumnasGanadas.cpp
│ ├── EvaluadorCondiciones.cpp
│ └── EvaluadorCondiciones.h
├── build/ (archivos .o generados)
├── bin/ (ejecutable final)
└── Makefile


## Compilación y ejecución

1. Compilar el proyecto:
   1. bash
   2. make

2. Ejecucion
    ./bin/totito

3. limpieza de archivos generados en el bin 
    make clean


## Cómo jugar

Al iniciar, el programa pedirá:

Número de filas y columnas del tablero.

Número de jugadores y sus nombres.

Cada jugador recibe una inicial que lo identificará.

En cada turno:

El jugador debe ingresar dos coordenadas (ejemplo: A0 y A1) para dibujar una línea.

Si completa un cuadro, gana un punto y ese cuadro queda marcado con su inicial.

El juego termina cuando:

Se completan todas las líneas del tablero.

Se escribe salir en lugar de coordenadas.


## Condiciones de victoria

Si varios jugadores empatan en puntos, se aplican filtros en el siguiente orden:

Puntos totales

Cuadros capturados

Filas ganadas

Columnas ganadas

Si persiste el empate -> se declara empate técnico.



## Tecnologías utilizadas

Lenguaje: C++17

Paradigma: POO

Estructuras dinámicas: listas enlazadas simples, dobles y nodos con 4 direcciones

Compilación: g++ con Makefile

Sistema operativo: Linux (Ubuntu recomendado)
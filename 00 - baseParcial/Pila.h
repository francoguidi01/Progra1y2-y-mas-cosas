#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "listaJugadores.h"


/// 6.a

#define Pila nodoJugador *


void inicPila (Pila * pila);

void apilar (Pila * pila, stJugador dato);

void mostrar (Pila * pila);

#endif // PILA_H_INCLUDED

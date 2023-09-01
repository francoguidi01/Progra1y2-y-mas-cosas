#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "productos.h"

typedef struct _nodoArbol
{
    stProducto dato;
    struct _nodoArbol *izq;
    struct _nodoArbol *der;
} nodoArbol;

nodoArbol * inicArbol();
nodoArbol * cargarElArbol (nodoArbol * arbol);
nodoArbol * crearNodoArbol(stProducto dato);
nodoArbol * insertarPorId(nodoArbol * arbol, stProducto dato);
nodoArbol * buscar(nodoArbol * arbol, stProducto dato);
nodoArbol * borrarNodoArbol (nodoArbol * osvaldo, stProducto dato);
nodoArbol * nodoMasDerecho (nodoArbol* arbol);
nodoArbol * nodoMasIzquierdo (nodoArbol* arbol);
void preorder(nodoArbol * arbol);
void inorder(nodoArbol * arbol);
void postorder(nodoArbol * arbol);

#endif // ARBOL_H_INCLUDED
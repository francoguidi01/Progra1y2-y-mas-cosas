#ifndef NODOARBOL_H_INCLUDED
#define NODOARBOL_H_INCLUDED

#include "productos.h"


typedef struct _nodoArbol
{
    stProducto dato;
    struct _nodoArbol *izq;
    struct _nodoArbol *der;
} nodoArbol;

nodoArbol * inicArbol();
nodoArbol * crearNodoArbol(stProducto dato);
nodoArbol * cargarElArbol (nodoArbol * arbol);
nodoArbol * insertarPorId(nodoArbol * arbol, stProducto dato);
void preorder(nodoArbol * arbol);
void inorder(nodoArbol * arbol);
void postorder(nodoArbol * arbol);
nodoArbol * buscar(nodoArbol * arbol, stProducto dato);
void copiarProdArbolLista(nodoArbol * arbol, nodoListaProducto ** lista, stProducto dato);
stProducto retornaProdNodo (nodoArbol * arbol);
nodoArbol * deArchivoAArbolProductos (nodoArbol * arbol, char archivo []);
nodoArbol * deArrayToArbol(stProducto dato[], int principio, int fin);
nodoArbol * nodoMasDerecho (nodoArbol* arbol);
nodoArbol * nodoMasIzquierdo (nodoArbol* arbol);
nodoArbol * borrarNodoArbol (nodoArbol * osvaldo, stProducto dato);
void copiarProdArbolLista(nodoArbol * arbol, nodoListaProducto ** lista, stProducto dato);


#endif // NODOARBOL_H_INCLUDED

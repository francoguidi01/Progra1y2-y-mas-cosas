#ifndef ARBOLPRODUCTOS_H_INCLUDED
#define ARBOLPRODUCTOS_H_INCLUDED

typedef struct _nodoArbolProducto
{
    stProducto p;
    struct _nodoArbolProducto* izq;
    struct _nodoArbolProducto* der;
} nodoArbolProducto;

nodoArbolProducto * inicArbol();
nodoArbolProducto * crearNodoArbol(stProducto p);
nodoArbolProducto * insertarNodoArbolProd(nodoArbolProducto * arbol, stProducto p);
void inorder (nodoArbolProducto * arbol);
nodoArbolProducto * buscarNodoArbolProd(nodoArbolProducto * arbol,int idP);
stProducto retornaProdNodo (nodoArbolProducto * arbol);


#endif // ARBOLPRODUCTOS_H_INCLUDED

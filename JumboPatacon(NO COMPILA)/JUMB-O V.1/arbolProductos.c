#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "arbolProductos.h"
#include "productos.h"


nodoArbolProducto * inicArbol()
{
    return NULL;
}
nodoArbolProducto * crearNodoArbol(stProducto p)
{
    nodoArbolProducto * aux = (nodoArbolProducto*)malloc(sizeof(nodoArbolProducto));
    aux->p = p;
    aux->der = NULL;
    aux->izq = NULL;
    return aux;
}
nodoArbolProducto * insertarNodoArbolProd(nodoArbolProducto * arbol, stProducto p)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(p);
    }
    else
    {
        if(p.idProducto>arbol->p.idProducto)
        {
            arbol->der=insertarNodoArbolProd(arbol->der,p);

        }
        else
        {
            arbol->izq=insertarNodoArbolProd(arbol->izq,p);
        }
    }
    return arbol;
}
void inorder (nodoArbolProducto * arbol)
{
    if(arbol)
    {
        inorder(arbol->izq);
        muestraProducto(arbol->p);
        inorder(arbol->der);
    }
}
nodoArbolProducto * buscarNodoArbolProd(nodoArbolProducto * arbol,int idP)
{
    nodoArbolProducto * rta=NULL;
    if(arbol!=NULL)
    {
        if(idP==arbol->p.idProducto)
        {
            rta=arbol;
        }
        else
        {
            if(idP>arbol->p.idProducto)
            {
                rta=buscarNodoArbolProd(arbol->der,idP);
            }
            else
            {
                rta=buscarNodoArbolProd(arbol->der,idP);
            }
        }
    }return rta;
}
stProducto retornaProdNodo (nodoArbolProducto * arbol)
{
    stProducto aux=arbol->p;
    return aux;
}

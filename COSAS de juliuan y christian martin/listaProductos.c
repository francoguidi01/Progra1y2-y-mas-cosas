#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "productos.c"
#include "listaProductos.h"
#include "arbolProductos.c"

nodoListaProducto * inicListaProducto()
{
    return NULL;
}
nodoListaProducto * crearNodoListaProducto(stProducto p)
{
    nodoListaProducto *aux = (nodoListaProducto *) malloc(sizeof(nodoListaProducto));
    aux ->p = p;
    aux ->siguiente =NULL;
    return aux;
}
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
    }
        lista = nuevoNodo;
    return lista;
}
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{
    if(lista== NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoListaProducto * ultimo = buscarUltimoNodo(lista);
        ultimo->siguiente=nuevo;
    }return lista;
}
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista)
{
	nodoListaProducto * ultimo=lista;
	if(ultimo!=NULL){
	while(ultimo->siguiente != NULL)
	{
		ultimo=ultimo->siguiente;
	}
	}return ultimo;
}
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{

	if(lista==NULL)
	{
		lista=nuevo;
	}
	else
	{
	    if(strcmp(nuevo->p.nombreProducto,lista->p.nombreProducto)<0)
	    {
	        lista=agregarAlPrincipio(lista,nuevo);
	    }
	    else
        {
            nodoListaProducto * ante=lista;
            nodoListaProducto * sig=lista->siguiente;
            while(sig!=NULL && strcmp(sig->p.nombreProducto,nuevo->p.nombreProducto)<0)
            {
                ante=sig;
                sig=sig->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=sig;
        }
	}
return lista;
}
void mostrarListaRecursivaProductos(nodoListaProducto * lista, stProducto p)
{
    if(lista!=NULL)
    {
        muestraProducto(lista->p);
        mostrarListaRecursivaProductos(lista->siguiente,p);
    }
}
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id)
{
    nodoListaProducto * seg=lista;
    nodoListaProducto * ante;
    while((seg!=NULL)&& (lista->p.idProducto!=id))
    {
        ante=seg;
        seg=seg->siguiente;
    }
    if(seg!=NULL)
    {
        ante->siguiente=seg->siguiente;
        free(seg);
    }return lista;
}

nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista)
{
    nodoListaProducto * actual=lista;

    while (lista!=NULL)
    {
        actual=lista;
        lista=lista->siguiente;
        free(actual);
    }
    return lista;
}
void copiarProdArbolLista(nodoArbolProducto * arbol, nodoListaProducto ** lista, int idP)
{
    nodoArbolProducto * aux;
    stProducto p;
    if(arbol!=NULL)
    {
        aux=buscarNodoArbolProd(arbol,idP);
        if(aux!=NULL)
        {
            p =retornaProdNodo(aux);
            (*lista)=agregarAlPrincipio((*lista),crearNodoLista(p));
        }
    }
}

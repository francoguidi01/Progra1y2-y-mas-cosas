#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "listaPedidos.h"

void inicListaPedidos()
{
    return NULL;
}

nodoListaPedidos * crearNodoListaPedidos(stPedido dato)
{
    nodoListaPedidos *aux = (nodoListaPedidos *) malloc(sizeof(nodoListaPedidos));
    aux->dato = dato;
    aux ->siguiente =NULL;
    return aux;
}

nodoListaPedidos * agregarAlPrincipioPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevoNodo)
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

nodoListaPedidos * agregarAlFinalPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevo)
{
    if(lista== NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoListaPedidos * ultimo = buscarUltimoNodo(lista);
        ultimo->siguiente=nuevo;
    }return lista;
}

nodoListaPedidos * buscarUltimoNodoPedidos(nodoListaPedidos * lista)
{
	nodoListaPedidos * ultimo=lista;
	if(ultimo!=NULL){
	while(ultimo->siguiente != NULL)
	{
		ultimo=ultimo->siguiente;
	}
	}return ultimo;
}

void mostrarListaRecursivaPedidos(nodoListaPedidos * lista, stPedido p)
{
    if(lista!=NULL)
    {
        mostrarStructPedido(lista->dato);
        mostrarListaRecursivaPedidos(lista->siguiente,p);
    }
}

nodoListaPedidos * borrarNodoPorIdPedido(nodoListaPedidos * lista, int id)
{
    nodoListaPedidos * seg=lista;
    nodoListaPedidos * ante;
    while((seg!=NULL)&& (lista->dato.idPedido!=id))
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

nodoListaPedidos * borrarTodaLaListaPedidos(nodoListaPedidos * lista)
{
    nodoListaPedidos * actual=lista;

    while (lista!=NULL)
    {
        actual=lista;
        lista=lista->siguiente;
        free(actual);
    }
    return lista;
}

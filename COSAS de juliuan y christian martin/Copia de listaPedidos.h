#ifndef LISTAPEDIDOS_H_INCLUDED
#define LISTAPEDIDOS_H_INCLUDED
#include "listaProductos.h"

typedef struct _nodoListaPedidos
    stPedido p;
    nodoListaProducto * producto;
    struct _nodoListaPedidos * siguiente;
}nodoListaPedidos;

void inicListaPedidos();
nodoListaPedidos * crearNodoListaPedidos(stPedido p);
nodoListaPedidos * agregarAlPrincipioPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevoNodo);
nodoListaPedidos * agregarAlFinalPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevo);
nodoListaPedidos * buscarUltimoNodoPedidos(nodoListaPedidos * lista);
void mostrarListaRecursivaPedidos(nodoListaPedidos * lista, stPedido p);
nodoListaPedidos * borrarNodoPorIdPedido(nodoListaPedidos * lista, int id);
nodoListaPedidos * borrarTodaLaListaPedidos(nodoListaPedidos * lista);

nodoListaPedidos * agregaProductosListaPedidos(nodoListaPedidos * lista, stProducto p); ///falta Hacer
void muestraProductosPedido(nodoListaPedidos * lista); ///Falta Hacer

#endif // LISTAPEDIDOS_H_INCLUDED


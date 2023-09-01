#ifndef LISTAPRODUCTOS_H_INCLUDED
#define LISTAPRODUCTOS_H_INCLUDED
#include "productos.h"
#include "arbolProductos.h"

typedef struct _nodoListaProducto
{
    stProducto p;
    struct _nodoListaProducto * siguiente;
}nodoListaProducto;

nodoListaProducto * inicLista();
nodoListaProducto * crearNodoLista(stProducto p);
nodoListaProducto * agregarAlPrincipio(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarAlFinal(nodoListaProducto * lista, nodoListaProducto * nuevo);
nodoListaProducto * buscarUltimoNodo(nodoListaProducto * lista);
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
void mostrarListaRecursivaProductos(nodoListaProducto * lista, stProducto p);
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id);
nodoListaProducto * borrarTodaLaLista(nodoListaProducto * lista);
void copiarProdArbolLista(nodoArbolProducto * arbol, nodoListaProducto ** lista, int idP);
#endif // LISTAPRODUCTOS_H_INCLUDED

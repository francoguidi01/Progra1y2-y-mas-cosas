#ifndef LISTAPRODUCTOS_H_INCLUDED
#define LISTAPRODUCTOS_H_INCLUDED
#include "productos.h"
#include "arbolProductos.h"

typedef struct _nodoListaProducto
{
    stProducto p;
    struct _nodoListaProducto * siguiente;
}nodoListaProducto;

nodoListaProducto * inicListaProducto();
nodoListaProducto * crearNodoListaProducto(stProducto p);
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista);
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
void mostrarListaRecursivaProductos(nodoListaProducto * lista, stProducto p);
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id);
nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista);
void copiarProdArbolLista(nodoArbolProducto * arbol, nodoListaProducto ** lista, int idP);
#endif // LISTAPRODUCTOS_H_INCLUDED

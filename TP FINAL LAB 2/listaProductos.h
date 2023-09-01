#ifndef LISTAPRODUCTOS_H_INCLUDED
#define LISTAPRODUCTOS_H_INCLUDED

#include "productos.h"
//#include "arboles.h"

typedef struct _nodoListaProducto
{
    stProducto dato;
    struct _nodoListaProducto * siguiente;
}nodoListaProducto;

nodoListaProducto * inicListaProducto();
nodoListaProducto * crearNodoListaProducto(stProducto dato);
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista);
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
void mostrarListaRecursivaProductos(nodoListaProducto * lista, stProducto dato);
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id);
nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista);
//void copiarProdArbolLista(nodoArbol * arbol, nodoListaProducto ** lista, int idP);
#endif // LISTAPRODUCTOS_H_INCLUDED

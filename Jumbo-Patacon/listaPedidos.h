#ifndef LISTAPEDIDOS_H_INCLUDED
#define LISTAPEDIDOS_H_INCLUDED

#include "productos.h"

typedef struct
{
    int idPedido;
    int idCliente;
    char fecha[20];
    char descripcion[300];
    float costo;
    int pedidoAnulado;
    nodoListaProducto * producto;
} stPedido;

void pedidos(int idCliente);
stPedido cargarPedido(stPedido p, int idCliente);
void fechaPedido(stPedido * p);

void mostrarPedidosCliente(int idCliente);
void mostrarStructPedido(stPedido p);
int cantidadPedidos();
void buscarPedido();
void buscarPedidoCliente(int idCliente);
void archAltaPedido( stPedido p, int idCliente);
stPedido anularPedido (int idPedido, int idCliente,FILE *  archiP);
void modificarPedido(int idCliente);
stPedido modificacionPedidoCliente (stPedido p,int idPedido, int idCliente, FILE * archiP);

///Lista Pedidos

typedef struct _nodoListaPedidos
{
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


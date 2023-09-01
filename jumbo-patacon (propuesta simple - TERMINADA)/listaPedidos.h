#ifndef LISTAPEDIDOS_H_INCLUDED
#define LISTAPEDIDOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "productos.h"
#include "arbol.h"

///Lista Pedidos


//typedef struct
//{
//    int idPedido;
//    int idCliente;
//    int idProducto;
////    char fecha[20];
////    char descripcion[300];
////    float costo;
////    int pedidoAnulado;
//} stPedido;

typedef struct
{
	int idPedido;
	int idCliente;
	int idProducto;
} stPedido;


typedef struct _nodoListaPedidos
{
    stPedido p;  ///cabecera
    nodoListaProducto * listaDeProductos;///detalle
    struct _nodoListaPedidos * siguiente;
}nodoListaPedidos;

void pedidos(int idCliente);
stPedido cargarPedido(stPedido p, int idCliente, int idPedido);
void fechaPedido(stPedido * p);

void mostrarPedidosCliente(int idCliente);
void mostrarStructPedido(stPedido p);
int cantidadPedidos();
void mostrarListaRecursivaPedidos(nodoListaPedidos * lista);
void buscarPedido();
void buscarPedidoCliente(int idCliente);
void archAltaPedido( stPedido p, int idCliente);
stPedido anularPedido (int idPedido, int idCliente, FILE *  archiP);
void modificarPedido(int idCliente);
stPedido modificacionPedidoCliente (stPedido p,int idPedido, int idCliente, FILE * archiP);

void muestraProductosPedido(nodoListaProducto * lista);

int buscaIdUltimoPedido(char rutaDelArchivoPedido[]);

#endif // LISTAPEDIDOS_H_INCLUDED

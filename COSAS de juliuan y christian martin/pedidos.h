#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED
#include "listaProductos.h"
typedef struct
{
    int idPedido;
    int idCliente;
    char fecha[20];
    char descripcion[300];
    float costo;
    int pedidoAnulado;
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


#endif // PEDIDOS_H_INCLUDED

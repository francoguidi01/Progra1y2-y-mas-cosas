#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef struct
{
    int idProducto;
    char nombreProducto [30];
    char descripcionProducto [140];
    float valor;
    int cantidad;
    int productoAnulado;
} stProducto;

stProducto cargarUnProducto ();
void mostrarUnProducto(stProducto a);
void estadoDelProducto(int numero);
int contarProductos(char archivoProductos[]);
int deArchivoToArrayProductos (stProducto prods[], char archivo []);
void deArrayAArchivo(char archivoAPasar[], stProducto prods[], int validos);
void agregarDeArrayAArchivo(char archivoAPasar[], stProducto prods);

///Lista Prod
//typedef struct _nodoListaProducto
//{
//    stProducto p;
//    int idPedido;
//    struct _nodoListaProducto * siguiente;
//}nodoListaProducto;

typedef struct
{
    stProducto p;
    struct nodoListaProducto * siguiente;
} nodoListaProducto;


nodoListaProducto * inicListaProducto();
nodoListaProducto * crearNodoListaProducto(stProducto p);
nodoListaProducto * crearNodoListaProducto2(stProducto p, int idPedido);
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista);
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo);
void mostrarListaRecursivaProductos(nodoListaProducto * lista);
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id);
nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista);





#endif // PRODUCTOS_H_INCLUDED

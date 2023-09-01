#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>      /// Incluye un soporte para amplios tipos de caracteres.
#include <locale.h>     /// Incluye el soporte para distintos tipos de formatos de fecha, moneda, texto, etc.
#include <windows.h>

#include "arbol.h"
#include "productos.h"
#include "menu.h"
#include "clientes.h"
#include "listaPedidos.h"

void cargaDeDatosClientes(stCelda ADL[],char rutaDelArchivoClienteAlta [], char rutaDelArchivoClienteBaja [], int *validos, int *dimension);

int alta (stCelda adl[], stCliente cliente, int validos);

stPedido hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int pos);

void lista2ArchiDetallePedido (stCelda adl[], int validos, char archiDetallePedido[]);
void asociacionLista2Lista(char archiProductos[], stCelda adl [], int idCliente, int validos);

void deArchivoACabecera (stCelda adl[], char archivo [], int validos, int pos, nodoArbol * arbolProductos);
void deCabeceraAlArchivo(char archivoAPasar[], stPedido pedidoCliente);

void deArchivoAdetalle (stCelda adl[], char archivo [], int pos, int idPedido);

int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};

    char rutaDelArchivoProdAlta []= {"ProductosAlta.dat"};

   // char rutaDelArchivoPedidos []= {"Pedidos.dat"};
    char rutaDelArchivoCabeceraPedidos []= {"CabeceraPedidos.dat"};
    int validos=0, dimension=0;/* ultimoIdPedido=15;*/
    nodoArbol * arbolProd=inicArbol();
    dimension=contarClientes(rutaDelArchivoClienteAlta);
    stCelda * adl = (stCelda*) malloc(dimension*sizeof(stCelda));
    stPedido hola;
    validos=deArchivoAAdl(adl, rutaDelArchivoClienteAlta);
    mostrarAdlUser(adl, validos);
    //system("pause");
    stProducto arregloProductos [100];
    int i=deArchivoToArrayProductos(arregloProductos, rutaDelArchivoProdAlta);
    arbolProd=deArrayToArbol(arregloProductos,0,i-1);
    inorder(arbolProd);
    system("pause");

    hola=hacerPedidoMagicJohnson(adl, arbolProd, 1);
    deCabeceraAlArchivo(rutaDelArchivoCabeceraPedidos, hola);
    system("cls");
    deArchivoACabecera(adl,rutaDelArchivoCabeceraPedidos,validos,1,arbolProd);
    mostrarListaRecursivaProductos(adl[1].listaDeProductos);

    return 0;
}


stPedido hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int pos)
{
    stPedido pedidoCliente;
    nodoArbol * aux=inicArbol();
    stProducto prod;
    int idProducto=0;

    pedidoCliente.idCliente=adl[pos].cliente.idCliente;
    ///pedidoCliente.idPedido=ultmioIdPedido; No se la funcion jaja
    pedidoCliente.idPedido=0;


    ///Verificar que exista el producto
    inorder(arbolProductos);
    printf("\nQue producto desea agregar?: ");
    scanf("%d", &idProducto);

    pedidoCliente.idProducto=idProducto;
    aux=buscarPorID(arbolProductos, idProducto);
    prod=retornaProdNodo(aux);
    adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, crearNodoListaProducto(prod));
    return pedidoCliente;
}

void deCabeceraAlArchivo(char archivoAPasar[], stPedido pedidoCliente)
{
    FILE * archiCabecera=fopen(archivoAPasar,"ab");

    //int i=0;
    if (archiCabecera!=NULL)
    {
        fwrite(&pedidoCliente,sizeof(stPedido),1,archiCabecera);
    }
    fclose(archiCabecera);
}

void deArchivoACabecera (stCelda adl[], char archivo [], int validos, int pos, nodoArbol * arbolProductos)
{
    FILE * archiCabecera=fopen(archivo,"rb");
    stPedido aux;
    nodoArbol * prodAux=inicArbol();
    // int pos=-1;

    if (archiCabecera)
    {
        while(fread(&aux,sizeof(stPedido),1,archiCabecera)>0)
        {
            if (aux.idCliente==adl[pos].cliente.idCliente)
                ///pos=buscaPosIdClienteCelda(adl,aux.idCliente,validos);
                prodAux=buscarPorID(arbolProductos, aux.idProducto);
            adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, crearNodoListaProducto(prodAux->dato));
        }
        fclose(archiCabecera);
    }
}




int alta (stCelda adl[], stCliente cliente, int validos)
{
    nodoListaProducto * aux = inicListaProducto();
    //Te pide otra cosas nuesra funcion
    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;
    }
    adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, aux);
    return validos;
}


void cargaDeDatosClientes(stCelda ADL[],char rutaDelArchivoClienteAlta [], char rutaDelArchivoClienteBaja [], int *validos, int *dimension)
{
    *dimension =contarClientes(rutaDelArchivoClienteAlta);
    *validos=deArchivoAAdl(ADL, rutaDelArchivoClienteAlta);
    printf("Validos %d", *validos);
}


//void asociacionLista2Lista(char archiProductos[], stCelda adl [], int idCliente, int validos)
//{
//    FILE * archi=fopen(archiProductos,"rb");
//    nodoListaProducto * aux=inicListaProducto();
//    int pos=-1;
//    if(archi)
//    {
//        pos=buscaPosIdClienteCelda(adl,idCliente,validos);
//        while(fread(&aux->p,sizeof(stProducto),1,archi)>0)
//        {
//            if((aux->idPedido)==(adl[pos].listaDePedidos->p.idPedido))
//            {
//                adl[pos].listaDePedidos->listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDePedidos->listaDeProductos,crearNodoListaProducto(aux->p));
//            }
//        }
//        fclose(archi);
//    }
//}
//void lista2ArchiDetallePedido (stCelda adl[], int validos, char archiDetallePedido[])
//{
//    FILE * archi = fopen(archiDetallePedido,"wb");
//    int i=0;
//    stProducto aux2;
//    nodoListaProducto * aux=inicListaProducto();
//    nodoListaPedidos * listita=inicListaPedidos();
//    if(archi)
//    {
//        while(i<validos)
//        {
//            printf("primer while\n");
//            listita=adl[i].listaDePedidos;
//            while(listita!=NULL)
//            {
//                printf("2 while\n");
//                while(listita->listaDeProductos)
//                {
//                    printf("3 while\n");
//                    aux2.idProducto=listita->listaDeProductos->p.idProducto;
//                    printf("3 while despues primer aux\n");
//                    aux=crearNodoListaProducto2(aux2,listita->p.idPedido);
//                    printf("3 while despues segundo aux\n");
//
//                    fwrite(&aux,sizeof(nodoListaProducto),1,archi);
//                    printf("3 while despues de escribir\n");
//                    listita->listaDeProductos=listita->listaDeProductos->siguiente;
//                    printf("3 while despues de ti\n");
//                }
//                listita=listita->siguiente;
//                printf("2 while despues de ti\n");
//            }
//            i++;
//            printf("1 while despues de ti\n");
//        }
//    }
//    fclose(archi);
//}
//void deArchivoAdetalle (stCelda adl[], char archivo [], int pos, int idPedido)
//{
//    FILE * archi=fopen(archivo,"rb");
//    nodoListaProducto * aux=inicListaProducto();
//
//    if (archi)
//    {
//        while(fread(&aux,sizeof(nodoListaProducto),1,archi)>0 )
//        {
//            if(aux->idPedido==idPedido)
//            adl[pos].listaDePedidos->listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDePedidos->listaDeProductos,aux);
//
//        }
//        fclose(archi);
//    }
//}

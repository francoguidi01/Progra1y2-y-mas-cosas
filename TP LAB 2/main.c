#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>      /// Incluye un soporte para amplios tipos de caracteres.
#include <locale.h>     /// Incluye el soporte para distintos tipos de formatos de fecha, moneda, texto, etc.
#include <windows.h>

#include "menu.h"
#include "clientes.h"
#include "listaPedidos.h"
#include "productos.h"
#include "arbol.h"

void cargaDeDatosClientes(stCelda ADL[],char rutaDelArchivoClienteAlta [], char rutaDelArchivoClienteBaja [], int *validos, int *dimension);

int alta (stCelda adl[], stCliente cliente, int validos);

void cargaArbolProd(nodoArbol **arbolProd, char rutaDelArchivoProdAlta []);
void hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbol, int * idPedido, int pos);




void deArchivoACabecera (stCelda adl[], char archivo [], int validos);
void deCabeceraAlArchivo(char archivoAPasar[], stCelda adl[], int validos);



int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};
    //char rutaDelArchivoClienteBaja []= {"ClientesBaja.dat"};
    char rutaDelArchivoProdAlta []= {"ProductosAlta.dat"};
    //char rutaDelArchivoProdBaja []= {"ProductosBaja.dat"};
    //char rutaDelArchivoPedidos []= {"Pedidos.dat"};
    char rutaDelArchivoCabeceraPedidos []= {"CabeceraPedidos.dat"};
    int validos=0, dimension=0, ultimoIdPedido=15;
    nodoArbol * arbolProd=inicArbol();
    dimension =contarClientes(rutaDelArchivoClienteAlta);
    stCelda * ADL = (stCelda*) malloc(dimension*sizeof(stCelda));
    validos=deArchivoAAdl(ADL, rutaDelArchivoClienteAlta);

    cargaArbolProd(&arbolProd, rutaDelArchivoProdAlta);

    mostrarListaRecursivaPedidos(ADL[2].listaDePedidos);
    ///mostrarStructPedido(ADL[2].listaDePedidos->p);
    printf("\n [[[[[[[[[[[[[[[[[[%d]]]]]]]]]]]]]]]]]]]]]]]]]]]]",ultimoIdPedido);

    system("pause");
   // hacerPedidoMagicJohnson(ADL, arbolProd, &ultimoIdPedido, 1);
    //deCabeceraAlArchivo(rutaDelArchivoCabeceraPedidos, ADL, validos);
deArchivoACabecera(ADL, rutaDelArchivoCabeceraPedidos, validos);
    mostrarListaRecursivaPedidos(ADL[1].listaDePedidos);

        system("pause");

    return 0;
}


void hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int * idPedido, int pos)
{
    // int id=0;
    //char salir= ' ';
    // nodoArbol * aux=inicArbol();
    // stPedido prod;
    int idProducto=0;
    stPedido mani;

    mani=cargarPedido(mani,adl[pos].cliente.idCliente, *idPedido);

    inorder(arbolProductos);
    printf("\nSeleccione un ID de producto: ");
    scanf("%d", &idProducto);

    mani.idProducto=idProducto;


    adl[pos].listaDePedidos=crearNodoListaPedidos(mani);


    *idPedido=(*idPedido)+1;

//    while (salir!='s')
//    {
//        inorder(arbol);
//        printf("Que producto desea agregar al pedido? (Ingrese la ID)\n");
//        scanf("%i",  &id);
//        aux=buscarPorID(arbol, id);
//        prod=retornaProdNodo(aux);
//        lista=agregaProductosListaPedidos(&lista, prod);
//        printf("Desea continuar agregando productos? (s para salir)\n");
//        salir=getch();
//        system("cls");
//        mostrarUnProducto(lista->producto->p);
//        system("pause");
//    }
}

void deCabeceraAlArchivo(char archivoAPasar[], stCelda adl[], int validos)
{
    FILE * archiCabecera=fopen(archivoAPasar,"ab");

    int i=0;
    if (archiCabecera!=NULL)
    {
        while (i<validos)
        {
            fwrite(&adl[i].listaDePedidos->p,sizeof(stPedido),1,archiCabecera);
            i++;
        }
    }
    fclose(archiCabecera);
}

void deArchivoACabecera (stCelda adl[], char archivo [], int validos)
{
    FILE * archiCabecera=fopen(archivo,"rb");
    stPedido aux;
    int i=0;

    if (archiCabecera)
    {
        while(fread(&aux,sizeof(stPedido),1,archiCabecera)>0)
        {
            while (i<validos)
            {
            if (adl[i].cliente.idCliente==aux.idCliente)
            {
                adl[i].listaDePedidos=agregarAlPrincipioPedido(adl[i].listaDePedidos, crearNodoListaPedidos(aux));
                //adl[i].listaDePedidos=agregarAlPrincipioPedido(adl[i].listaDePedidos, crearNodoListaPedidos(aux));
            }
            i++;
            }

      //      i=agregarClienteCelda(adl,aux,i);
        }
        fclose(archiCabecera);
    }
}




int alta (stCelda adl[], stCliente cliente, int validos)
{
    nodoListaPedidos * aux = inicListaPedidos();
    //Te pide otra cosas nuesra funcion
    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;
    }
    adl[pos].listaDePedidos=agregarAlPrincipioPedido(adl[pos].listaDePedidos, aux);
    return validos;
}


void cargaDeDatosClientes(stCelda ADL[],char rutaDelArchivoClienteAlta [], char rutaDelArchivoClienteBaja [], int *validos, int *dimension)
{
    *dimension =contarClientes(rutaDelArchivoClienteAlta);
    *validos=deArchivoAAdl(ADL, rutaDelArchivoClienteAlta);
    printf("Validos %d", *validos);
}

void cargaArbolProd(nodoArbol **arbolProd, char rutaDelArchivoProdAlta [])
{
    *arbolProd=deArchivoAArbolProductos(*arbolProd,rutaDelArchivoProdAlta);
}


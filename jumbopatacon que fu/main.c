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

void lista2ArchiDetallePedido (stCelda adl[], int validos, char archiDetallePedido[]);
void asociacionLista2Lista(char archiProductos[], stCelda adl [], int idCliente, int validos);

void deArchivoACabecera (stCelda adl[], char archivo [], int validos);
void deCabeceraAlArchivo(char archivoAPasar[], stCelda adl[], int validos);

void deArchivoAdetalle (stCelda adl[], char archivo [], int pos, int idPedido);

int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};
    //char rutaDelArchivoClienteBaja []= {"ClientesBaja.dat"};
    char rutaDelArchivoProdAlta []= {"ProductosAlta.dat"};
    //char rutaDelArchivoProdBaja []= {"ProductosBaja.dat"};
    char rutaDelArchivoPedidos []= {"Pedidos.dat"};
    char rutaDelArchivoCabeceraPedidos []= {"CabeceraPedidos.dat"};
    int validos=0, dimension=0, ultimoIdPedido=15;
    nodoArbol * arbolProd=inicArbol();
    dimension =contarClientes(rutaDelArchivoClienteAlta);
    stCelda * ADL = (stCelda*) malloc(dimension*sizeof(stCelda));
    validos=deArchivoAAdl(ADL, rutaDelArchivoClienteAlta);

    cargaArbolProd(&arbolProd, rutaDelArchivoProdAlta);

    mostrarListaRecursivaPedidos(ADL[2].listaDePedidos);
    ///mostrarStructPedido(ADL[2].listaDePedidos->p);

    system("pause");
    //hacerPedidoMagicJohnson(ADL, arbolProd, &ultimoIdPedido, 1);
    //deCabeceraAlArchivo(rutaDelArchivoCabeceraPedidos, ADL, validos);
    deArchivoACabecera(ADL, rutaDelArchivoCabeceraPedidos, validos);
    //deArchivoAdetalle(ADL,rutaDelArchivoPedidos,1,0);
    mostrarListaRecursivaPedidos(ADL[1].listaDePedidos);
    mostrarListaRecursivaProductos(ADL[1].listaDePedidos->listaDeProductos);
    system("pause");

    //lista2ArchiDetallePedido(ADL,validos,rutaDelArchivoPedidos);
    return 0;
}


void hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int * idPedido, int pos)
{
    char salir= ' ';
    nodoArbol * aux=inicArbol();
    stProducto prod;
    int idProducto=0;
    stPedido mani;

    mani=cargarPedido(mani,adl[pos].cliente.idCliente, *idPedido);

    inorder(arbolProductos);
    mani.idProducto=idProducto;
    adl[pos].listaDePedidos=crearNodoListaPedidos(mani);

    while (salir!='s')
    {
        printf("Que producto desea agregar al pedido? (Ingrese la ID)\n");
        scanf("%d", &idProducto);
        aux=buscarPorID(arbolProductos, idProducto);
        prod=retornaProdNodo(aux);
        adl[pos].listaDePedidos=agregaProductosListaPedidos(adl[pos].listaDePedidos, prod);
        printf("Desea continuar agregando productos? (s para salir)\n");
        salir=getch();
        //  system("cls");
        system("pause");
    }

    *idPedido=(*idPedido)+1;

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
    int pos=-1;

    if (archiCabecera)
    {
        while(fread(&aux,sizeof(stPedido),1,archiCabecera)>0)
        {
            pos=buscaPosIdClienteCelda(adl,aux.idCliente,validos);

            adl[pos].listaDePedidos=agregarAlPrincipioPedido(adl[pos].listaDePedidos, crearNodoListaPedidos(aux));

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
void asociacionLista2Lista(char archiProductos[], stCelda adl [], int idCliente, int validos)
{
    FILE * archi=fopen(archiProductos,"rb");
    nodoListaProducto * aux=inicListaProducto();
    int pos=-1;
    if(archi)
    {
        pos=buscaPosIdClienteCelda(adl,idCliente,validos);
        while(fread(&aux->p,sizeof(stProducto),1,archi)>0)
        {
            if((aux->idPedido)==(adl[pos].listaDePedidos->p.idPedido))
            {
                adl[pos].listaDePedidos->listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDePedidos->listaDeProductos,crearNodoListaProducto(aux->p));
            }
        }
        fclose(archi);
    }
}
void lista2ArchiDetallePedido (stCelda adl[], int validos, char archiDetallePedido[])
{
    FILE * archi = fopen(archiDetallePedido,"wb");
    int i=0;
    stProducto aux2;
    nodoListaProducto * aux=inicListaProducto();
    nodoListaPedidos * listita=inicListaPedidos();
    if(archi)
    {
        while(i<validos)
        {
            printf("primer while\n");
            listita=adl[i].listaDePedidos;
            while(listita!=NULL)
            {
                printf("2 while\n");
                while(listita->listaDeProductos)
                {
                    printf("3 while\n");
                    aux2.idProducto=listita->listaDeProductos->p.idProducto;
                    printf("3 while despues primer aux\n");
                    aux=crearNodoListaProducto2(aux2,listita->p.idPedido);
                    printf("3 while despues segundo aux\n");

                    fwrite(&aux,sizeof(nodoListaProducto),1,archi);
                    printf("3 while despues de escribir\n");
                    listita->listaDeProductos=listita->listaDeProductos->siguiente;
                    printf("3 while despues de ti\n");
                }
                listita=listita->siguiente;
                printf("2 while despues de ti\n");
            }
            i++;
            printf("1 while despues de ti\n");
        }
    }
    fclose(archi);
}
void deArchivoAdetalle (stCelda adl[], char archivo [], int pos, int idPedido)
{
    FILE * archi=fopen(archivo,"rb");
    nodoListaProducto * aux=inicListaProducto();

    if (archi)
    {
        while(fread(&aux,sizeof(nodoListaProducto),1,archi)>0 )
        {
            if(aux->idPedido==idPedido)
            adl[pos].listaDePedidos->listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDePedidos->listaDeProductos,aux);

        }
        fclose(archi);
    }
}







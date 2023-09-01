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



void lista2ArchiDetallePedido (stCelda adl[], int validos, char archiDetallePedido[]);
void asociacionLista2Lista(char archiProductos[], stCelda adl [], int idCliente, int validos);



int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};
    int validos=0, dimension=0;
    dimension=contarClientes(rutaDelArchivoClienteAlta);
    stCelda * adl = (stCelda*) malloc(dimension*sizeof(stCelda));
    validos=deArchivoAAdl(adl, rutaDelArchivoClienteAlta);




































    menuNavegable(adl,&validos,&dimension);
//   system("pause");
    return 0;
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

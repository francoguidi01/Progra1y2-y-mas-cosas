#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>


#include "arbol.h"
#include "productos.h"
#include "menu.h"
#include "clientes.h"

///FALTA EL BORRAR LOS DATOS EN TIEMPO DE EJECUCIÓN


int alta (stCelda adl[], stCliente cliente, int validos);
void borrarTodo (stCelda **adl, int * validos);

int main()
{
    char rutaDelArchivoClienteAlta []= {"ClientesAlta.dat"};

    int validos=0, dimension=0;

    logo();

    dimension=contarClientes(rutaDelArchivoClienteAlta);

    stCelda * adl = (stCelda*) malloc(dimension*sizeof(stCelda));

    validos=deArchivoAAdl(adl, rutaDelArchivoClienteAlta);

    menuNavegable(adl,&validos,&dimension);

    return 0;
}

int alta (stCelda adl[], stCliente cliente, int validos) ///Por temas de librerias se debe dejar en el main o rompe
{
    nodoListaProducto * aux = inicListaProducto();

    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;
    }
    adl[pos].listaDeProductos=agregarAlPrincipioProducto(adl[pos].listaDeProductos, aux);
    return validos;
}



void borrarTodo (stCelda **adl, int * validos)
{
    int i=(*validos)-1;
    while (i>1)
    {
        if ((*adl)[i].listaDeProductos!=NULL)
        {
            (*adl)[i].listaDeProductos=borrarTodaLaListaProducto((*adl)[i].listaDeProductos);
        }


        //  printf("hola\n");
        i--;
    }
    *validos=i;
    printf("%d ", *validos);
    system("pause");
}






















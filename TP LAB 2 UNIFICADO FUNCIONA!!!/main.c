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

int alta (stCelda adl[], stCliente cliente, stProducto x, int validos);

int main()
{
    char rutaDelArchivo []= {"Clientes.dat"};
    int validos=0;
    validos=contarClientes(rutaDelArchivo);
    int dimension = validos;
    stCelda * ADL = (stCelda*) malloc(dimension*sizeof(stCelda));
    validos=deArchivoAAdl(ADL, rutaDelArchivo);
    menuNavegable(ADL,&validos,&dimension);
    deAdlAlArchivo(rutaDelArchivo,ADL,validos);
    mostrarAdlAdmin(ADL,validos);
    return 0;
}

int alta (stCelda adl[], stCliente cliente, stProducto x, int validos)
{
    nodoListaProducto * aux = crearNodoListaProducto(x);


    //Te pide otra cosas nuesra funcion
    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;

    }
    adl[pos].listaDeProductos=agregarAlPrincipioPedido(adl[pos].listaDeProductos, aux);
    return validos;
}


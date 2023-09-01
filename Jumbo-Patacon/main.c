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


#include "productos.h"
#include "nodoArbol.h"

int main()
{
char rutaDelArchivo []= {"Clientes.dat"};

    int validos=0;

    validos=contarClientes(rutaDelArchivo);
    int dimension = validos;

    saltoDeLinea(2);
    printf("Total de clientes en archivo: %d",validos);
    saltoDeLinea(2);

    stCelda * ADL = (stCelda*) malloc(dimension*sizeof(stCelda));

    validos=deArchivoAAdl(ADL, rutaDelArchivo);

    mostrarAdlAdmin(ADL,validos);
    system("pause");

   // modificarCliente(ADL,107,validos);

    menuNavegable(ADL,&validos,&dimension);

    deAdlAlArchivo(rutaDelArchivo,ADL,validos);

    mostrarAdlAdmin(ADL,validos);
    return 0;
}

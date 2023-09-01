#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

//#include "cosasdepersonas.h" /// para que no te tire bronca la linea 13.
#include "productos.h"

///#define Pila nodo *

typedef struct _nodo
{
    stProducto dato;
    struct _nodo * siguiente;
} nodoListaProducto;
///---------------------------------------------------------------------------------------
//typedef struct
//{
//    char patente[6];
//    int valor;
//    char marca[10];
//} automovil;
//
//typedef struct _nodoAuto
//{
//    automovil dato;
//    struct _nodoAuto * siguiente;
//} nodoAuto;
/// TP FINAL
nodoListaProducto * inicLista();
nodoListaProducto * crearNodo (stProducto dato);
nodoListaProducto * agregarNodoNuevoAlPrincipio (nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarEnOrden (nodoListaProducto * lista, nodoListaProducto * nuevoNodo);
nodoListaProducto * agregarNodoNuevoAlFinal (nodoListaProducto * lista, nodoListaProducto * nuevoNodo);

nodoListaProducto * borrarNodoAEleccionPorId(nodoListaProducto * lista, int id);

void mostrarNodoRecursivo (nodoListaProducto * lista);
void mostrarUnSoloDatoR (nodoListaProducto*lista);




///--------------------------------------------------------NODOS--------------------------------------------------------------


nodoListaProducto * borrarNodoAEleccionPorNombre(nodoListaProducto * lista, char nombre[20]);
nodoListaProducto * borrarTodaLaLista(nodoListaProducto * lista);
int buscarNodoPorNombre (nodoListaProducto * lista, char nombre[20]);
nodoListaProducto * buscarUltimo (nodoListaProducto * lista);
nodoListaProducto * cargarElNodo (nodoListaProducto* lista);
nodoListaProducto * crearNodo (stProducto dato);
nodoListaProducto * deArchivoALista (nodoListaProducto * lista, char archivo []);
nodoListaProducto * desvincularNodo (nodoListaProducto ** lista);
nodoListaProducto * eliminarPrimero (nodoListaProducto * lista);
nodoListaProducto * eliminarUltimo (nodoListaProducto * lista);

nodoListaProducto * invertirLista (nodoListaProducto * lista);
nodoListaProducto * intercalarListas(nodoListaProducto* lista_1,nodoListaProducto* lista_2);
void mostrarLista (nodoListaProducto*lista);
nodoListaProducto * subProgramaAgregarAlFinal(nodoListaProducto * lista, stProducto dato);
int sumarEdadesLista(nodoListaProducto * lista);

///------------------------------------------------------NODOS RECURSIVOS----------------------------------------------------

nodoListaProducto * borrarNodoRecursivoAEleccion (nodoListaProducto * lista, char flaco []);
nodoListaProducto * BorrarTodaLaListaRecursivo (nodoListaProducto * lista);
nodoListaProducto * invertirListaRecursiva (nodoListaProducto * lista);
void mostrarNodoParRecursivo (nodoListaProducto * lista);
void mostrarNodoRecursivoInvertida (nodoListaProducto * lista);
int sumarListaRecursiva(nodoListaProducto * lista);

///---------------------------------------------------------Nodos AUTOS-------------------------------------------------------

//void agregarNodoNuevoAlFinalPunteroDoble (nodoAuto ** lista, nodoAuto * nuevoNodo);
//automovil cargarUnAuto ();
//nodoAuto * buscarUltimoAuto (nodoAuto * lista);
//nodoAuto * cargarElNodoDeAutos (nodoAuto * lista);
//nodoAuto * crearNodoAuto (automovil dato);
//void mostrarListaAutos (nodoAuto*lista);
//void mostrarUnAuto(automovil a);

#endif // NODO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "listaJugadores.h"
#include "Pila.h"


/// 3.c
int subProgramaOnceIdeal(nodoJugador ** plista, stJugador A[], int dim);

/// 4.c
void subProgramaPorcentaje(nodoJugador * lista);

/// 5
void mostrarArregloJugadoresR(stJugador A[], int validos, int i);

/// 6.b
void copiarDeLista2Pila(nodoJugador * lista, Pila * pilita);

int main()
{
    printf("Hello world primer parcial!\n");

    /// 1
    nodoJugador * listita=inicLista();
    listita=archivo2lista("jugadores.dat", listita);

    printf("\nSe paso el archivo a la lista!\n");
    system("pause");

    ///2
    printf("\nContenido de la lista: \n");
    muestraListaRecursiva(listita);

    printf("\n");
    system("pause");

    /// 3
    stJugador MisJugadores[11];
    int valid=0;

    printf("\nBuscando mejores jugadores !\n");
    valid=subProgramaOnceIdeal(&listita, MisJugadores, 11);
    system("pause");

    /// 5
    printf("\nLos mojeres: \n");
    mostrarArregloJugadoresR(MisJugadores, valid, 0);
    system("pause");


    /// 4
    printf("\nVemos las cantidades y el porcentaje!\n");

    subProgramaPorcentaje(listita);
    system("pause");

    /// 6

    Pila pilita;
    inicPila(&pilita);

    printf("\nCopiando Jugadores a la pila\n");
    copiarDeLista2Pila(listita, &pilita);
    system("pause");

    printf("Contenido de la pila de jugadores: \n");
    mostrar(&pilita);
    system("pause");

    return 0;
}

int subProgramaOnceIdeal(nodoJugador ** plista, stJugador A[], int dim)
{
    int i=0, idJugador;
    stJugador aux;

    while((*plista)!=NULL && i<dim)
    {
        idJugador=mejorGoleador(*plista);

        aux=borrarJugadorSegunId(plista, idJugador);

        A[i]=aux;

        i++;
    }
    return i;
}

void mostrarArregloJugadoresR(stJugador A[], int validos, int i)
{
    if(i<validos)
    {
        mostrarArregloJugadoresR(A, validos, i+1);
        mostrarUnRegistro(A[i]);
    }
}

void subProgramaPorcentaje(nodoJugador * lista)
{
    int total, filtro;
    float valor=0, porcent;
    printf("\n Ingrese el valor para filtrar: ");
    scanf("%f", &valor);

    total=contarRecursivoLista(lista);
    filtro=contarRecursivoConFiltro(lista, valor);

    porcent=((float) filtro*100)/(float)total;

    printf("\n El total de jugadores en la lista es %d\n", total);
    printf("\n La cantidad de jugadores con un promedio de gol superior a % .2f en la lista es %d\n",valor, filtro);
    printf("\n Y corresponde a un %.2f %% del total de la lista\n", porcent);
}


void copiarDeLista2Pila(nodoJugador * lista, Pila * pilita)
{
    stJugador aux;
    nodoJugador * seg=lista;

    while(seg)
    {
        if(seg->dato.goles>10&&seg->dato.promedioDeGol>0.4)
        {
            aux=seg->dato;

            apilar(pilita, aux);
        }
        seg=seg->siguiente;
    }
}

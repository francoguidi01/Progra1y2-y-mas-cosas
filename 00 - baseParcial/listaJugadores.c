#include <stdio.h>
#include <stdlib.h>
#include "listaJugadores.h"


nodoJugador* inicLista()
{
    return NULL;
}
///1
nodoJugador* crearNodoJugador(stJugador dato)
{
    nodoJugador* nuevonodoJugador = (nodoJugador*)malloc(sizeof(nodoJugador));
    nuevonodoJugador->dato = dato;
    nuevonodoJugador->siguiente = NULL;
    return nuevonodoJugador;
}

nodoJugador* agregaAlFinalRecursiva(nodoJugador * lista, nodoJugador *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        lista->siguiente=agregaAlFinalRecursiva(lista->siguiente, nuevo);
    }
    return lista;
}

nodoJugador* archivo2lista(char arJugadores[], nodoJugador * lista)
{
    stJugador p;

    FILE * pArch = fopen(arJugadores,"rb");

    if(pArch)
    {
        while(fread(&p,sizeof(stJugador),1,pArch)>0)
        {
            nodoJugador* nuevo = crearNodoJugador(p);
            lista = agregaAlFinalRecursiva(lista,nuevo);
        }
        fclose(pArch);
    }
    return lista;
}


/// 2
void muestraListaRecursiva(nodoJugador* lista)
{
    if(lista)
    {
        /// podemos agregar tambien la fn mostrarUnNodo
        mostrarUnRegistro(lista->dato);
        muestraListaRecursiva(lista->siguiente);
    }
}


/// 3
int mejorGoleador(nodoJugador *lista)
{
    nodoJugador * mejor;
    nodoJugador * seg;

    if(lista)
    {
        mejor=lista; ///supongo el primero como el mejor

        seg=lista->siguiente; /// cargo el siguiente para iterar

        while(seg)
        {
            if(seg->dato.goles>mejor->dato.goles)
            {
                mejor=seg;
            }
            seg=seg->siguiente;
        }
    }

    return mejor->dato.idJugador;
}

stJugador borrarJugadorSegunId(nodoJugador ** lista, int idJugador)
{

    stJugador j;
    if(*lista)
    {
        if((*lista)->dato.idJugador==idJugador)
        {
            nodoJugador * aBorrar=*lista;
            *lista=(*lista)->siguiente;

            j=aBorrar->dato;

            free(aBorrar);
        }
        else
        {
            nodoJugador *ante=*lista;
            nodoJugador *seg=(*lista)->siguiente;

            while(seg && seg->dato.idJugador!=idJugador)
            {
                ante=seg;
                seg=seg->siguiente;
            }

            if(seg)
            {
                ante->siguiente = seg->siguiente;

                j=seg->dato;

                free(seg);
            }
        }
    }

    return j;
}

/// 4
///a
int contarRecursivoLista(nodoJugador * lista)
{
    int cant=0;
    if(lista)
    {
        cant=1+contarRecursivoLista(lista->siguiente);
    }
    return cant;
}
///b
int contarRecursivoConFiltro(nodoJugador * lista, float valor)
{
    int cant=0;
    if(lista)
    {
        if(lista->dato.promedioDeGol>valor)
        {
            cant=1+contarRecursivoConFiltro(lista->siguiente, valor);
        }
        else
        {
            cant=0+contarRecursivoConFiltro(lista->siguiente, valor);
        }
    }
    return cant;
}

/// fns para Pila
nodoJugador* agregarAlPrincipio(nodoJugador* lista, nodoJugador* nuevo)
{
    nuevo->siguiente = lista;
    return nuevo;
}




#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#define Pila nodoJugador *

typedef struct
{
    int idJugador;
    char nombre[20];
    char apellido[20];
    char dni[10];
    int edad;
    char posicion[12];              /// Arquero, Defensa, Medio Campo, Delantero
    char equipo[30];
    int goles;
    float promedioDeGol;        /// indica el promedio de gol del jugador (en el torneo se jugaron 30 fechas)
} stJugador;

typedef struct _nodo{
    stJugador dato;
    struct _nodo* siguiente;
} nodoJugador;

nodoJugador * inicListaJugadores ();

///Punto 1
nodoJugador * crearNodo (stJugador dato);
void insertarAlFinalRecursivoPunteroDoble(nodoJugador ** lista, nodoJugador * nuevoNodo);
nodoJugador * subProgramaDeArchivoALista (nodoJugador * lista, char archivo []);

///Punto 2
void mostrarNodoRecursivo (nodoJugador * lista);
void mostrarUnSoloDatoR (nodoJugador * lista);
void mostrarUnJugador(stJugador a);

///Punto 3
int buscarNodoJugadorPorGol (nodoJugador * lista);
stJugador borrarNodoAEleccion (nodoJugador ** lista, int idJug);
nodoJugador * listaToArray (nodoJugador * lista, stJugador jug[]);

///Punto 4
int contarCantJug(nodoJugador * lista);
int contarCantJugConFiltro(nodoJugador * lista, float minProm);
void subProgramaGoles(nodoJugador * lista, float minProm);

///Punto 5
void mostrarArregloRecursivo (stJugador A[], int validos, int i);

///Punto 6
void inicPila(Pila * pila);
void apilar (Pila * pila, stJugador dato);
Pila agregarAPila (Pila * pila, Pila nuevaPila);
void listaToPila(Pila * pilaJugadores, nodoJugador * lista);
void mostrarPila (Pila pila);

///Punto 7 Main
int main()
{
    ///Punto 1
    char rutaDelArchivo []= {"jugadores.dat"};
    nodoJugador * listaJugador = inicListaJugadores();
    listaJugador = subProgramaDeArchivoALista(listaJugador, rutaDelArchivo);
    ///Punto 2
    mostrarNodoRecursivo(listaJugador);
    ///Punto 3
    stJugador arregloJugadores [15];
    listaJugador= listaToArray(listaJugador, arregloJugadores);
    ///Punto 4
    float i =0;
    printf("\n Que promedio minimo de gol?: ");
    scanf("%f", &i);
    subProgramaGoles(listaJugador, i);
    ///Punto 5
    mostrarArregloRecursivo(arregloJugadores, 11, 0);
    ///Punto 6
    Pila pilita;
    inicPila(&pilita);
    listaToPila(&pilita, listaJugador);
    mostrarPila(pilita);
    return 0;
}

nodoJugador * inicListaJugadores ()
{
return NULL;
}

///Punto 1
///a)
nodoJugador * crearNodo (stJugador dato)
{
    nodoJugador * aux = (nodoJugador*) malloc(sizeof (nodoJugador));
    aux -> dato = dato;
    aux -> siguiente = NULL;
    return aux;
}
///b)
void insertarAlFinalRecursivoPunteroDoble(nodoJugador ** lista,nodoJugador * nuevoNodo)
{
    if(*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        insertarAlFinalRecursivoPunteroDoble(&((*lista)->siguiente), nuevoNodo);
    }
}
///c)
nodoJugador * subProgramaDeArchivoALista (nodoJugador * lista, char archivo [])
{
    stJugador aux;

    FILE * archiJugadores=fopen(archivo,"rb");
    if (archiJugadores)
    {
        while(fread(&aux,sizeof(stJugador),1,archiJugadores)>0)
        {
            insertarAlFinalRecursivoPunteroDoble(&lista, crearNodo(aux));
        }
        fclose(archiJugadores);
    }
    return lista;
}

///Punto 2
void mostrarNodoRecursivo (nodoJugador * lista)
{
    if(lista != NULL)
    {
        mostrarUnSoloDatoR(lista);
        mostrarNodoRecursivo(lista->siguiente);
    }
}

void mostrarUnSoloDatoR (nodoJugador * lista)
{
    nodoJugador * aux = lista;

    mostrarUnJugador(aux->dato);
    aux=aux->siguiente;
}

void mostrarUnJugador(stJugador a)
{
    puts("\n---------------");
    printf("\n Id del jugador: %d", a.idJugador);
    printf("\n Nombre del Jugador: %s",a.nombre);
    printf("\n Apellido del Jugador: %s",a.apellido);
    printf("\n El dni del Jugador: %s", a.dni);
    printf("\n La edad del Jugador: %d", a.edad);
    printf("\n La posicion del Jugador: %s", a.posicion);
    printf("\n El equipo del Jugador: %s", a.equipo);
    printf("\n Los goles del Jugador: %d", a.goles);
    printf("\n El promedio de gol del Jugador: %0.02f", a.promedioDeGol);
    puts("\n---------------");
}
///Punto 3
///a)
int buscarNodoJugadorPorGol (nodoJugador * lista)
{
    int mayor=0, auxIdJug=0;

    if (lista)
    {
        mayor= lista->dato.goles;
    }
    while (lista != NULL )
    {
        if (lista->dato.goles > mayor)
        {
            auxIdJug=lista->dato.idJugador;
            mayor=lista->dato.goles;
        }
        lista=lista->siguiente;
    }
    return auxIdJug;
}

///b)
stJugador borrarNodoAEleccion (nodoJugador ** lista, int idJug)
{
    stJugador a;
    nodoJugador * seg;
    nodoJugador * ante;
    if(((*lista) != NULL) && (*lista)->dato.idJugador==idJug)
    {
        a=(*lista)->dato;
        nodoJugador * aux = (*lista);
        (*lista) = (*lista)->siguiente;
        free(aux);
    }
    else
    {
        seg = (*lista);

        while((seg != NULL) && (*lista)->dato.idJugador!=idJug)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg!=NULL)
        {
            a=(*lista)->dato;
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return a;
}

///c)
nodoJugador * listaToArray (nodoJugador * lista, stJugador jug[])
{
    int i=0;
    while (i < 11)
    {
     jug [i] = borrarNodoAEleccion(&lista,buscarNodoJugadorPorGol(lista));
     i++;
    }
    return lista;
}

///Punto 4
///a)
int contarCantJug(nodoJugador * lista)
{
    int rta=0;

    if(lista == NULL)
    {
        rta=0;
    }
    else
    {
        rta= 1 + (contarCantJug(lista->siguiente));
    }
    return rta;
}

///b)

int contarCantJugConFiltro(nodoJugador * lista, float minProm)
{
    int rta=0;

    if(lista == NULL)
    {
        rta=0;
    }
    else
    {
        if (lista->dato.promedioDeGol>minProm)
        {
         rta= 1 + (contarCantJugConFiltro(lista->siguiente, minProm));
        }
        else
        {
            rta= 0 + (contarCantJugConFiltro(lista->siguiente, minProm));
        }

    }
    return rta;
}

///c

void subProgramaGoles(nodoJugador * lista, float minProm)
{
    int cantJugadores = contarCantJug(lista);
    int cantJugadoresProm = contarCantJugConFiltro(lista, minProm);
    float porcentaje = (cantJugadores/cantJugadoresProm);
    printf("\nLa cantidad de jugadores es: %d \n", cantJugadores);
    printf("\nLa cantidad de jugadores con un promedio de gol mas alto que %0.02f es: %d \n", minProm,cantJugadoresProm);
    printf("\nEl procentaje es: %0.02f \n", porcentaje);

}

///Punto 5

void mostrarArregloRecursivo (stJugador A[], int validos, int i)
{

    if (i == validos - 1)
    {
       mostrarUnJugador(A[i]);
    }
    else
    {
        mostrarArregloRecursivo(A,validos, i+1);
        mostrarUnJugador(A[i]);
    }
}

///Punto 6

///a)
void inicPila(Pila * pila)
{
    (*pila)=inicListaJugadores();
}

void apilar (Pila * pila, stJugador dato)
{
    Pila nueva = crearNodo(dato);
    (*pila) = agregarAPila(&(*pila), nueva);
}

Pila agregarAPila (Pila * pila, Pila nuevaPila)
{
    if((*pila) == NULL)
    {
        (*pila) = nuevaPila;
    }
    else
    {
        nuevaPila->siguiente = (*pila);
        (*pila) = nuevaPila;
    }
    return *pila;
}

///b)
void listaToPila(Pila * pilaJugadores, nodoJugador * lista)
{
    nodoJugador * aux=lista;
    while (aux)
    {
        if ((lista->dato.goles>10) && (lista->dato.promedioDeGol> 0.04))
        {
         apilar(&(*pilaJugadores), lista->dato);
        }
        else
        {
            aux=aux->siguiente;
        }
    }
}

void mostrarPila (Pila pila)
{
    printf("Tope\n");
    mostrarNodoRecursivo(pila);
    printf("Base\n");
}



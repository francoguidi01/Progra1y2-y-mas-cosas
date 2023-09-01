#ifndef LISTAPERSONAS_H_INCLUDED
#define LISTAPERSONAS_H_INCLUDED

#include "stJugador.h"

typedef struct _nodo{
    stJugador dato;
    struct _nodo* siguiente;
}nodoJugador;


nodoJugador* inicLista();

/// 1
///a
nodoJugador* crearNodoJugador(stJugador dato);
///b
nodoJugador* agregaAlFinalRecursiva(nodoJugador * lista, nodoJugador *nuevo);
/// c
nodoJugador* archivo2lista(char arJugadores[], nodoJugador* lista);


///2
void muestraListaRecursiva(nodoJugador* lista);

/// 3
int mejorGoleador(nodoJugador *lista);
stJugador borrarJugadorSegunId(nodoJugador ** lista, int idJugador);

/// 4
int contarRecursivoLista(nodoJugador * lista);
int contarRecursivoConFiltro(nodoJugador * lista, float valor);

/// fns para Pila
nodoJugador* agregarAlPrincipio(nodoJugador* lista, nodoJugador* nuevo);

#endif // LISTAPERSONAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "nodo.h"
#include "productos.h"
#include "nodoDoble.h"
#include "arboles.h"

nodoDoble * deNodoSimpleADoble (nodo * lista, nodoDoble * listaDoble);
nodo * arbolToLista(nodoArbol * arbol, nodo * lista);
///lista->dato.nombre[0]== letra  Encontras la primer letra del string
///strlen (lista->dato.nombre)-1 Encontras la ultima letra del string, esta buenisimo

/*int main()
{
    nodo * lista= inicLista();
    nodoArbol * osvaldo = inicArbol();
    osvaldo= cargarElArbol(osvaldo);
    arbolToLista(osvaldo, &lista);
    mostrarLista(lista);
    printf("\n--------------------------------------------\n");
    printf("%s",NULL);
    return 0;
}

*/
nodoDoble * deNodoSimpleADoble (nodo * lista, nodoDoble * listaDoble)
{
    while(lista)
    {
        listaDoble=agregarEnOrdenDoble(listaDoble, crearNodoDoble(lista->dato));
        lista=lista->siguiente;
    }
    return listaDoble;

}



nodo * arbolToLista(nodoArbol * arbol, nodo * lista)
{
    nodo * aux =NULL;
        if(arbol != NULL)
    {

        lista=arbolToLista(arbol->izq, lista);
        aux=crearNodo(arbol->dato);
        lista=agregarNodoNuevoAlFinal(lista, aux);
        lista=arbolToLista(arbol->der,lista);
      //  *lista=agregarNodoNuevoAlPrincipio((*lista),crearNodo(arbol->dato));
    }
    return lista;
}



//nodo * arbolToLista (nodoArbol* osvaldo, nodo* lista)
//{
//    nodoArbol* derecho=osvaldo;
//    nodoArbol* izquierdo=osvaldo;
//    while(derecho)
//    {
//    lista=agregarNodoNuevoAlPrincipio(lista, crearNodo(derecho->dato));
//    derecho=derecho->der;
//    }
//    while(izquierdo)
//    {
//    lista=agregarNodoNuevoAlPrincipio(lista, crearNodo(izquierdo->dato));
//    izquierdo=izquierdo->izq;
//    }
//    return lista;
//}

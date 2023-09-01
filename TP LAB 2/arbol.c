#include "arbol.h"


nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodoArbol(stProducto dato)
{
    nodoArbol * aux = (nodoArbol*) malloc(sizeof(nodoArbol));
    aux->dato=dato;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}
nodoArbol * cargarElArbol (nodoArbol * arbol)
{
    nodoArbol * nuevoNodoArbol;
    char control ='s';

    while (control=='s')
    {
        nuevoNodoArbol = crearNodoArbol(cargarUnProducto());
        arbol=insertarPorId(arbol,nuevoNodoArbol->dato);

        printf("\nDesea agragar otro producto? (S/N): ");
        fflush(stdin);
        scanf("%c", &control);
        system("cls");
    }
    return arbol;
}
nodoArbol * insertarPorId(nodoArbol * arbol, stProducto dato)
{
    if(arbol==NULL)
        arbol = crearNodoArbol(dato);
    else
    {
        if( dato.idProducto > (arbol->dato.idProducto))
            arbol->der = insertarPorId(arbol->der, dato);
        else
            arbol->izq = insertarPorId(arbol->izq, dato);
    }
    return arbol;
}

void preorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        mostrarUnProducto(arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        inorder(arbol->izq);
        mostrarUnProducto(arbol->dato);
        inorder(arbol->der);
    }
}

void postorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrarUnProducto(arbol->dato);
    }
}

nodoArbol * buscar(nodoArbol * arbol, stProducto dato)
{
    nodoArbol * rta = inicArbol();
    if(arbol!=NULL)
    {
        if(dato.idProducto == arbol->dato.idProducto)
            rta = arbol;
        else if(dato.idProducto > arbol->dato.idProducto)
            rta = buscar(arbol->der, dato);
        else
            rta = buscar(arbol->izq, dato);
    }
    return rta;
}

nodoArbol * buscarPorID(nodoArbol * arbol, int id)
{
    nodoArbol * rta = inicArbol();
    if(arbol!=NULL)
    {
        if(id == arbol->dato.idProducto)
            rta = arbol;
        else if(id > arbol->dato.idProducto)
            rta = buscarPorID(arbol->der, id);
        else
            rta = buscarPorID(arbol->izq, id);
    }
    return rta;
}


nodoArbol * deArchivoAArbolProductos (nodoArbol * arbol, char archivo [])
{
    stProducto aux;

    FILE * productoslista=fopen(archivo,"rb");
    if (productoslista)
    {
        while(fread(&aux,sizeof(stProducto),1,productoslista)>0)
        {
            arbol=insertarPorId(arbol,aux);
        }
        fclose(productoslista);
    }
    return arbol;
}

nodoArbol * deArrayToArbol(stProducto dato[], int principio, int fin)
{
    if (principio > fin)
    {
        return NULL;
    }

    int mitad = (principio + fin)/2;

    nodoArbol * raiz = crearNodoArbol(dato[mitad]);

    raiz->izq =  deArrayToArbol(dato, principio, mitad-1);

    raiz->der = deArrayToArbol(dato, mitad+1, fin);

    return raiz;
}

nodoArbol * nodoMasDerecho (nodoArbol* arbol)
{
    nodoArbol * resp;

    if (arbol)
    {
        if (arbol->der)
        {
            resp=nodoMasDerecho(arbol->der);
        }
        else
        {
            resp=arbol;
        }
    }
    return resp;
}

nodoArbol * nodoMasIzquierdo (nodoArbol* arbol)
{
    nodoArbol * resp;

    if (arbol)
    {
        if (arbol->izq)
        {
            resp=nodoMasIzquierdo(arbol->izq);
        }
        else
        {
            resp=arbol;
        }
    }
    return resp;
}

nodoArbol * borrarNodoArbol (nodoArbol * osvaldo, stProducto dato)
{
    if (osvaldo)
    {
        if (osvaldo->dato.idProducto==dato.idProducto)
        {
            if (osvaldo->izq)
            {
                nodoArbol * masDer = nodoMasDerecho(osvaldo->izq);
                osvaldo->dato = masDer->dato;
                osvaldo->izq = borrarNodoArbol(osvaldo->izq, masDer->dato);
            }
            else if (osvaldo->der)
            {
                nodoArbol * masIzq = nodoMasIzquierdo(osvaldo->der);
                osvaldo->dato = masIzq->dato;
                osvaldo->der = borrarNodoArbol(osvaldo->der, masIzq->dato);
            }
            else
            {
                free(osvaldo);
                osvaldo=NULL;
            }
        }
        else if (dato.idProducto>osvaldo->dato.idProducto)
        {
            osvaldo->der=borrarNodoArbol(osvaldo->der, dato);
        }
        else
        {
            osvaldo->izq=borrarNodoArbol(osvaldo->izq, dato);
        }
    }

    return osvaldo;
}

stProducto retornaProdNodo (nodoArbol * arbol)
{
    stProducto aux=arbol->dato;
    return aux;
}







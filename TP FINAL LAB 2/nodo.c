#include "nodo.h"

nodoListaProducto * inicLista()
{
    return NULL;
}

nodoListaProducto * crearNodo (stProducto dato)
{
    nodoListaProducto * aux = (nodoListaProducto*) malloc(sizeof (nodoListaProducto));
    aux -> dato = dato;
    aux -> siguiente = NULL;
    return aux;
}

void mostrarLista (nodoListaProducto*lista)
{
    nodoListaProducto * aux = lista;

    while (aux != NULL)
    {
        mostrarUnProducto(aux->dato);
        aux=aux->siguiente;
    }
}

void mostrarUnSoloDatoR (nodoListaProducto*lista)
{
    mostrarUnProducto(lista->dato);
    lista=lista->siguiente;
}

nodoListaProducto * agregarNodoNuevoAlPrincipio (nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoListaProducto * cargarElNodo (nodoListaProducto* lista)
{
    nodoListaProducto * nuevoNodo;
    char control ='s';
    while (control=='s')
    {
        nuevoNodo = crearNodo(cargarUnProducto());
        lista=agregarNodoNuevoAlPrincipio(lista,nuevoNodo);

        printf("\nDesea agragar otro producto? (S/N): ");
        fflush(stdin);
        scanf("%c", &control);
        system("cls");
    }
    return lista;
}

nodoListaProducto * buscarUltimo (nodoListaProducto * lista)
{
    nodoListaProducto * ultimo = lista;
    if (ultimo!= NULL)
    {
        while (ultimo -> siguiente != NULL)
        {
            ultimo=ultimo->siguiente;
        }
    }
    return ultimo;
}


nodoListaProducto * agregarNodoNuevoAlFinal (nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    nodoListaProducto * ultimo = NULL;
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo= buscarUltimo(lista);
        ultimo->siguiente=nuevoNodo;
    }
    return lista;
}

nodoListaProducto * agregarEnOrden (nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if (strcmp(nuevoNodo->dato.nombre, lista->dato.nombre)<0)
        {
            lista=agregarNodoNuevoAlPrincipio(lista,nuevoNodo);
        }
        else
        {
            nodoListaProducto * ante = lista;
            nodoListaProducto * sig = lista->siguiente;
            while (sig != NULL && strcmp(sig->dato.nombre, nuevoNodo->dato.nombre)<0)
            {
                ante=sig;
                sig=sig->siguiente;
            }
            ante->siguiente=nuevoNodo;
            nuevoNodo->siguiente=sig;
        }
    }
    return lista;
}

nodoListaProducto * eliminarPrimero (nodoListaProducto * lista)
{
    nodoListaProducto * primerNodo = lista;
    if (lista != NULL)
    {

        lista=lista->siguiente;
        free(primerNodo);
    }

    return lista;
}

nodoListaProducto * eliminarUltimo (nodoListaProducto * lista)
{
    nodoListaProducto * ante;
    nodoListaProducto * copiaLista= lista;

    while (copiaLista->siguiente!= NULL)
    {
        ante = copiaLista;
        copiaLista=copiaLista->siguiente;
    }

    ante->siguiente = copiaLista->siguiente;

    free(copiaLista);

    return lista;
}

nodoListaProducto * borrarNodoAEleccionPorNombre(nodoListaProducto * lista, char nombre[20])
{
    nodoListaProducto * seg;
    nodoListaProducto * ante;
    if((lista != NULL) && (strcmp(nombre, lista->dato.nombre)==0 ))
    {
        nodoListaProducto * aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    else
    {
        seg = lista;

        while((seg != NULL) && (strcmp(nombre, seg->dato.nombre)!=0 ))
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg!=NULL)
        {
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

nodoListaProducto * borrarNodoAEleccionPorId(nodoListaProducto * lista, int id)
{
    nodoListaProducto * seg;
    nodoListaProducto * ante;
    if((lista != NULL) && lista->dato.idProducto==id)
    {
        nodoListaProducto * aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    else
    {
        seg = lista;

        while((seg != NULL) && lista->dato.idProducto!=id)
        {
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg!=NULL)
        {
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

nodoListaProducto * borrarTodaLaLista(nodoListaProducto * lista)
{
    nodoListaProducto * actual;
    actual = lista;
    while(actual != NULL)
    {
        actual = lista;
        lista = lista->siguiente;
        free(actual);
    }
    return lista;
}


int sumarEdadesLista(nodoListaProducto * lista)
{
    int suma = 0;
    nodoListaProducto * seg = lista;
    while (seg != NULL)
    {
        suma = suma + seg->dato.precio;
        seg = seg->siguiente;
    }
    return suma;
}

nodoListaProducto * desvincularNodo (nodoListaProducto ** lista)
{
    nodoListaProducto * aux;
    if (*lista!=NULL)
    {
        aux =(*lista);
        (*lista)=(*lista)->siguiente;
        aux->siguiente=NULL;
    }
    return aux;
}

nodoListaProducto * intercalarListas(nodoListaProducto* lista_1,nodoListaProducto* lista_2)
{
    nodoListaProducto * lista_Nueva=NULL;
    nodoListaProducto * aux;

    while(lista_1 != NULL && lista_2 != NULL)
    {
        if(lista_1->dato.precio < lista_2->dato.precio)
        {
            aux=lista_1;
            lista_1=lista_1->siguiente;
        }
        else
        {
            aux=lista_2;
            lista_2=lista_2->siguiente;
        }
        aux->siguiente = NULL;
        lista_Nueva=agregarNodoNuevoAlFinal(lista_Nueva,aux);
    }

    if(lista_1 != NULL)
    {
        lista_Nueva = agregarNodoNuevoAlFinal(lista_Nueva, lista_1);
    }
    else if(lista_2 != NULL)
    {
        lista_Nueva = agregarNodoNuevoAlFinal(lista_Nueva, lista_2);
    }

    return lista_Nueva;
}

int buscarNodoPorNombre (nodoListaProducto * lista, char nombre[20])
{
    int flag=0;
    while (lista != NULL && flag==0)
    {
        if (strcmp(nombre, lista->dato.nombre)==0)
        {
            flag=1;
        }
        lista=lista->siguiente;
    }
    return flag;
}


nodoListaProducto* subProgramaAgregarAlFinal(nodoListaProducto * lista, stProducto dato)
{
    nodoListaProducto * nuevo=crearNodo(dato);

    lista=agregarNodoNuevoAlFinal(lista,nuevo);

    return lista;
}

nodoListaProducto * deArchivoALista (nodoListaProducto * lista, char archivo [])
{
    stProducto aux;

    FILE * productoslista=fopen(archivo,"rb");
    if (productoslista)
    {
        while(fread(&aux,sizeof(stProducto),1,productoslista)>0)
        {
            lista=subProgramaAgregarAlFinal(lista,aux);
        }
        fclose(productoslista);
    }
    return lista;
}


nodoListaProducto * invertirLista (nodoListaProducto * lista)
{
    nodoListaProducto * aux;
    nodoListaProducto * listaInvertida= inicLista();
    while (lista)
    {
        aux=desvincularNodo(&lista);
        listaInvertida=agregarNodoNuevoAlPrincipio(listaInvertida,aux);
    }
    return listaInvertida;
}


void mostrarNodoRecursivo (nodoListaProducto * lista)
{
    if(lista != NULL)
    {
        mostrarUnSoloDatoR(lista);//Se puede escribir el printf pero asi es mas rapido.
        mostrarNodoRecursivo(lista->siguiente);
    }
}

void mostrarNodoRecursivoInvertida (nodoListaProducto * lista)
{
    if(lista != NULL)
    {
        mostrarNodoRecursivoInvertida(lista->siguiente);
        mostrarUnSoloDatoR(lista);
    }
}

int sumarListaRecursiva(nodoListaProducto * lista)
{
    int rta=0;

    if(lista == NULL)
    {
        rta=0;
    }
    else
    {
        rta= (lista->dato.precio) + (sumarListaRecursiva(lista->siguiente));
    }
    return rta;
}

void mostrarNodoParRecursivo (nodoListaProducto * lista)
{
    if(lista != NULL)
    {
        lista= lista->siguiente;

        if(lista)
        {
            mostrarUnSoloDatoR(lista);
            mostrarNodoParRecursivo(lista->siguiente);
        }
    }
}

nodoListaProducto * borrarNodoRecursivoAEleccion (nodoListaProducto * lista, char flaco [])
{
    if(lista != NULL)
    {
        if (strcmp(flaco, lista->dato.nombre)==0)
        {
            nodoListaProducto * aux = lista;
            lista = lista->siguiente;
            free(aux);
        }
        else
        {
            lista->siguiente = borrarNodoRecursivoAEleccion(lista->siguiente, flaco);
        }
    }
    return lista;
}


nodoListaProducto * BorrarTodaLaListaRecursivo (nodoListaProducto * lista)
{

    if(lista != NULL)
    {
        lista=BorrarTodaLaListaRecursivo(lista->siguiente);

        eliminarPrimero(lista);
    }

    return lista;
}

nodoListaProducto * invertirListaRecursiva (nodoListaProducto * lista)
{
    nodoListaProducto * aux;

    if (lista !=NULL)
    {
        aux=desvincularNodo(&lista);
        lista=invertirListaRecursiva(lista);
        lista=agregarNodoNuevoAlFinal(lista,aux);
        ///lista=agregarNodoNuevoAlFinal(invertirListaRecursiva(lista),aux);
        ///lista=agregarNodoNuevoAlFinal(invertirListaRecursiva(lista),desvincularNodo(&lista);
    }
    return lista;
}

///-----------------------------------------------------------practica primer parcial----------------------------------------

//nodoAuto * crearNodoAuto (automovil dato)
//{
//    nodoAuto * aux = (nodoAuto*) malloc(sizeof (nodoAuto));
//    aux -> dato = dato;
//    aux -> siguiente = NULL;
//    return aux;
//}
//
//automovil cargarUnAuto ()
//{
//    automovil a;
//
//    printf("\nIngrese la patente del auto(solo 6 numeros y letras): ");
//    fflush(stdin);
//    gets(a.patente);
//    printf("\nIngrese el valor del auto: ");
//    scanf("%d", &a.valor);
//    printf("\nIngrese la marca del auto: ");
//    fflush(stdin);
//    gets(a.marca);
//
//    return a;
//}
//
//nodoAuto * cargarElNodoDeAutos (nodoAuto * lista)
//{
//    nodoAuto * nuevoNodo;
//    char control ='s';
//
//    while (control=='s')
//    {
//        nuevoNodo = crearNodoAuto(cargarUnAuto());
//        agregarNodoNuevoAlFinalPunteroDoble(&lista,nuevoNodo);
//
//
//        printf("\nDesea agragar otro auto? (S/N): ");
//        fflush(stdin);
//        scanf("%c", &control);
//        system("cls");
//    }
//    return lista;
//}
//
//void agregarNodoNuevoAlFinalPunteroDoble (nodoAuto ** lista, nodoAuto * nuevoNodo)
//{
//    nodoAuto * ultimo = NULL;
//    if(*lista == NULL)
//    {
//        *lista = nuevoNodo;
//    }
//    else
//    {
//        ultimo = buscarUltimoAuto(*lista);
//        ultimo->siguiente=nuevoNodo;
//    }
//}
//
//void mostrarListaAutos (nodoAuto*lista)
//{
//    nodoAuto * aux = lista;
//
//    while (aux != NULL)
//    {
//        mostrarUnAuto(aux->dato);
//        aux=aux->siguiente;
//    }
//}
//
//void mostrarUnAuto(automovil a)
//{
//    puts("\n---------------");
//    printf("\n PATENTE:%s",a.patente);
//    printf("\n MARCA:%s",a.marca);
//    printf("\n VALOR:%d", a.valor);
//    puts("\n---------------");
//}
//
//nodoAuto * buscarUltimoAuto (nodoAuto * lista)
//{
//    nodoAuto * ultimo = lista;
//    if (ultimo!= NULL)
//    {
//        while (ultimo -> siguiente != NULL)
//        {
//            ultimo=ultimo->siguiente;
//        }
//    }
//    return ultimo;
//}
///----------------------------------------------------------------------------------------------------------------------
//
//void deListaToArchiFiltro(nodoListaProducto * lista, char personaABuscar [])
//{
//    FILE *archi = fopen(RUTA4,"wb");
//    stProducto p;
//    //char primerLetra;
//
//    if(archi!=NULL)
//        {
//        while(lista->siguiente != NULL)
//            {
//            //primerLetra = lista->dato.nombre;
//            if(strcmp(personaABuscar,lista->dato.nombre)==0)
//            {
//                p = lista->dato;
//                fwrite(&p, sizeof(stProducto), 1, archi);
//            }
//            lista=lista->siguiente;
//        }
//        fclose(archi);
//    }
//    else
//    {
//        printf("EH? cualquiera");
//    }
//}

int contandoPersonasRecursivoConFiltro (nodoListaProducto * lista, int precio)
{
    int contador = 0;

    if(lista->siguiente != NULL && lista->dato.precio > precio)
    {
        contador = 1 + contandoPersonasRecursivoConFiltro(lista->siguiente, precio);
    }
    else if (lista->siguiente != NULL)
    {
        contador = contandoPersonasRecursivoConFiltro(lista->siguiente, precio);
    }

    return contador;
}

void insertarAlFinalRecursivoPunteroDoble(nodoListaProducto ** lista,nodoListaProducto * nuevoNodo)
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

//void insertarEnOrdenRecursivaPunteroDoble(nodoListaProducto ** lista, nodoListaProducto * nuevoNodo)
//{
//    if(*lista == NULL)
//    {
//        *lista = nuevoNodo;
//    }
//    else
//    {
//        if((*lista)->dato.precio > nuevoNodo->dato.precio)
//        {
//            nuevoNodo -> siguiente = *lista;
//            *lista = nuevoNodo;
//        }
//        else
//        {
//            insertarEnOrdenRecursivaPunteroDoble(&(*lista)->siguiente, nuevoNodo);
//        }
//    }
//}



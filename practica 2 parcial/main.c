#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char dni[9];
    char nombre[30];
    float pesoEquipaje;
    int edad;
    int idAvion;
    int idPasaje;
} registroPasajero;

typedef struct
{
    char nombre[30];
    char dni[9];
    int edad;
} Persona;

typedef struct nodoPasajero
{
    Persona p;
    int idPasaje;
    float pesoEquipaje;
    struct nodoPasajero* sig;
} nodoPasajero;

typedef struct nodoAvion
{
    int idAvion;
    nodoPasajero* pasajeros;
    struct nodoAvion* sig;
} nodoAvion;
nodoAvion * inicListaAvion();
nodoAvion * deArchivoALista (nodoAvion * lista, char archivo []);
nodoAvion * agregarNodoNuevoAlFinalAvion (nodoAvion * lista, nodoAvion * nuevoNodo);
nodoAvion * crearNodoAvion(int idAvion);
nodoAvion * buscarUltimoAvion(nodoAvion * plane);
nodoAvion * agregarPpioAvion (nodoAvion * lista, nodoAvion * nuevoNodo);

nodoPasajero * inicListaPasajero();
nodoPasajero * crearNodoPasajero(Persona p, int idPasaje, float pesoEquipaje);
nodoPasajero * agregarNodoNuevoAlFinalPasajero (nodoPasajero * lista, nodoPasajero * nuevoNodo);
nodoPasajero * buscarUltimoPasajero(nodoPasajero * people);
nodoPasajero * agregarPpioPasajero(nodoPasajero * lista, nodoPasajero * nuevoNodo);
void mostrarPersona(Persona dato);


nodoAvion * alta (nodoAvion * plane, nodoPasajero * people, int idAvion);
nodoAvion * buscarAvion(nodoAvion * lista, int idAvion);
void recorrerYmostrarPasajerosConTodo(nodoAvion * lista);
void mostrarNodo(nodoAvion * aux);
void recorrerYmostrarClientes(nodoPasajero * lista);

int avionConMaxPasajeros (nodoAvion* plane);
int avionConMaxHola (nodoPasajero* lista);

float pesoTotalEquipaje (nodoAvion * plane, int idAvion);
float pesoTotalEquipajeHola (nodoPasajero * people);

nodoAvion * eliminarMayores50Anios (nodoAvion * plane, int idAvion);
nodoPasajero * borrarNodoPasajero(nodoPasajero * people, char nombre [20]);
nodoPasajero * subProgramaBorrarNodoPasajero (nodoPasajero * people);

void pasarTodoAdistintosArchivos (nodoAvion * plane);
void pasarArchiHola (nodoPasajero * people, registroPasajero aux, char nombreArchi[]);


nodoAvion * altaAvion(nodoAvion * listaAvion,Persona chabon, int idPasaje,float PesoEquipaje, int idAvion);
nodoPasajero * agregarEnOrden (nodoPasajero * listaPasajeros, nodoPasajero * nuevoPasajero);

int main()
{
    char archiPasajeros [] = "pasajerosAviones.bin";

    nodoAvion * plane = inicListaAvion();

    plane = deArchivoALista(plane, archiPasajeros);
    //recorrerYmostrarPasajerosConTodo(plane);
    // system("pause");
    int rta=avionConMaxPasajeros(plane);
    printf("rta= %d\n", rta);
    float peso=pesoTotalEquipaje(plane, 4);
    printf("peso= %0.2f\n", peso);
    plane=eliminarMayores50Anios(plane, 2);
    recorrerYmostrarPasajerosConTodo(plane);
    pasarTodoAdistintosArchivos(plane);
    return 0;
}

void pasarTodoAdistintosArchivos (nodoAvion * plane)
{
    registroPasajero aux;

    char arEspecie[20];

    arEspecie[0]='\0';
    // char nombreArchi[10];
    while (plane)
    {
//        scanf("&s", nombreArchi);
//         fflush(stdin);
//        strcat (arEspecie,nombreArchi);
        strcat (arEspecie,"pi");
        strcat (arEspecie,".bin");
        aux.idAvion=plane->idAvion;
        pasarArchiHola(plane->pasajeros, aux, arEspecie);
        plane=plane->sig;
       // strcpy(arEspecie, "elppepe");
    }
}


void pasarArchiHola (nodoPasajero * people, registroPasajero aux, char nombreArchi[])
{
    FILE * archi1=fopen(nombreArchi, "wb");
    if(archi1)
    {
        while (people)
        {
            strcpy(aux.dni, people->p.dni);
            printf("%s\n",aux.dni);
            strcpy(aux.nombre, people->p.nombre);
            aux.edad=people->p.edad;
            aux.idPasaje=people->idPasaje;
            aux.pesoEquipaje=people->pesoEquipaje;
            fwrite(&aux, sizeof(registroPasajero), 1, archi1);
            people=people->sig;
        }
        fclose(archi1);
    }
}

void recorrerYmostrarPasajerosConTodo(nodoAvion * lista)
{
    nodoAvion * seg = lista;
    while (seg != NULL)
    {
        printf("\n-----------------------\n");
        mostrarNodo(seg);
        recorrerYmostrarClientes(seg->pasajeros);
        printf("\n-----------------------\n");
        seg= seg->sig;
        // seg->pasajeros=seg->pasajeros->sig;
    }
}

void mostrarNodo(nodoAvion * aux)
{
    //printf("\n-----------------------\n");
    printf("\n\tID Avion: %d \n", aux->idAvion);
    // printf("-----------------------\n");
}

void mostrarNodoPersona(nodoPasajero * aux)
{
    printf("\n-----------------------\n");
    printf("ID Pasaje: %d \n", aux->idPasaje);
    mostrarPersona(aux->p);
    printf("Peso Equipaje: %.2f \n", aux->pesoEquipaje);
    printf("-----------------------\n");
}

void mostrarPersona(Persona dato)
{
    printf("Nombre: %s \n", dato.nombre);
    printf("DNI: %s \n", dato.dni);
    printf("Edad: %d \n", dato.edad);
}


void recorrerYmostrarClientes(nodoPasajero * lista)
{
    nodoPasajero * seg = lista;
    while (seg != NULL)
    {
        mostrarNodoPersona(seg);
        seg= seg->sig;
    }
}

nodoAvion * deArchivoALista (nodoAvion * plane, char archivo [])
{
    registroPasajero aux;
    Persona people;
    // int i=0;
    //nodoAvion * plane= inicListaAvion();
    FILE * archi = fopen(archivo,"rb");
    if (archi)
    {
        while(fread(&aux,sizeof(registroPasajero),1,archi)>0)
        {
            // printf("id Avion: %d ", aux.idAvion);
            // printf("nombre: %s\n", aux.nombre);
            strcpy(people.dni,aux.dni);
            strcpy(people.nombre,aux.nombre);
            people.edad=aux.edad;
            plane=altaAvion(plane, people, aux.idPasaje, aux.pesoEquipaje, aux.idAvion);
//            plane=agregarNodoNuevoAlFinalAvion(plane, crearNodoAvion(aux.idAvion));
//
//            plane->pasajeros=agregarNodoNuevoAlFinalPasajero(plane->pasajeros, crearNodoPasajero(people, aux.idPasaje, aux.pesoEquipaje));
            //  i++;
        }
        fclose(archi);
    }
    return plane;
}

nodoAvion * inicListaAvion()
{
    return NULL;
}

nodoAvion * agregarNodoNuevoAlFinalAvion (nodoAvion * lista, nodoAvion * nuevoNodo)
{
    nodoAvion * ultimo = NULL;
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo= buscarUltimoAvion(lista);
        ultimo->sig=nuevoNodo;
    }
    return lista;
}



nodoAvion * crearNodoAvion(int idAvion)
{
    nodoAvion * aux = (nodoAvion*)malloc(sizeof(nodoAvion));
    aux->idAvion= idAvion;

    aux->pasajeros=inicListaPasajero();
    aux->sig = NULL;

    return aux;
}

nodoAvion * buscarUltimoAvion(nodoAvion * plane)
{
    nodoAvion * seg = plane;
    if(seg)
        while(seg->sig != NULL)
        {
            seg = seg->sig;
        }
    return seg;
}

nodoPasajero * inicListaPasajero()
{
    return NULL;
}

nodoPasajero * crearNodoPasajero(Persona p, int idPasaje, float pesoEquipaje)
{
    nodoPasajero * aux = (nodoPasajero*)malloc(sizeof(nodoPasajero));
    aux->p=p;
    aux->idPasaje= idPasaje;
    aux->pesoEquipaje=pesoEquipaje;

    // aux->pasajeros=inicListaPasajero();
    aux->sig = NULL;

    return aux;
}



nodoPasajero * agregarNodoNuevoAlFinalPasajero (nodoPasajero * lista, nodoPasajero * nuevoNodo)
{
    nodoPasajero * ultimo = NULL;
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo= buscarUltimoPasajero(lista);
        ultimo->sig=nuevoNodo;
    }
    return lista;
}


nodoPasajero * buscarUltimoPasajero(nodoPasajero * people)
{
    nodoPasajero * seg = people;
    if(seg)
        while(seg->sig != NULL)
        {
            seg = seg->sig;
        }
    return seg;
}


//
//nodoAvion * alta (nodoAvion * plane, nodoPasajero * people, int idAvion)
//{
//    nodoAvion * avionEncontrado = buscarAvion(plane, idAvion);
//
//    if(avionEncontrado==NULL)
//    {
//        plane = agregarPpioAvion(plane, crearNodoAvion(idAvion));
//        //plane = agregarNodoNuevoAlFinalAvion(plane, crearNodoAvion(idAvion));
//        plane->pasajeros = agregarNodoNuevoAlFinalPasajero(plane->pasajeros, people);
//        //plane->pasajeros = agregarPpioAvion(plane->pasajeros, people);
//    }
//    else
//    {
//      //  printf("ID pasaje: %d\n", people->idPasaje);
//      avionEncontrado->pasajeros = agregarNodoNuevoAlFinalPasajero(avionEncontrado->pasajeros, people);
//        //avionEncontrado->pasajeros = agregarPpioAvion(avionEncontrado->pasajeros, people);
//    }
//    return plane;
//}

nodoAvion * altaAvion(nodoAvion * listaAvion,Persona chabon, int idPasaje,float PesoEquipaje, int idAvion)
{
    nodoPasajero * NuevoPasajero=crearNodoPasajero(chabon,idPasaje,PesoEquipaje);
    nodoAvion * avionBuscado=buscarAvion(listaAvion,idAvion);

    if(avionBuscado==NULL)
    {
        avionBuscado=crearNodoAvion(idAvion);
        listaAvion=agregarNodoNuevoAlFinalAvion(listaAvion,avionBuscado);
        avionBuscado=buscarUltimoAvion(listaAvion);
    }

    avionBuscado->pasajeros=agregarEnOrden(avionBuscado->pasajeros,NuevoPasajero);

    return listaAvion;
}

nodoPasajero * agregarEnOrden (nodoPasajero * listaPasajeros, nodoPasajero * nuevoPasajero)
{
    if(listaPasajeros == NULL)
    {
        listaPasajeros = nuevoPasajero;
    }
    else
    {
        if (strcmp(nuevoPasajero->p.dni, listaPasajeros->p.dni)<0)
        {
            listaPasajeros=agregarPpioPasajero(listaPasajeros,nuevoPasajero);
        }
        else
        {
            nodoPasajero * ante = listaPasajeros;
            nodoPasajero * next = listaPasajeros->sig;
            while (next != NULL && strcmp(next->p.dni, nuevoPasajero->p.dni)<0)
            {
                ante=next;
                next=next->sig;
            }
            ante->sig=nuevoPasajero;
            nuevoPasajero->sig=next;
        }
    }
    return listaPasajeros;
}

nodoAvion * buscarAvion(nodoAvion * lista, int idAvion)
{
    nodoAvion * seg = lista;
    nodoAvion *avionEncontrado = NULL;
    int flag = 0;

    while(seg!= NULL && flag == 0)
    {
        if(seg->idAvion == idAvion)
        {
            avionEncontrado = seg;
            flag=1;
        }
        seg = seg->sig;
    }
    return avionEncontrado;
}


int avionConMaxPasajeros (nodoAvion* plane)

{
    int rta=0, i=0, x=0;
    nodoAvion * pas=plane;
    while (pas)
    {
        i= avionConMaxHola(pas->pasajeros);
        if (i>x)
        {
            x=i;
            rta=pas->idAvion;
        }
        pas=pas->sig;
    }
    return rta;
}



int avionConMaxHola (nodoPasajero* lista)

{
    int rta=0;
    nodoPasajero * pas=lista;
    if (pas)
    {
        rta= 1+avionConMaxHola(pas->sig);
    }
    return rta;
}

float pesoTotalEquipaje (nodoAvion * plane, int idAvion)
{
    float pesoTotal=0, flag=0;
    nodoAvion * pas=plane;
    while (pas && flag==0)
    {
        if (pas->idAvion==idAvion)
        {
            flag=1;
            pesoTotal=pesoTotalEquipajeHola(pas->pasajeros);
        }
        pas=pas->sig;
        // printf("hola\n");
    }
    return pesoTotal;
}



float pesoTotalEquipajeHola (nodoPasajero * people)
{
    float rta=0;
    nodoPasajero * pas=people;
    if (pas)
    {
        rta= rta + (pas->pesoEquipaje) + pesoTotalEquipajeHola(pas->sig);
    }
    return rta;
}




nodoAvion * eliminarMayores50Anios (nodoAvion * plane, int idAvion)
{
    nodoAvion * pas=plane;
    int flag=0;
    while (pas && flag==0)
    {
        if (pas->idAvion==idAvion)
        {
            flag=1;
            pas->pasajeros= subProgramaBorrarNodoPasajero(plane->pasajeros);
        }
        pas=pas->sig;
        printf("hola\n");
    }
    return plane;
}

nodoPasajero * subProgramaBorrarNodoPasajero (nodoPasajero * people)
{
    nodoPasajero * pas = people;
    while (pas)
    {
        if (pas->p.edad>50)
        {
            people=borrarNodoPasajero(people, pas->p.nombre);
        }
        pas=pas->sig;
    }
    return people;
}

nodoPasajero * borrarNodoPasajero(nodoPasajero * people, char nombre[20])
{
    nodoPasajero * seg=inicListaPasajero();
    nodoPasajero * ante=inicListaPasajero();

    if((people != NULL) && (strcmp(nombre, people->p.nombre)==0))
    {
        nodoPasajero * aux = people;
        people = people->sig;
        free(aux);
    }
    else
    {
        seg = people;
        while((seg != NULL) && (strcmp(nombre, seg->p.nombre)!=0))
        {
            ante = seg;
            seg = seg->sig;
        }
        if( seg!= NULL)
        {
            ante->sig = seg->sig;
            free(seg);
        }
    }
    return people;
}

nodoPasajero * agregarPpioPasajero(nodoPasajero * people, nodoPasajero * nuevoNodo)
{
    if(people == NULL)
    {
        people = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = people;
        people = nuevoNodo;
    }
    return people;
}

nodoAvion * agregarPpioAvion (nodoAvion * lista, nodoAvion * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}















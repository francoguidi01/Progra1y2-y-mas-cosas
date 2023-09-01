#include "FDFAlumnos.h"


///INICLISTALDL
nodoLDL * inicListaLDL()
{
    return NULL;
}

///CREAR NUEVO NODO LDL
nodoLDL * crearNodoLDL(int idMateria, char materia[])
{
    nodoLDL * nuevoNodo=(nodoLDL *) malloc(sizeof(nodoLDL));
    nuevoNodo->idMateria=idMateria;
    strcpy(nuevoNodo->materia,materia);
    nuevoNodo->listaNotas=inicListaNotas();
    nuevoNodo->siguiente=NULL;

    return nuevoNodo;
}

///ALTA DE DE LISTA DE LISTAS
nodoLDL * altaLDL(nodoLDL * listaMaterias,char materia[],int idMateria,notaAlumno nuevo)
{
    nodo * nuevoNodo=crearNodoNotas(nuevo);
    nodoLDL * aux=buscaPosMateriaLDL(listaMaterias,idMateria);

    if(!aux)
    {
        listaMaterias=subProgramaAgregarMateriaLDL(listaMaterias,materia,idMateria);
        aux=buscarUltimoNodoLDL(listaMaterias);
    }

    aux->listaNotas=agregarFinalNotas(aux->listaNotas,nuevoNodo);

    return listaMaterias;
}

///BUSCAR ULTIMO NODO
nodoLDL * buscarUltimoNodoLDL(nodoLDL * lista)
{
    nodoLDL * rta=NULL;

    if(lista)
    {
        if(!lista->siguiente)
        {
            rta=lista;
        }
        else
        {
            rta=buscarUltimoNodoLDL(lista->siguiente);
        }
    }

    return rta;
}

///BUSCAR POS MATERIA
nodoLDL * buscaPosMateriaLDL(nodoLDL * listaMaterias,int idMateria)
{
    nodoLDL * rta=NULL;

    if(listaMaterias)
    {
        if(idMateria == listaMaterias->idMateria)
        {
            rta=listaMaterias;
        }
        else
        {
            rta=buscaPosMateriaLDL(listaMaterias->siguiente,idMateria);
        }
    }

    return rta;
}

///AGREGAR MATERIA
nodoLDL * subProgramaAgregarMateriaLDL(nodoLDL * listaMaterias,char materia[],int idMateria)
{
    nodoLDL * nuevoNodo=crearNodoLDL(idMateria,materia);
    printf("creo el nodo LDL \n");

    listaMaterias=agregarAlFinalMateriaLDLRecur(listaMaterias,nuevoNodo);

    return listaMaterias;
}



///AGREGAR AL FINAL MATERIA
nodoLDL * agregarAlFinalMateriaLDLRecur(nodoLDL * lista, nodoLDL * nuevoNodo)
{
    if(!lista)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(!lista->siguiente)
        {
            lista->siguiente=nuevoNodo;
        }
        else
        {
            lista->siguiente=agregarAlFinalMateriaLDLRecur(lista->siguiente,nuevoNodo);
        }
    }


    return lista;
}

///PASAR ARCHIVO TO LDL
nodoLDL * pasarArchivoToLDL(nodoLDL* listaMaterias, char archivo[])
{
    FILE * archi=fopen(archivo,"rb");
    registroArchivo aux;
    notaAlumno nuevo;

    if(archi)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
        {

            nuevo.legajo=aux.legajo;
            nuevo.nota=aux.nota;
            strcpy(nuevo.nombreApe,aux.nombreApe);
            listaMaterias=altaLDL(listaMaterias,aux.materia,aux.idMateria,nuevo);
        }
        fclose(archi);
    }

    return listaMaterias;
}

///MOSTRAR LDL
void mostrarLDL(nodoLDL * listaMaterias)
{
    while(listaMaterias)
    {
        printf("=========================== \n");
        printf("*************************** \n");
        printf("Materia:       %s \n",listaMaterias->materia);
        printf("ID de Materia: %d \n",listaMaterias->idMateria);
        mostrarListaIterativamente(listaMaterias->listaNotas);
        listaMaterias=listaMaterias->siguiente;
    }
}

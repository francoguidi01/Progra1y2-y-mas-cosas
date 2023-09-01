#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <time.h>
#include <conio.h>

int cargarUnArreglo(int A[], int dimension);
int sumarUnArreglo(int A[], int validos);
int cargarUnArregloRandom(int A[], int dim);
int buscarMenor(Pila * p);
int pasarUnaPilaAArreglo(Pila *p, int a[], int dim);
void pasarUnArrayAPilas (int A[], int validos, Pila * pe);
void crearPilasRandom ( Pila * p,int cant);
void CargaPila(Pila *p);
void mostrarUnArreglo(int A[], int validos);
void encontrarUnElemento(int A[], int dimension);
void divisoresPilas (Pila  p, Pila *sd);
void ordenarPorSeleccionUnaPila(Pila * origen, Pila * destino);
void pasarPila (Pila *a, Pila *b);
void insertarEnOrden(Pila * p, int valor);
void ordenarPorInsercionUnaPila(Pila * origen, Pila * destino);
float promedioUnArray (int A[], int dimension);
char cargarUnArregloLetras (char letras[], int dim);
char encontrarLaLetraMayor (char A[], int dimension);
void mostrarUnArregloLetras(char A[], int validos);
void encontrarLaLetra (char A[], int dimension);




int main()
{
    srand(time(NULL));
    system(" color e0");
    Pila pene, pitito, pija;
    inicpila(&pene);
    inicpila(&pitito);
    inicpila(&pija);
    int unArregloA[20];
    int unArregloB[20];
    char abc[20];
    char letramasgrande;
    /// int i=0;
    ///int validos=0;
    ///int y=0;
    ///int x=0;

    crearPilasRandom(&pene, 15);
    ordenarPorSeleccionUnaPila(&pene, &pija);
    mostrar(&pija);
    return 0;
}



int cargarUnArreglo(int A[], int dimension)
{
    char control='s';
    int i=0;

    while(control=='s'&&i<dimension)
    {
        printf("Ingrese un elemento entero al arreglo: ");
        scanf("%d", &A[i]);

        printf("\nDesea continuar? s/n\n");
        fflush(stdin);
        scanf("%c", &control);

        i++;
    }

    return i;
}
int cargarUnArregloRandom(int A[], int dim)
{
    srand(time(NULL));
    // int i=0;
    for (int i=0; i<dim; i++)
    {
        A[i]=rand()%100;
    }
    return dim;
}
void crearPilasRandom ( Pila * p,int cant)
{
    int i=0;
    for (i=0; i<cant; i++)
    {
        apilar(p, (rand()%100));
    }
}
void mostrarUnArreglo(int A[], int validos)
{
    int i=0;

    puts("Contenido del arreglo\n");

    for(i=0; i<validos; i++)
    {
        printf("(%d) ", A[i]);
    }
}
int sumarUnArreglo(int A[], int validos)
{
    int cont=0, i=0;
    for (i; i<validos; i++)
    {
        cont+=A[i];
    }
    return cont;
}
void encontrarUnElemento(int A[], int dimension)
{
    int i=0;
    int elemento=0;
    puts("\n que elemento varon?");
    scanf("%d", &elemento);
    while (i<dimension && A[i]!=elemento)
    {
        A[i];
        i++;
    }
    if (A[i]==elemento)
    {
        printf("mira mira, se encuentra \n");
        system("start https://youtu.be/af1tbI5xiqM?t=90");
    }
    else
    {
        printf("mira mira, no se encuentra\n");
    }
}

float promedioUnArray (int A[], int dimension)
{
    float promedio=0;
    int suma=0;

    suma=sumarUnArreglo(A, 5);

    promedio= (float) suma/dimension;
    printf("\nEste es tu promedio papa frita %0.2f\n", promedio);
    return promedio;
}

void divisoresPilas (Pila  p, Pila *sd)
{
    int x=0;
    Pila noDivisor;
    inicpila(&noDivisor);

    printf("por cual numero dividir?\n");
    scanf("%d", &x);

    while(!pilavacia(&p))
    {

        if(tope (&p) % x == 0)
        {
            apilar(sd, desapilar(&p));
        }
        else
        {
            apilar(&noDivisor, desapilar(&p));
        }
    }
}
int pasarUnaPilaAArreglo(Pila *p, int a[], int dim)
{
    int i=0;
    while(!pilavacia(p) && i<dim)
    {
        a[i]= buscarMenor(p);
        i++;
    }
    return i;
}
int divisoresArray(int A[],Pila *p, int dimension)
{
    int i=0;
    int x=0;
    int y=0;
    int B[5];
    printf("\npor cual numero dividir?\n");
    scanf("%d", &x);

    for (i=0; i<dimension; i++)
    {
        if (A[i] % x == 0)
        {
            apilar(&p, A[i]);
            mostrar(&p);
            B[y]=desapilar(&p);
            y++;
        }

    }
    return B;
}
void pasarPila (Pila *a, Pila *b)
{
    while(!pilavacia(a))
    {
        apilar(b, desapilar(a));
    }
}
void insertarEnOrden(Pila * p, int valor)
{
    Pila aux;
    inicpila(&aux);

    while(!pilavacia(p) && tope(p)>valor)
    {

        apilar(&aux, desapilar(p));
    }

    apilar(p, valor);

    pasarPila(&aux, p);
}
void ordenarPorInsercionUnaPila(Pila * origen, Pila * destino)
{
    int aInsertar=0;

    while(!pilavacia(origen))
    {
        aInsertar=desapilar(origen);
        insertarEnOrden(destino, aInsertar);
    }
}
void CargaPila(Pila *p)
{
    int datoingresado=0;
    char control;
    do
    {
        printf("\n Ingrese datos para cargar a la pila:  ");
        scanf("%d", &datoingresado);
        apilar(p, datoingresado);

        printf("\nDesea seguir cargando datos? Cualquier tecla para continuar o ESC para salir\n");
        control=getch();
    }
    while(control!=27);
}
int buscarMenor(Pila * p)
{
    int elMenorParaRetornar;
    Pila menor, aux;
    inicpila(&menor);
    inicpila(&aux);

    apilar(&menor, desapilar(p));

    while(!pilavacia(p))
    {
        if(tope(p)<tope(&menor))
        {
            apilar(&aux, desapilar(&menor));
            apilar(&menor, desapilar(p));
        }
        else
        {
            apilar(&aux, desapilar(p));
        }
    }

    pasarPila(&aux, p);

    elMenorParaRetornar=tope(&menor);

    return elMenorParaRetornar;
}
void pasarUnArrayAPilas(int A[], int validos, Pila *pe)
{
    for (int i=0; i<validos; i++)
    {
        apilar(pe, A[i]);
    }
}

void ordenarPorSeleccionUnaPila(Pila * origen, Pila * destino)
{
    int unValor=0;
    while(!pilavacia(origen))
    {
        unValor=buscarMenor(origen);

        apilar(destino, unValor);
    }
}
char cargarUnArregloLetras (char letras[], int dim)
{
    int i=0;
    char opcion;
    do
    {
        printf("\nCargue la letra que desea meter en el arreglo\n");
        scanf("%c", &letras[i]);
        fflush(stdin);
        printf("Desea continuar? s/n, bro\n");
        scanf("%c", &opcion);
        fflush(stdin);
        i++;
        opcion=getch();
        system("cls");
    }
    while(i<dim && opcion=='n');
    return i;
}
void mostrarUnArregloLetras(char A[], int validos)
{
    int i=0;

    puts("Contenido del arreglo\n");

    for(i=0; i<validos; i++)
    {
        printf("(%c) ", A[i]);
    }
}
void encontrarLaLetra (char A[], int dimension)
{
    int i=0;
    char letra;

    printf("\nQue letra desea buscar amable senior?\n");
    scanf("%c", &letra);

    while (i<dimension && letra!=A[i])
    {
        A[i];
        i++;
    }
    if (letra==A[i])
    {
        printf("se encuentra goddddd");
    }
    else
    {
        printf("NOOO se encuentra");
    }
}
char encontrarLaLetraMayor (char A[], int dimension)
{
    int i=1;
    char letraMayor;
    letraMayor=A[0];
    while (i<dimension)
    {
        if (letraMayor < A[i])
        {
            letraMayor=A[i];
        }
        i++;
    }
    return letraMayor;
}

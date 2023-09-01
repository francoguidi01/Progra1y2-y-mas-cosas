#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <time.h>
#include <conio.h>
void cargarRandomModoOn ( Pila * p);
void cargarRandomModoOff ( Pila * p);
void resultados (Pila p, int arreglo []);
void mostrarUnArreglo(int A[], int validos);
void resultadosDeArregloB (int b[]);
int gananciaTotal (Pila p);
int valorMaxPosicion (int a[], int validos);
int minimoCoin(Pila p);
int separacionDeResultados (Pila *p, int b[], int dim);
float promedioUnArray (int A[], int dimension, int validos);

int main()
{
    char x;
    srand(time(NULL));
    int b[100];
    int validos=0;
    Pila modoON, modoOff;
    inicpila(&modoON);
    inicpila(&modoOff);
    printf("Empezar en modo seguro? 's' para confirmar o cualquier tecla para no iniciarlo\n");
    scanf("%c",&x);
    if(x=='s')
    {
        cargarRandomModoOn(&modoON);
        printf("\nEstos son los resultados de haber invocado en modo seguro\n");
        mostrar(&modoON);
        separacionDeResultados(&modoON, b, 10);
        printf("\nEstos son los resultados de haber separado entre la pila y el arreglo, \nel arreglo no lleva nada por usar el modo seguro \n");
        mostrar(&modoON);
        mostrarUnArreglo(b, 0);
        resultados(modoON, b);
    }
    else
    {
        cargarRandomModoOff(&modoOff);
        printf("\nEstos son los resultados de no haber invocado en modo seguro\n");
        mostrar(&modoOff);
        validos=b[separacionDeResultados(&modoOff, b, 10)];

        printf("\nEstos son los resultados de haber separado entre la pila y el arreglo");
        mostrar(&modoOff);
        mostrarUnArreglo(b, validos);
        resultados(modoOff, b);
    }
    return 0;
}
void resultados (Pila p, int arreglo [])
{
    int menor=0, posicion=0, ganancia=0;
    menor=minimoCoin(p);
    printf("El valor mas chico es:%d", menor);
    posicion=valorMaxPosicion(arreglo, 10);
    printf("\nLa posicion del valor mas grande es:%d", posicion);
    ganancia=gananciaTotal(p);
    printf("La ganancia total es:%d", gananciaTotal);
}
void resultadosDeArregloB (int b[]) ///Un subprograma, que deberá invocar a las funciones anteriores (4.a y 4.b) e informar por pantalla los resultados obtenidos en cada caso.
{
    float prom=0;
    prom=promedioUnArray(b, 10, 10);
    printf("\nEste es el promedio de las coins almacenadas %0.2f\n", prom);

}
float promedioUnArray (int A[], int dimension, int validos) ///Una función que calcule el promedio de coins almacenadas sobre el arreglo.
{
    float promedio=0;
    int suma=0;
    int cont=0, i=0;
    for (i; i<validos; i++)
    {
        cont+=A[i];
    }
    suma=cont;
    promedio= (float) suma/dimension;
    return promedio;
}
int gananciaTotal (Pila p) ///Una función que calcule la ganancia total del día.
{
    Pila pa;
    inicpila(&pa);
    int total=0;
    while (!pilavacia(&p))
    {
        apilar(&pa, desapilar(&p));
        total=tope(&pa) + total;
    }
    return total;
}
int valorMaxPosicion (int a[], int validos) ///3-a-Una función que busque la posición del valor máximo de coin generada en un arreglo.
{
    int max = a[0];
    int maxposi=0;
    int i = 1;
    for(i=1; i<validos; i++)
    {
        if (max<a[i])
        {
            max = a[i];
            maxposi=i;
        }
    }
    return maxposi;
}

int minimoCoin(Pila p) ///Una función que busque el valor mínimo de coin generada en una pila.
{
    int coinMasChica=0;
    Pila menor, aux;
    inicpila(&menor);
    inicpila(&aux);

    apilar(&menor, desapilar(&p));

    while(!pilavacia(&p))
    {
        if(tope(&p)<tope(&menor))
        {
            apilar(&aux, desapilar(&menor));
            apilar(&menor, desapilar(&p));
        }
        else
        {
            apilar(&aux, desapilar(&p));
        }
    }

    while (!pilavacia(&aux), &p)
    {
        apilar(&p, desapilar(&aux));
    }

    coinMasChica=tope(&menor);
    return coinMasChica;
}

void cargarRandomModoOn ( Pila * p) ///Punto 1
{
    int i=0, cant=0;
    printf("¿Cuantas veces invocaste la placa de video en Modo Seguro?");
    scanf("%d", &cant);
    for (i=0; i<cant; i++)
    {
        apilar(p, (rand()%30)+10);
    }
}
void cargarRandomModoOff ( Pila * p) ///Punto 1
{
    int i=0, cant=0;
    printf("¿Cuantas veces invocaste la placa de video en Modo Inseguro?");
    scanf("%d", &cant);
    for (i=0; i<cant; i++)
    {
        apilar(p, (rand()%120)-20);
    }
}

int separacionDeResultados (Pila *p, int b[], int dim) ///punto 2
{
    Pila a, aux;
    inicpila(&a);
    inicpila(&aux);
    int i=0;
    while (!pilavacia(p)&&i<dim)
    {
        if (tope(p)<40)
        {
            apilar(&a, desapilar(p));
        }
        else
        {
            b[i]=tope(p);
            i++;
            apilar(&aux, desapilar(p));
        }
    }
    while (!pilavacia(&a))
    {
        apilar(p, desapilar(&a));
    }
    return i;
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

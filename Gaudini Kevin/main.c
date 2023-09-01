#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include "pila.h"



void muestraArreglos (int A[], int validos);
//El valor generado podrá variar entre 10 a 40 coins o -20 a 100 coins, dependiendo del modo de invocación de la placa (modo seguro: on/off).
int generaCoins(int modo);

/*
A partir de la pila cargada con el inciso anterior, analizar la información y separar en  un arreglo y otra pila, las coins generadas según el siguiente criterio:
En la pila A, se pasarán las coins entre -20 y 40.
En el arreglo B, se pasarán las coins entre 41 y 100.
*/
int separaPilaArreglo(int A[], int validos, Pila *P, Pila * S);

/*
Averiguar el valor máximo, el mínimo de coin generada y la ganancia total del día. Para lo cual deberá realizar:
Una función que busque la posición del valor máximo de coin generada en un arreglo.
Una función que busque el valor mínimo de coin generada en una pila.
Una función que calcule la ganancia total del día.
Un subprograma, que deberá invocar a las funciones anteriores (3.a, 3.b y 3.c) e informar por pantalla los resultados obtenidos en cada caso.
*/


int valorMaximo(int A[], int validos);

int valorMinimoPila(Pila P);

int gananciaTotal(Pila P, int A[], int validos);

void MuestraPilaYGanancia(int A[], int validos, Pila P);

/*

Averiguar el promedio de coins en el arreglo B y el porcentaje de coins negativas almacenadas en la pila A. Para lo cual deberá realizar:
Una función que calcule el promedio de coins almacenadas sobre el arreglo.
Una función que calcule qué porcentaje de coins son negativas del total cargado en la pila.
Un subprograma, que deberá invocar a las funciones anteriores (4.a y 4.b) e informar por pantalla los resultados obtenidos en cada caso.
*/

float promedioArreglo(int A[], int validos);

float coinsNegativas(Pila P);

void muestraPromedios(int A[], int validos, Pila P);



int main()
{
    printf("Hello parcial!\n");
    srand(time(NULL));
    /*

Hacer una función main() que invoque a los módulos anteriores y demuestre el funcionamiento del programa.
Para hacer esto, cree las variables que considere necesarias e invoque las funciones (de forma directa o indirecta) como corresponde en cada caso.
Muestre los resultados cada vez que sea necesario.
Si lo considera, cree un menú de opciones para ejecutar cada función o subprograma.
A fin de identificar cada inciso, comente su código indicando a qué apartado corresponde, por ejemplo: // Apartado 3.b

*/


    Pila dia, menores, aux;
    inicpila(&dia);
    inicpila(&menores);
    inicpila(&aux);

    int i=0, valor=0, modo=0, cantidadgen=0, vcargado=0,  validos=0, ganancia=0;
    int ArregloB[100];
    printf("\nIngrese la cantidad de monedas generadas en el dia: ");
    scanf("%d", &cantidadgen);
    printf("\nIngrese El modo de operacion, siendo 0 el modo normal o 1 el modo avanzado: ");
    scanf("%d", &modo);
    while(i<cantidadgen)
    {
        valor=generaCoins(modo);

        apilar(&dia, valor );
        i++;
    }
    printf("\nEstos son los valores generados en el dia de minado:\n");

    mostrar(&dia);


    /*
    A partir de la pila cargada con el inciso anterior, analizar la información y separar en  un arreglo y otra pila, las coins generadas según el siguiente criterio:
    En la pila A, se pasarán las coins entre -20 y 40.
    En el arreglo B, se pasarán las coins entre 41 y 100.
    */
validos=separaPilaArreglo(ArregloB, validos, &dia, &menores);


    printf("\nAsi quedan los valores una vez separados en la pila y el arreglo:\n");
    mostrar(&menores);

muestraArreglos(ArregloB, validos);


    MuestraPilaYGanancia(ArregloB, validos, menores);

    muestraPromedios(ArregloB, validos, menores);


















    return 0;
}



int separaPilaArreglo(int A[], int validos, Pila *P, Pila * S){
    Pila aux;

    inicpila(&aux);
    int vcargado=0;
    while(!pilavacia(P))
    {

        vcargado=tope(P);
        if(vcargado<40)
        {
            apilar(S, desapilar(P));


        }
        else if(vcargado>40)
        {
            A[validos]=vcargado;
            apilar(&aux,desapilar(P));
            validos++;
        }

    }
    return validos;
}


float coinsNegativas(Pila P)
{

    Pila aux, negativos;
    inicpila(&aux);
    inicpila(&negativos);
    int cantidad=0, suma=0;
    float promedio=0;
    while(!pilavacia(&P))
    {
        if(tope(&P)<0)
        {
            apilar(&negativos, desapilar(&P));
            cantidad++;

        }
        else
        {
            apilar(&aux, desapilar(&P));
        }
    }
    while(!pilavacia(&negativos))
    {
        suma=suma+tope(&negativos);
        apilar(&aux, desapilar(&negativos));

    }
    promedio=(float)suma/cantidad;


    return promedio;
}



float promedioArreglo(int A[], int validos)
{

    int i=0,suma=0, div=0;

    float promedio=0;

    div= validos-1;
    for (i=0; i<validos; i++)
    {

        suma=suma+A[i];

    }
    promedio=(float)suma/div;

    return promedio;
}


void muestraPromedios(int A[], int validos, Pila P)
{

    float  proarreglo=0, propila=0;

    proarreglo=promedioArreglo(A, validos);
    propila=coinsNegativas(P);

    printf("\nEl promedio de valores negativos de la pila es la pila es %.1f\n", propila);

    system("pause");


    printf("\nEl promedio de los valores del arreglo es  %.1f\n",proarreglo);




}


int gananciaTotal(Pila P, int A[], int validos)
{
    Pila aux;
    inicpila(&aux);
    int i=0, ganancia=0;
    while(!pilavacia(&P))
    {

        ganancia=ganancia+tope(&P);
        apilar(&aux, desapilar(&P));
    }
    for(i=0; i<validos; i++)
    {

        ganancia=ganancia+A[i];

    }

    return ganancia;
}


int valorMinimoPila(Pila P)
{
    Pila aux;
    inicpila(&aux);
    int valorminimo=40;
    while(!pilavacia(&P))
    {
        if(valorminimo>tope(&P))
        {
            valorminimo=tope(&P);
        }
        apilar(&aux, desapilar(&P));
    }


    return valorminimo;
}



int valorMaximo(int A[], int validos)
{
    int i=0, maximo=0, posicion=0;

    while(i<validos)
    {
        if(A[i]>maximo)
        {
            maximo=A[i];
            posicion=i;
        }
        i++;
    }

//revisar si funciona devolver mayor por param
    return posicion;

}

int generaCoins(int modo)
{

    int valor=0;

    if(modo==0)
    {
        valor=rand() % (40 +1 - 10)+10;
    }
    else
    {
        valor=rand() % (100 +1 - -20)-10;
    }




    return valor;
}


void MuestraPilaYGanancia(int A[], int validos, Pila P)
{

    int  valorminimo=0, posicion=0, ganancia=0;

    valorminimo=valorMinimoPila(P);

    printf("\nEl valor minimo en la pila es %d\n", valorminimo);

    system("pause");

    posicion=valorMaximo(A, validos);
    printf("\nEl valor maximo del arreglo se encuentra en la posicion %d\n",posicion);


    ganancia=gananciaTotal(P, A, validos);
    printf("\nLa ganancia total del dia es: %d\n",ganancia);
}

void muestraArreglos (int A[], int validos)
{
    int i=0;
    printf("\nContenido del arreglo\n");
    for(i=0; i<validos; i++)
    {

        printf(" %i ",A[i]);
    }

}


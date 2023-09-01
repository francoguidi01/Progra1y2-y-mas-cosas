#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "pila.h"


int SumatopeAnte(Pila * p);
int SumaElementos(Pila *p);
int CuentaElementos(Pila * p );
float DivideElementos(int a, int b);
float CalculaPromedio(Pila * p);
float Transformadecimal(Pila * p);

void CargaPila(Pila *p);
void CargarPilaRand(Pila * p);
void OpcionCarga (Pila * p);

void MuevePila(Pila *p, Pila *s);
void MuevePilaOrd(Pila *p, Pila *s);

int RetornaMenor(Pila *p);
void OrdenaMenor(Pila *p, Pila *s);
void OrdenaMenorSilent(Pila *p,Pila *s);
void InsertaElemento(Pila *p, int elemento);
void OrdenInsercion(Pila * p, Pila * s);

void MenuPrincipal (Pila * p, Pila * s)
{
    int opcioncarga=0, opcionmain=0, menorvalor=0, mayorvalor=0;
    float promedio=0;
    puts("\n---------------------------------\n");
    puts("\n   Bienvenido al Practico de Funciones con pilas\n");

    puts("2. Hacer una función que pase todos los elementos de una pila a otra.\n");
    puts("3. Hacer una función que pase todos los elementos de una pila a otra, pero conservando el orden.\n");
    puts("4. Hacer una función que encuentre el menor elemento de una pila y lo retorna. La misma debe eliminar ese dato de la pila.\n");
    puts("5.Hacer una función que pase los elementos de una pila a otra, de manera que se genere una nueva pila ordenada.Usar la función del ejercicio 4. (Ordenamiento por selección)\n");
    puts("6. Hacer una función que inserta en una pila ordenada un nuevo elemento, conservando el orden de ésta.\n");
    puts("7. Hacer una función que pase los elementos de una pila a otra, de manera que se genere una nueva pila ordenada. Usar la función del ejercicio 6.  (Ordenamiento por inserción)\n");
    puts("8. Hacer una función que sume y retorne los dos primeros elementos de una pila (tope y anterior), sin alterar su contenido.");
    puts("9. Hacer una función que calcule el promedio de los elementos de una pila, para ello hacer también una función que calcule la suma, otra para la cuenta y otra que divida. En total son cuatro funciones, y la función que calcula el promedio invoca a las otras 3.\n");
    puts("10. Hacer una función que reciba una pila con números de un solo dígito (es responsabilidad de quien usa el programa) y que transforme esos dígitos en un número decimal.\n");
    fflush(stdin);
    scanf("%d", &opcionmain);

    switch(opcionmain)
    {

    case 2:
    {
        puts("\nDatos en las Pilas antes de las operaciones:\n");
        puts("Pila de Origen");
        mostrar(p);
        puts("Pila de Destino");
        mostrar(s);
        MuevePila(p, s);
        puts("\nDatos en las Pilas despues de las operaciones:\n");
        puts("Pila de Origen");
        mostrar(p);
        puts("Pila de Destino");
        mostrar(s);

        break;

    }
    case 3:
    {
        puts("\nDatos en las Pilas antes de las operaciones:\n");
        puts("Pila de Origen");
        mostrar(p);
        puts("Pila de Destino");
        mostrar(s);
        MuevePilaOrd(p,s);
        puts("\nDatos en las Pilas despues de las operaciones:\n");
        puts("Pila de Origen");
        mostrar(p);
        puts("Pila de Destino");
        mostrar(s);
        break;
    }
    case 4:
    {
        puts("\nDato en la Pila antes de la operacion:\n");
        puts("Pila de Origen");
        mostrar(p);
        menorvalor=RetornaMenor(p);
        printf("\nEl menor valor del grupo de datos es: %d\n", menorvalor);
        puts("Pila de Origen post operacion sin el dato");
        mostrar(p);

        break;
    }
    case 5:
    {
        puts("\n\nDato en la Pila antes de la operacion:\n");
        puts("Pila de Origen");
        mostrar(p);
        OrdenaMenor(p,s);
        puts("\n\nDato en las Pilas despues de la operacion:  \n");
        puts("\n\nPila de Origen\n\n");
        mostrar(p);
        puts("\n\nPila de Destino\n\n");
        mostrar(s);
        break;
    }
    case 6:
    {

        puts("\n\nIngrese un elemento para insertar dentro de la pila ordenada;  ");
        scanf("%d", &opcioncarga );

        puts("\n\nDato en la Pila antes de la operacion:\n");
        mostrar(p);
        OrdenaMenorSilent(p,s);
        InsertaElemento(s, opcioncarga);
        puts("\n\nDato en la Pila despues de la operacion:\n");
        mostrar(s);
        break;

    }
    case 7:
    {
        puts("\n\nDatos en la Pila antes de la operacion:\n");
        mostrar(p);
        OrdenInsercion(p, s);
        puts("\n\nDatos en la Pila Original despues de la operacion:\n");
        mostrar(p);
        puts("\n\nDatos en la Pila Secundaria despues de la operacion:\n");
        mostrar(s);
        break;

    }
    case 8:
    {
        puts("\n\nDatos en la Pila antes de la operacion:\n");
        mostrar(p);
        opcioncarga=SumatopeAnte(p);
        printf("\nLa suma de los dos ultimos valores es: %d\n", opcioncarga);

        break;

    }
    case 9:
    {
        puts("\n\nDatos en la Pila antes de la operacion:\n");
        mostrar(p);
        promedio=CalculaPromedio(p);
        printf("\nEl promedio de los valores de la pila es: %.2f\n\n", promedio);

        break;

    }
    case 10:
    {
        puts("\n\nDatos en la Pila antes de la operacion:\n");
        mostrar(p);
        promedio=Transformadecimal(p);
        printf("\nEl numero decimal de la Pila es: %.2f\n\n", promedio);
        break;

    }



    default:
    {
        //puts("Error, se pulso otra tecla");
        break;
    }

    }



}






int main()
{
    Pila Principal, Secundaria;
    inicpila(&Principal);
    inicpila(&Secundaria);

    OpcionCarga(&Principal);
    MenuPrincipal (&Principal, &Secundaria);

    return 0;
}



void OpcionCarga (Pila * p)
{
    int opcioncarga=0, opcionmain=0;
    puts("\n---------------------------------\n");
    printf("\nBienvenido al Practico de Funciones con pilas ordenado. Elija su metodo de carga de datos: \n\n");
    printf("Opcion 1: Cargar datos manualmente, 50 datos maximo\nOpcion 2: Cargar datos random\n");
    fflush(stdin);
    scanf("%d", &opcioncarga);
    fflush(stdin);
    switch(opcioncarga)
    {
    case 1:
    {
        CargaPila(p);
        break;
    }
    case 2:
    {
        CargarPilaRand(p);
        break;

    }

    default:
    {
        puts("Error, se pulso otra tecla");
        break;
    }

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

void CargarPilaRand(Pila * p)
{
    int i=0, cantidad=0;

    printf("Ingrese la cantidad de datos a cargar a la pila, maximo 50\n");
    scanf("%d", &cantidad);
    fflush(stdin);
    for (i=0; i< cantidad; i++)
    {
        apilar(p, rand()%50);
    }

}

void MuevePila(Pila *p, Pila *s)
{
    if(!pilavacia(p))
    {

        puts("La pila de Origen contiene datos, ahora seran pasados a la Pila de destino");
        while(!pilavacia(p))
        {
            apilar(s, desapilar(p));
        }
    }
    else
    {
        puts("La Pila A no contiene datos, no se puede realizar la operacion");
    }

}

void MuevePilaOrd(Pila *p, Pila *s)
{
    Pila aux;
    inicpila(&aux);
    if(!pilavacia(p))
    {

        puts("La pila de Origen contiene datos, ahora seran pasados a la Pila de Destino de forma ordenada");
        while(!pilavacia(p))
        {
            apilar(&aux, desapilar(p));
        }
        while(!pilavacia(&aux))
        {
            apilar(s, desapilar(&aux));
        }
    }
    else

    {
        puts("La Pila de Origen no contiene datos, no se puede realizar la operacion");
    }

}

int RetornaMenor(Pila *p)
{
    ///4. Hacer una función que encuentre el menor elemento de una pila y lo retorna. La misma debe eliminar ese dato de la pila.
    /// Version alternativa, solo retorna el valor por pantalla dentro de la funcion y lo elimina de la pila
    Pila menores, mayor;
    int menor=0;
    inicpila(&menores);
    inicpila(&mayor);


    if(!pilavacia(p))
    {

        apilar(&menores,desapilar(p));
        while(!pilavacia(p))
        {
            if(tope(p)>tope(&menores))
            {
                apilar(&mayor,desapilar(p));
            }
            else
            {
                apilar(&mayor, desapilar(&menores));
                apilar(&menores,desapilar(p));
            }

        }
        while(!pilavacia(&mayor))
        {
            apilar(p,desapilar(&mayor));
        }
        menor=tope(&menores);



    }
    else
    {
        puts("La pila no contiene datos");
    }

    return menor;
}


void OrdenaMenor(Pila * p, Pila * s)
{

    int menor1=0;

    if(!pilavacia(p))
    {
        puts("\n\nLa pila contiene estos datos, procediendo a ordenar los valoresn\n");
        mostrar(p);

        while(!pilavacia(p))
        {
            menor1=RetornaMenor(p);

            apilar(s, menor1);

        }


    }
    else
    {
        puts("La pila no contiene datos");
    }

}

void OrdenaMenorSilent(Pila *p,Pila *s)
{


    int menor1=0;

    if(!pilavacia(p))
    {
        while(!pilavacia(p))
        {
            menor1=RetornaMenor(p);

            apilar(s, menor1);

        }


    }


}




void InsertaElemento(Pila *p, int elemento)
{
    Pila aux;
    inicpila(&aux);


    while(!pilavacia(p) && elemento<tope(p))
    {
        apilar(&aux, desapilar(p));

    }
    apilar(p, elemento);
    while(!pilavacia(&aux))
    {
        apilar(p, desapilar(&aux));
    }



}


void OrdenInsercion(Pila * p, Pila * s)
{
    /*7. Hacer una función que pase los elementos de una pila a otra, de manera que se genere una nueva pila ordenada.
     Usar la función del ejercicio 6.  (Ordenamiento por inserción)\n");
    */
    int aInsertar=0;

    while(!pilavacia(p))
    {
        aInsertar=desapilar(p);
        InsertaElemento(s, aInsertar);
    }
}

int SumatopeAnte(Pila * p)
{
//8. Hacer una función que sume y retorne los dos primeros elementos de una pila (tope y anterior), sin alterar su contenido.
    Pila aux;
    inicpila(&aux);

    int resultado=0;
    resultado=resultado+tope(p);
    apilar(&aux,desapilar(p));
    resultado=resultado+tope(p);
    apilar(p, desapilar(&aux));

    return resultado;
}


int SumaElementos(Pila *p)
{
    Pila aux;
    inicpila(&aux);
    int resultado=0;
    while(!pilavacia(p))
    {
        resultado=resultado+tope(p);
        apilar(&aux,desapilar(p));
    }
    while(!pilavacia(&aux))
    {
        apilar(p,desapilar(&aux));
    }
    return resultado;
}
int CuentaElementos(Pila * p )
{
    Pila aux;
    inicpila(&aux);
    int resultado=0;
    while(!pilavacia(p))
    {
        resultado++;
        apilar(&aux,desapilar(p));
    }
    while(!pilavacia(&aux))
    {
        apilar(p,desapilar(&aux));
    }
    return resultado;

}

float DivideElementos(int a, int b)
{
    float resultado=0;

    resultado=(float)a/b;

    return resultado;

}

float CalculaPromedio(Pila * p)
{
    int elementos, cantidad;
    float promedio;
    elementos=SumaElementos(p);
    cantidad=CuentaElementos(p);
    promedio=DivideElementos(elementos, cantidad);

    return promedio;
}



float Transformadecimal(Pila * p)
{
    Pila aux1, aux2;
    inicpila(&aux1);
    inicpila(&aux2);
    float suma=0, resultado=0;

    while(!pilavacia(p))
    {
        if(tope(p)<10)
        {
            apilar(&aux1, desapilar(p));
        }
        else
        {
            apilar(&aux2, desapilar(p));
        }

    }
    while(!pilavacia(&aux1))
    {
        suma=suma+tope(&aux1);
        apilar(&aux2, desapilar(&aux1));
    }

    resultado=suma/37;

    return resultado;
}

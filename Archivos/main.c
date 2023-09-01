#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    int legajo;
    char nombreYapellido[30];
    int edad;
    int anio;
} alumnos;


void agregarAlFinal (char nombre_archivo[], int dato);
void mostrarArchivo (char nombre_archivo[], int dato);
int cocaretornable (char nombre_archivo[]);

int main()
{
    int numero=0, dato, x=0, edad=0, edad2=0, p=0, i=0, validos=0;
    srand(time(NULL));
    alumnos outOfTouch;
    char rutaDelArchivo []= {"archivoDeEnteros.dat"};
    char rutaDelArchivoAlumnos []= {"archivoDeAlumnos.dat"};
    Pila mayor;
    inicpila(&mayor);



    puts("1- Hacer una funcion que agregue un elemento al final de un archivo.\n");
    puts("2- Hacer una funcin que muestre por pantalla el contenido de un archivo.\n");
    puts("3- Hacer una funcion que retorne la cantidad de registros que contiene un archivo.\n");
    puts("4- Crear una funcion que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el archivo ya esta creado previamente. Cargar el archivo con 5 datos. Cerrarlo dentro de la funcion.\n");
    puts("5- Crear una funcion que muestre por pantalla los registros de un archivo de alumnos. Modularizar\n");
    puts("6- Crear una funcion que permita agregar de a un elemento al final del archivo. O sea, se debe abrir el archivo, se piden los datos, se escribe en el archivo y se cierra.\n");
    puts("7- Crear una funcion que pase a una pila los numeros de legajo de los alumnos mayores de edad.\n");
    puts("8- Dado un archivo de alumnos, hacer una funcion que cuente la cantidad de alumnos mayores a edad especifica que se envia por parametro.\n");
    puts("9- Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango de edades especifico. Dicho rango debe recibirse por parametro.\n");
    puts("10- Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad.\n");
    puts("11- Crear una funcion que retorne la cantidad de alumnos que cursan de la edad de 6 años en adelante.\n");
    puts("12- Crear una funcion que reciba como parametro un arreglo de tipo alumno y lo copie en el archivo. Asimismo, realice otra funcion que pase los elementos del archivo a un arreglo de alumnos, filtrando los estudiantes de un anio en particular.\n");
    puts("13- Crear una funcion que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell\n");
    puts("14- Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una funcion que muestre el contenido de un registro, cuyo numero (entre 0 y 9) se pase por parametro. Controlar no sobrepasar los limites del archivo.\n");
    puts("15- Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos. La misma debe permitir modificar uno o todos los campos de la estructura y sobreescribir el registro existente en el archivo.\n");
    puts("16- \n");
    printf("Que ejercicio queres hacer? ");
    scanf("%d", &numero);
    switch (numero)
    {
    case 1:
        system("cls");
        printf("\n--PUNTO 1--\n");
        printf ("que dato? ");
        scanf("%d", &dato);
        agregarAlFinal(rutaDelArchivo, dato);
        break;
    case 2:
        system("cls");
        printf("\n--PUNTO 2--\n");
        printf ("que dato? ");
        scanf("%d", &dato);
        agregarAlFinal(rutaDelArchivo, dato);
        mostrarArchivo(rutaDelArchivo, dato);
        break;
    case 3:
        system("cls");
        printf("\n--PUNTO 3--\n");
        printf ("Que dato?: ");
        scanf("%d", &dato);
        agregarAlFinal(rutaDelArchivo, dato);
        mostrarArchivo(rutaDelArchivo, dato);
        x=cocaretornable(rutaDelArchivo);
        printf("\nEsta es la cantidad: %d", x);
        break;
    case 4:
        system("cls");
        printf("\n--PUNTO 4--\n");
        cargaAlumnos(rutaDelArchivoAlumnos);
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        break;
    case 5:
        system("cls");
        printf("\n--PUNTO 5--\n");
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        break;
    case 6:
        system("cls");
        printf("\n--PUNTO 6--\n");
        cargaUnAlumno(rutaDelArchivoAlumnos);
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        break;
    case 7:
        system("cls");
        printf("\n--PUNTO 7--\n");
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        buscarLegajo(rutaDelArchivoAlumnos, &mayor);
        mostrar(&mayor);
        break;
    case 8:
        system("cls");
        printf("\n--PUNTO 8--\n");
        printf("desde que edad? ");
        scanf("%d", &edad);
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        p=contadorEdad(rutaDelArchivoAlumnos, edad);
        printf("estos son los alumnos mayores a %d: %d", edad, p);
        break;
    case 9:
        system("cls");
        printf("\n--PUNTO 9--\n");
        printf("desde que edad? ");
        scanf("%d", &edad);
        printf("hasta que edad? ");
        scanf("%d", &edad2);
        verNombresRangoEdad(rutaDelArchivoAlumnos, edad,edad2);
        // muestraAlumnoFalopa(rutaDelArchivoAlumnos);
        //mostrarUnEstudiantes(rutaDelArchivoAlumnos);
        break;
    case 10:
        system("cls");
        printf("\n--PUNTO 10--\n");
        buscaAlumnoMayorEdad(rutaDelArchivoAlumnos);
        break;
    case 11:
        system("cls");
        printf("\n--PUNTO 11--\n");
        printf("Que edad varon?: ");
        scanf("%d", &edad);
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        i=contadorPorEdad(rutaDelArchivoAlumnos,edad);
        printf("La cantidad de alumnos que cursan de %d son: %d", edad,i);
        break;
    case 12:
        system("cls");
        printf("\n--PUNTO 12--\n");
        validos=cargaArregloStruct(&outOfTouch, 10);
        pasarArregloAlArchivo(rutaDelArchivoAlumnos, &outOfTouch, validos);
        mostrarStEstudiantes(rutaDelArchivoAlumnos);
        break;
    case 13:
        system("cls");
        printf("\n--PUNTO 13--\n");
        x=cuentaRegistroArchivo(rutaDelArchivoAlumnos);
        printf("\n\n\n\t\t\t\t esta es la cantidad de alumnos registrados: %d\n\n\n\t\t\t\t", x);
        break;
    case 14:
        system("cls");
        printf("\n--PUNTO 14--\n");
        printf("Que registro del 1 al 10 compi?: ");
        scanf("%d", &i);
        mostrarAlumnoArchivo(rutaDelArchivoAlumnos, i);
        break;
    case 15:
        system("cls");
        printf("\n--PUNTO 15--\n");
        muestraAlumnoFalopa(rutaDelArchivoAlumnos);
        printf("Que registro queres modificar compi necesito el legajo tho?: ");
        scanf("%d", &i);
        modificarUnRegistro(rutaDelArchivoAlumnos, i);
        break;
    case 16:
        system("cls");
        printf("\n--PUNTO 16--\n");
        printf("\nNo lo hice lol\n");
        break;
    default:
        printf("No abarca los puntos del tp");
        break;
    }
    return 0;
}

void agregarAlFinal (char nombre_archivo[],int dato)
{
    FILE * archivoDeEnteros;
    archivoDeEnteros=fopen(nombre_archivo, "ab");

    if (archivoDeEnteros!=NULL)
    {
        fwrite(&dato, sizeof(int), 1, archivoDeEnteros);
        fclose(archivoDeEnteros);
    }
}

void mostrarArchivo (char nombre_archivo[], int dato)
{
    FILE * archivoDeEnteros;
    archivoDeEnteros=fopen(nombre_archivo, "rb");

    if (archivoDeEnteros!=NULL)
    {
        while (fread(&dato,sizeof (int), 1, archivoDeEnteros)>0)
        {
            printf(" /%d/ ", dato);
        }
        fclose(archivoDeEnteros);
    }
}

int cocaretornable (char nombre_archivo[])
{
    int i=0, dato=0;
    FILE * archivoDeEnteros;
    archivoDeEnteros=fopen(nombre_archivo, "rb");

    if (archivoDeEnteros!=NULL)
    {
        fseek(archivoDeEnteros,sizeof(int)*0,SEEK_SET);

        while(fread(&dato,sizeof(int),1,archivoDeEnteros)>0)
        {
            i++;
        }
        fclose(archivoDeEnteros);
    }
    return i;
}
int contadorEdad(char nombre_archivo[],int edad)
{
    int i=0;
    alumnos a;
    FILE * archivoDeAlumnos;
    archivoDeAlumnos=fopen(nombre_archivo,"rb");

    if(archivoDeAlumnos!=NULL)
    {

        while(!feof(archivoDeAlumnos))
        {
            fread(&a,sizeof(alumnos), 1, archivoDeAlumnos);

            if(!feof(archivoDeAlumnos))
            {
                if(a.edad>edad)
                {
                    i++;
                }
            }

        }
        fclose(archivoDeAlumnos);
    }
    return i;
}
int cargaAlumnos(char nombre_archivo[])
{
    int i=0;
    char control = 's';
    alumnos a;


    FILE * archivoDeAlumnos;

    archivoDeAlumnos=fopen(nombre_archivo,"ab");

    if(archivoDeAlumnos!=NULL)
    {
        printf("Ingreso de alumnos: \n");
        while(control=='s')
        {
            printf("\n Ingrese legajo: ");
            scanf("%d", &a.legajo);
            printf("\n Ingrese nombre y apellido: ");
            fflush(stdin);
            gets(a.nombreYapellido);
            printf("\n Ingrese edad: ");
            scanf("%d",&a.edad);
            fwrite(&a,sizeof(alumnos),1,archivoDeAlumnos);
            i++;
            printf("\nDesea agregar otro registro?: ");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archivoDeAlumnos);
    }
    return i;
}

int cargaUnAlumno(char nombre_archivo[])
{
    int i=0;
    alumnos a;


    FILE * archivoDeAlumnos;

    archivoDeAlumnos=fopen(nombre_archivo,"ab");

    if(archivoDeAlumnos!=NULL)
    {
        printf("Ingreso de alumnos: \n");
        printf("\n Ingrese legajo: ");
        scanf("%d", &a.legajo);
        printf("\n Ingrese nombre y apellido: ");
        fflush(stdin);
        gets(a.nombreYapellido);
        printf("\n Ingrese edad: ");
        scanf("%d",&a.edad);
        fwrite(&a,sizeof(alumnos),1,archivoDeAlumnos);
        i++;
        fclose(archivoDeAlumnos);
    }
    return i;
}

void mostrarStEstudiantes (char nombre_archivo[])
{
    system("cls");
    alumnos a;
    FILE * archivoDeAlumnos= fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        while(fread(&a,sizeof(alumnos), 1, archivoDeAlumnos)>0)
        {
            puts("Estos son los datos de los estudiantes");
            printf("Matricula:%d\n", a.legajo);
            printf("Nombre:%s\n", a.nombreYapellido);
            printf("Edad:%d\n", a.edad);
        }
    }
    fclose(archivoDeAlumnos);
}

void buscarLegajo (char nombre_archivo [],Pila * m)
{

    FILE * archivoDeAlumnos;
    int i=0;
    alumnos a;
    archivoDeAlumnos=fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        while(!feof(archivoDeAlumnos))
        {
            fread(&a,sizeof(alumnos),1, archivoDeAlumnos);

            if(!feof(archivoDeAlumnos))
            {
                if (a.edad>=18)
                {
                    apilar(m, a.legajo);
                }
            }
        }
        fclose(archivoDeAlumnos);
    }
}

void verNombresRangoEdad (char nombre_archivo[], int edad, int edad2)
{
    FILE * archivoDeAlumnos;
    alumnos a;
    int i=0;
    archivoDeAlumnos=fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        while(!feof(archivoDeAlumnos))
        {
            fread(&a,sizeof(alumnos), 1, archivoDeAlumnos);

            if(!feof(archivoDeAlumnos))
            {
                if ((a.edad>=edad) && (a.edad<=edad2))
                {
                    mostrarAlumno(a);
                    puts("Estos son los datos de los estudiantes");
                }
            }

        }
        fclose(archivoDeAlumnos);
    }
}
void mostrarUnEstudiante (char nombre_archivo[])
{
    FILE * archivoDeAlumnos;
    alumnos a;
    archivoDeAlumnos=fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        fread(&a,sizeof(alumnos),1, archivoDeAlumnos);
        puts("Estos son los datos de los estudiantes");
        printf("Nombre:%s\n", a.nombreYapellido);
    }
    fclose(archivoDeAlumnos);
}

void buscaAlumnoMayorEdad(char nombreArchivo[])
{
    FILE * archivoDeAlumnos;
    alumnos mayor,aux;
    archivoDeAlumnos=fopen(nombreArchivo,"rb");
    if(archivoDeAlumnos!=NULL)
    {
        fread(&mayor,sizeof(alumnos),1,archivoDeAlumnos);
        while(fread(&aux,sizeof(alumnos),1,archivoDeAlumnos)>0)
        {
            if(aux.edad>mayor.edad)
            {
                mayor=aux;
            }
//            printf("El alumno de mayor edad en el archivo es:\n");
//            mostrarAlumno(mayor);
            //fclose(archivoDeAlumnos);
        }
        printf("El alumno de mayor edad en el archivo es:\n");
        mostrarAlumno(mayor);
        fclose(archivoDeAlumnos);
    }
}



void mostrarAlumno(alumnos a)
{
    puts("\n---------------");
    printf("Legajo:%d",a.legajo);
    printf("\nNombreyApellido:%s",a.nombreYapellido);
    printf("\nEdad:%d",a.edad);
    puts("\n---------------\n");
}


void muestraAlumnoFalopa (char nombre_archivo[])
{
    system("cls");
    alumnos a;
    FILE * archivoDeAlumnos= fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        while(fread(&a,sizeof(alumnos), 1, archivoDeAlumnos)>0)
        {
            mostrarAlumno(a);
        }
    }
    fclose(archivoDeAlumnos);
}

int buscaPosicionMenorIntSt(alumnos a[], int v, int pos)
{
    int i=pos;
    int menor = a[i].legajo;
    int posMenor = i;
    i++;
    while(i<v)
    {
        if(a[i].legajo < menor)
        {
            menor = a[i].legajo;
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void ordenaArregloSeleccionSt(alumnos a[], int validos)
{
    int posMenor;
    alumnos aux;
    int i = 0;
    while(i<validos-1)
    {
        posMenor=buscaPosicionMenorIntSt(a, validos, i);
        aux = a[posMenor];
        a[posMenor] = a[i];
        a[i] = aux;
        i++;
    }
}

int contadorPorEdad (char nombre_archivo[], int edad)
{
    FILE * archivoDeAlumnos;
    alumnos a;
    int i=0;
    archivoDeAlumnos=fopen(nombre_archivo, "rb");
    if(archivoDeAlumnos!=NULL)
    {
        while(!feof(archivoDeAlumnos))
        {
            fread(&a,sizeof(alumnos), 1, archivoDeAlumnos);

            if(!feof(archivoDeAlumnos))
            {
                if (a.edad>=edad)
                {
//                    mostrarAlumno(a);
//                    puts("Estos son los datos de los estudiantes");
                    i++;
                }
            }

        }
        fclose(archivoDeAlumnos);
    }
    return i;
}

char **Insertion_sort(char** words, int Max_lines)
{
    int i, j;
    char *temp;

    for( i = 1 ; i < Max_lines; i++)
    {
        strcpy(temp, words[i]);
        j = i-1;
        while ( j >= 0 && strcmp(words[j], temp)>0)
        {
            strcpy(words[j+1], words[j]);
            j=j-1;
        }
        strcpy(words[j+1],temp);
    }
    return words;
}


void pasarArregloAlArchivo (char nombre_archivo[], alumnos outOfTouch[], int validos)
{
    FILE * archivoDeAlumnos;
    archivoDeAlumnos=fopen(nombre_archivo, "ab");
    if(archivoDeAlumnos!=NULL)
    {
        fwrite(outOfTouch,sizeof(alumnos), validos, archivoDeAlumnos);
    }
    fclose(archivoDeAlumnos);
}

int cargaArregloStruct (alumnos A[], int dimension)
{
    int i=0;
    char control = 's';
    while(i<dimension && control=='s')
    {

        printf("\nIngrese legajo: ");
        fflush(stdin);
        scanf("%d", &A[i].legajo);
        printf("\nIngrese nombre apellido: ");
        fflush(stdin);
        gets(A[i].nombreYapellido);
        printf("\nIngrese edad: ");
        fflush(stdin);
        scanf("%d",&A[i].edad);
        i++;
        printf("\nDesea agregar otro registro?: ");
        fflush(stdin);
        scanf("%c", &control);
    }
    return i;
}

int cuentaRegistroArchivo(char nombre_archivo[])
{
    int cantidad=0;
    FILE*archivodealumnos;
    archivodealumnos=fopen(nombre_archivo,"rb");
    if(archivodealumnos!=NULL)
    {
        // me posiciono al final del archiva
        fseek(archivodealumnos,0,SEEK_END);
        // divido la cantidad de bytes del archivodealumnos por la cantidad de
        // bytes de un registro de alumnos

        cantidad= ftell(archivodealumnos)/sizeof(alumnos);
        fclose(archivodealumnos);
    }
    return cantidad;
}

///Dado un archivo de alumnos, que tenga al menos 10 registros,
///hacer una funcion que muestre el contenido de un registro, cuyo numero (entre 0 y 9)
///se pase por parametro. Controlar no sobrepasar los limites del archivo



void mostrarAlumnoArchivo(char nombre_archivo[], int i)
{
    FILE * archivodealumnos;
    alumnos a;
    archivodealumnos=fopen(nombre_archivo,"rb");
    if (i<10)
    {
        if(archivodealumnos!=NULL)
        {
            fseek(archivodealumnos,sizeof(alumnos)*(i-1), SEEK_SET);
            fread(&a, sizeof(alumnos), 1, archivodealumnos);
            fclose(archivodealumnos);
            mostrarAlumno(a);
        }
    }
    else
    {
        printf("flaco ?????");
    }
}

void modificarUnRegistro(char nombreArchivo[],int legajo)
{
    FILE*archi=fopen(nombreArchivo,"r+b");
    alumnos aux;
    char nuevoNombreYApellido [30];
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(alumnos),1,archi)>0)
            {
                if(aux.legajo == legajo)
                {
                    flag=1;
                }
            }
        }
    }
    if(flag ==1)
    {
        /// modificar el registro o darle de baja
        printf("\n\n\n\t\rLo encontreeeee!! \nque nombre queres ponerle brother?? ");

        ///PORQUE NO ME DEJAAAA :(
        //  gets(nuevoNombreYApellido);
        scanf("%s", nuevoNombreYApellido);
        strcpy(aux.nombreYapellido,nuevoNombreYApellido);
        /// me muevo un registro para atras
        fseek(archi, -1*sizeof(alumnos),SEEK_CUR);
        /// sobre escribe el registro
        fwrite(&aux,sizeof(alumnos),1,archi);
        mostrarAlumno(aux);
    }
    fclose(archi);
}

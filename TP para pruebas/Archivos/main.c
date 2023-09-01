#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "pila.h"

//#define equipos "archivoEquipos.dat"

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

    puts("1- \n");
    puts("2- \n");
    puts("3- \n");
    puts("4- \n");
    puts("5- \n");
    printf("Que ejercicio queres hacer? ");
    scanf("%d", &numero);
    switch (numero)
    {
    case 1:
        system("cls");
        printf("\n--PUNTO 1--\n");

        break;
    case 2:
        system("cls");
        printf("\n--PUNTO 2--\n");

        break;

        return 0;
    }
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
    char nuevoNombreYApellido[30];
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
        fflush(stdin);
        gets(nuevoNombreYApellido);
        ///scanf("%s", nuevoNombreYApellido);
        strcpy(aux.nombreYapellido,nuevoNombreYApellido);
        /// me muevo un registro para atras
        fseek(archi, -1*sizeof(alumnos),SEEK_CUR);
        /// sobre escribe el registro
        fwrite(&aux,sizeof(alumnos),1,archi);
        mostrarAlumno(aux);
    }
    fclose(archi);
}

int validardatos(int legajo, char nombre[])
{
    FILE * archivin=NULL;

    alumnos aux;
    int flag=0;

    archivin=fopen(nombre,"rb");

    if(archivin!=NULL)
    {
        while(flag==0 && !feof(archivin))
        {
            fread(&aux,sizeof(alumnos),1,archivin);
            if(!feof(archivin))
            {
                if(aux.legajo == legajo)
                {
                    flag=1;
                }
            }
        }
        fclose(archivin);
    }
    else
    {
        printf("ERROR DE DATOS - El archivo no pudo ser abierto \n");
    }

    return flag;

}

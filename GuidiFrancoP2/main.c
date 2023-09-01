#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>


typedef struct
{
    int idMonotrib;
    long int cuit;
// valores entre 2.000.000 y 10.000.000
    char nombreYapellido [30];
} stMonotributista;

typedef struct
{
    int nroFactura;
    int idMonotrib;
    char tipoFactura; // A o B en mayúscula
    float montoTotal; // no más de $ 500.000
    // no puede haber montos negativos
} stFactura;
int cargaArregloMonotributista (stMonotributista a[], int dimension, char mono[]);
int cuentaRegistroArchivo(char nombre_archivo[]);
int cargaArregloFacturas (stFactura x[], int dimension, char mono[]);
int validardatos(int id, char nombre[]);
void pasarArregloAlArchivoMonotributista (char nombre_archivo[], stMonotributista a[], int validos);
void pasarArregloAlArchivoFacturas (char facturaA[],char facturaB[], stFactura a[], int validos);
void mostrarMonotributista(stMonotributista a);
void muestraMonotributista (char nombre_archivo[]);
void mostrarFactura(stFactura a);
void muestraFacturaA (char nombre_archivo[]);
void muestraAFacturaB(char nombre_archivo[]);
int busqueda (char mono[], char facturaA[], char facturaB[], long int cuit);


int main()
{
    int validosMono=0, validosFactura=0;
    long int cuit=0;
    stMonotributista mono[100];
    stFactura factura [100];
    char archivoMono []= {"monotributistas.dat"};
    char rutaDeFacturasA []= {"archivoDeFacturasA.dat"};
    char rutaDeFacturasB []= {"archivoDeFacturasB.dat"};

///PUNTO 1
    validosMono=cargaArregloMonotributista(mono, 100, archivoMono);
///PUNTO 2
    validosFactura=cargaArregloFacturas(factura, 100, archivoMono);
///PUNTO 3
    pasarArregloAlArchivoMonotributista(archivoMono, mono, validosMono);
    pasarArregloAlArchivoFacturas(rutaDeFacturasA, rutaDeFacturasB, factura, validosFactura);
///PUNTO 4
    muestraMonotributista(archivoMono);
    muestraFacturaA(rutaDeFacturasA);
    muestraAFacturaB(rutaDeFacturasB);
///PUNTO 5
    printf("\n Ingrese un cuit que este en el sistema por favor: ");
    scanf("%ld", cuit);
    busqueda(archivoMono, rutaDeFacturasA, rutaDeFacturasB, cuit);

    return 0;
}
///Hacer una función de carga de un arreglo de Monotributistas. La misma debe validar que el cuit sea un valor entre 2.000.000 y 10.000.000 (impedir la carga fuera de ese rango).
///El usuario puede cargar tantos registros como desee y la función debe retornar la cantidad de monotributistas cargados. Si lo necesita, puede modularizar lo que considere.
int cargaArregloMonotributista (stMonotributista a[], int dimension, char mono[])
{
    FILE * monotributista=NULL;
    monotributista=fopen(mono, "rb");
    int i=0, flag=0;
    long int  cuit=0;
    char control = 's';
    a[i].idMonotrib=cuentaRegistroArchivo(mono)+(i+1);
    while(i<dimension && control=='s')
    {
        do
        {
            printf("\nIngrese cuit: ");
            scanf("%ld", &cuit);

            if (2000000 < cuit && cuit<10000000)
            {
                flag=1;
            }
            else
            {
                printf("cuit invalido, ingrese nuevamente");
            }
        }
        while (flag==0);
        a[i].cuit=cuit;
        printf("\nIngrese nombre apellido: ");
        fflush(stdin);
        gets(a[i].nombreYapellido);
        i++;
        printf("\nDesea agregar otro monotribustista?: ");
        fflush(stdin);
        scanf("%c", &control);
    }
    fclose(monotributista);
    return i;
}
int cuentaRegistroArchivo(char nombre_archivo[])
{
    int cantidad=0;
    FILE*archivoMono;
    archivoMono=fopen(nombre_archivo,"rb");
    if(archivoMono!=NULL)
    {

        fseek(archivoMono,0,SEEK_END);
        cantidad= ftell(archivoMono)/sizeof(stMonotributista);
        fclose(archivoMono);
    }
    return cantidad;
}


///Hacer una función que cargue un arreglo de Facturas, donde el usuario puede cargar tantas Facturas como desee y la función debe retornar la cantidad de facturas cargadas. La misma debe validar:
///Que los tipos de factura sean A o B.
///Validar que el monto no sea negativo, ni supere los $500.000.
///Que el idMonotrib exista en el arreglo de monotributistas previamente cargado con el inciso 1. Para lo cual,
///debe realizar una función de búsqueda para verificar si el monotributista ya existe. Si no existe el monotributista,
///lo debemos cargar (el arreglo correspondiente) antes de continuar con la carga de la factura.
///Tenga en cuenta que esta función, además de recibir los datos que necesita para trabajar,
/// deberá recibir el arreglo de monotributistas y sus validos con el fin de modificarlos (agregar un nuevo monotributista) de ser necesario.
///Puede modularizar lo que considere. Preste atención al tipo de pasaje de parámetros a aplicar.


int cargaArregloFacturas (stFactura x[], int dimension, char mono[])
{
    FILE * archivoMono= NULL;
    archivoMono=fopen(mono, "rb");
    int i=0, id=0, flag=0;
    float monto=0;
    char control = 's', factura, a, b;
    while(i<dimension && control=='s')
    {

        do
        {
            printf("\nIngrese id de Monotributo: ");
            scanf("%d", &id);
            flag=validardatos(id, mono);
            if (flag==0)
            {
                printf("id no encontrado");
            }
        }
        while(flag==0);
        x[i].idMonotrib=id;
        printf("\nIngrese nro factura: ");
        scanf("%d", &x[i].nroFactura);
        do
        {
            printf("\nTipo de Factura A o B: ");
            fflush(stdin);
            scanf("%c", &factura);
            if (factura!= a|| factura!=b)
            {
                printf("factura no reconosible");
            }

        }
        while (factura==a || factura==b);
        strcpy(x[i].tipoFactura, factura);
        printf("\nIngrese monto total: ");
        fflush(stdin);
        do
        {
            scanf("%f",&monto);
        }
        while (0<monto && monto<500000);
        x[i].montoTotal=monto;
        i++;
        printf("\nDesea agregar otro registro?: ");
        fflush(stdin);
        scanf("%c", &control);
    }
    fclose(archivoMono);
    return i;
}
int validardatos(int id, char nombre[])
{
    FILE * archivoMono=NULL;

    stMonotributista aux;
    int flag=0;

    archivoMono=fopen(nombre,"rb");

    if(archivoMono!=NULL)
    {
        while(flag==0 && !feof(archivoMono))
        {
            fread(&aux,sizeof(stMonotributista),1,archivoMono);
            if(!feof(archivoMono))
            {
                if(aux.idMonotrib == id)
                {
                    flag=1;
                }
            }
        }
        fclose(archivoMono);
    }
    return flag;
}

///Debemos persistir la información almacenada en cada arreglo (Monotributistas y Facturas), cada uno en un archivo diferente,
///para lo cual realizará 2 funciones diferentes para simplificar el problema:
///La primera: Una función que escriba los datos del arreglo de Monotributistas a un archivo de llamado “monotributistas.dat”, los cuales fueron cargados en el inciso 1.
///La segunda: Una función que escriba los datos del arreglo de facturas, los cuales fueron cargados en el inciso 2, a dos archivos diferentes:
///uno con las facturas de tipo A
///y otro con las facturas de tipo B.
///Dentro de la función trabaje con 2 variables de tipo FILE*, una para cada archivo.

void pasarArregloAlArchivoMonotributista (char nombre_archivo[], stMonotributista a[], int validos)
{
    FILE * archivoMono=NULL;
    archivoMono=fopen(nombre_archivo, "wb");
    if(archivoMono!=NULL)
    {
        fwrite(a,sizeof(stMonotributista), validos, archivoMono);
    }
    fclose(archivoMono);
}

void pasarArregloAlArchivoFacturas (char facturaA[],char facturaB[], stFactura a[], int validos)
{
    FILE * archivoFacturaA=NULL;
    FILE * archivoFacturaB=NULL;
    int i=0;
    archivoFacturaA=fopen(facturaA, "wb");
    archivoFacturaB=fopen(facturaB, "wb");
    if(archivoFacturaA!=NULL && archivoFacturaB!=NULL)
    {
        for(i=0; i<validos; i++)
        {
            if(a[i].tipoFactura=='a')
            {
                fwrite(a,sizeof(stFactura), validos, archivoFacturaA);

            }
            else
            {
                fwrite(a,sizeof(stFactura), validos, archivoFacturaB);
            }
        }
        fclose(archivoFacturaA);
        fclose(archivoFacturaB);
    }
}


///Debemos generar un listado por cada archivo (mostrar por pantalla).
///Uno por las Factura A, Factura B y Monotributistas. Es de carácter obligatorio modularizar.


void mostrarMonotributista(stMonotributista a)
{
    puts("\n---------------");
    printf("ID del monotributista:%d",a.idMonotrib);
    printf("\nNombre y Apellido:%s",a.nombreYapellido);
    printf("\CUIT:%ld",a.cuit);
    puts("\n---------------\n");
}
void muestraMonotributista (char nombre_archivo[])
{
    system("cls");
    stMonotributista a;
    FILE * archivoMono= fopen(nombre_archivo, "rb");
    if(archivoMono!=NULL)
    {
        while(fread(&a,sizeof(stMonotributista), 1, archivoMono)>0)
        {
            mostrarMonotributista(a);
        }
    }
    fclose(archivoMono);
}
void mostrarFactura(stFactura a)
{
    puts("\n---------------");
    printf("Nro de Factura:%d",a.nroFactura);
    printf("\n Id:%d",a.idMonotrib);
    printf("\Tipo de factura:%c",a.tipoFactura);
    printf("\Monto Total:%f",a.montoTotal);
    puts("\n---------------\n");
}


void muestraFacturaA (char nombre_archivo[])
{
    system("cls");
    stFactura a;
    FILE * archivoDeFacturaA= fopen(nombre_archivo, "rb");
    if(archivoDeFacturaA!=NULL)
    {
        while(fread(&a,sizeof(stFactura), 1, archivoDeFacturaA)>0)
        {
            mostrarFactura(a);
        }
    }
    fclose(archivoDeFacturaA);
}


void muestraAFacturaB(char nombre_archivo[])
{
    system("cls");
    stFactura a;
    FILE * archivoFacturaB= fopen(nombre_archivo, "rb");
    if(archivoFacturaB!=NULL)
    {
        while(fread(&a,sizeof(stFactura), 1, archivoFacturaB)>0)
        {
            mostrarFactura(a);
        }
    }
    fclose(archivoFacturaB);
}

///Por último, debemos averiguar si un Monotributista tiene cargada por lo menos 1 factura en el archivo de “facturasA” y por lo menos 1 factura en el archivo de “facturasB”.
///La búsqueda se realiza por el cuit del Monotributista que se recibe por parámetro. La función deberá retornar 0 o 1, es decir, si encontró o no que el cuit en ambos archivos.
///Puede modularizar lo que considere necesario.


int busqueda (char mono[], char facturaA[], char facturaB[], long int cuit)
{
    FILE * archivoMonotributista=NULL;
    FILE * archivoFacturaA=NULL;
    FILE * archivoFacturaB=NULL;
    archivoMonotributista=fopen(mono, "rb");
    archivoFacturaA=fopen(facturaA, "rb");
    archivoFacturaB=fopen(facturaB, "rb");
    int flag=0;
    stMonotributista aux;

    if(archivoFacturaB!=NULL && archivoFacturaA!=NULL && archivoMonotributista!=NULL)
    {

        while (flag==0 && !feof(archivoMonotributista))
        {
            fread(&aux,sizeof(stMonotributista), 1, archivoMonotributista);
            if (!feof(archivoMonotributista))
            {
                if (aux.cuit==cuit)
                {
                    flag=1;
                }
                else
                {
                    printf("no se encuentra en el archivo esta persona");
                }
            }
        }
        fclose(archivoFacturaA);
        fclose(archivoFacturaB);
        fclose(archivoMonotributista);

    }
    return flag;
}










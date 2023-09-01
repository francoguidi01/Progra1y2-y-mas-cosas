#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
///-------------------------------------------------Estructuras-------------------------------------------------------------
typedef struct
{

    char nombre[30];
    float precio;
    int eliminado;
} stCompra;

typedef struct
{
    char nombre[30];
    stCompra Coso;
} stPersona;

///-------------------------------------------------Prototipado-------------------------------------------------------------
int cargarPersonas (stPersona A[], int dimension);
int cargarCompra (stCompra A[], int dimension);
int verificacionNumerosRandom (int validos, int numeroRand, int arregloNumerosRandom[]);
int verificarSiesIgual (int validos, int numeroRand, int arregloNumerosRandom[]);

void inicArray(int A[], int dim);
void mostrarQueTeToca(stPersona A[],stCompra B[], int validosC, int validosP);
void muestraArreglos (int A[], int validos);
///-------------------------------------------------------------------------------------------------------------------------

int main()
{
    srand(time(NULL));

    stPersona people [100];
    stCompra compra [100];

    int validosP=0, validosC=0;

    validosP = cargarPersonas(people,100);
    validosC = cargarCompra(compra,100);
    mostrarQueTeToca(people, compra, validosC, validosP);

    return 0;
}

int cargarPersonas (stPersona A[], int dimension)
{
    int i=0;
    char control = 's';
    system("cls");

    while(i<dimension && control=='s')
    {
        printf("\nIngrese el nombre: ");
        fflush(stdin);
        gets(A[i].nombre);
        i++;
        printf("\nDesea agregar otra persona? (S/N): ");
        fflush(stdin);
        scanf("%c", &control);
    }

    return i;
}

int cargarCompra (stCompra A[], int dimension)
{
    int i=0;
    char control = 's';
    system("cls");

    while(i<dimension && control=='s')
    {
        printf("\nIngrese nombre del producto: ");
        fflush(stdin);
        gets(A[i].nombre);
        printf("\nIngrese el precio: ");
        scanf("%f", &A[i].precio);

        i++;
        printf("\nDesea agregar otro producto? (S/N): ");
        fflush(stdin);
        scanf("%c", &control);
    }
    return i;
}

void inicArray(int A[], int dim)
{
    for(int i=0; i<dim; i++)
        A[i]=-1;
}

void mostrarQueTeToca(stPersona A[],stCompra B[], int validosC, int validosP)
{
    int i=0;
    int posP=0, posC=0;


    int numP [100];
    int numC [100];

///Siempre inicializa las array en -1 para que el 0 no termine siempre al final o por si hay basura

    inicArray(numC, 100);
    inicArray(numP,100);

    system("cls");

    while (i<validosC)
    {
///Genera numero random para la posicion

        posP=rand()%(validosP);
        posC=rand()%(validosC);

///Verifica si el numero random se repite, para que no haya 2 personas o productos iguales

        posP=verificacionNumerosRandom(validosP,posP,numP);
        posC=verificacionNumerosRandom(validosC,posC,numC);

///Asigna el numero random ya verificado en una array para que se siga verificando

        numP[i]=posP;
        numC[i]=posC;

///Muestra la persona y el producto a partir del numero random generado

        printf("----------------------------------------------------------------\n");
        printf("Persona: %s \n", A[posP].nombre);
        printf("Compra: %s\nPrecio:%0.2f \n", B[posC].nombre, B[posC].precio);
        i++;

    }

}

void muestraArreglos (int A[], int validos)
{
    int i=0;

    printf("\nContenido del arreglo\n");

    for(i=0; i<validos; i++)
    {

        printf(" %d ",A[i]);

    }
    system("pause");
}

int verificacionNumerosRandom (int validos, int numeroRand, int arregloNumerosRandom[])
{
    int flag=1;

    while (flag==1)
    {
        flag=verificarSiesIgual(validos,numeroRand,arregloNumerosRandom);

        if (flag==1)
        {
            numeroRand=rand()%(validos);
        }

    }
    return numeroRand;
}

int verificarSiesIgual (int validos, int numeroRand, int arregloNumerosRandom[])
{
    int i=0;
    int flag=0;

    while (i<validos)
    {

        if (arregloNumerosRandom[i]==numeroRand)
        {
            flag=1;
        }
        i++;
    }
    return flag;
}

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


typedef struct
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int rol;
    int activo;

} stCliente;

//---------------------------[MENU]----------------------------------//
int main()
{
    system(" color 0B");
    char rutaDelArchivo []= {"archivoDeCliente.dat"};
    int validos=0;
    int dim=100;
    stCliente cliente[dim];
    registrarse(rutaDelArchivo);
//    validos=agregarUsuarioManualAdmin(cliente, 3);
//    mostrarTodosLosClientesAdmin(cliente,validos);
//    iniciarSesion(cliente,validos);

    return 0;
}

//---------------------------[FUNCIONES SIN TERMINAR]----------------------------------//

///Para esto falta inicializar al admin y depende quien se registrara
/// se le habilitara las funciones de cada uno(Hay que aprender a usar strcmp)

//int ingresoAdminOUsuario(stCliente cliente[])
//{
//    int i=0;
//
//    registrarse(cliente);
//
//   if(strcmp(cliente[i].password, usuario)==0)
//{
//        printf("Buen dia Admin como se encuentra usted, que desea hacer?");
//    }
//    else
//    {
//        printf("Pedite esta por delivery");
//    }
//}

///Esto era para modulizar pero hay un error que seguro es algo muy sencillo pero no lo encontramos al final.

//void respuesta ( stCliente cliente[],char nombreUsuario[],int i,int flag)
//{
//
//
//    if (flag==1)
//    {
//        printf("\nUsuario ya registrado, por favor vuelva a intentarlo\n");
//    }
//    else if (flag==0)
//    {
//        strcpy(cliente[i].userName, nombreUsuario);
//    }
//    else
//    {
//        printf("----------#!$%#ERROR#%$!#----------");
//    }
//}
//---------------------------[FUNCIONES BIEN]----------------------------------//
void registrarse (char r[])
{
    int i=0;
    char control='s';
   // char rutaDelArchivo []= {"archivoDeCliente.dat"};

    FILE * archivoDeCliente = fopen(r, "ab");
    stCliente a;
    if (archivoDeCliente!=NULL)
    {
        a.idCliente=0;
        a.activo=1;
        printf("\nIngrese su nombre: ");
        fflush(stdin);
        scanf("%s", &a.nombre);
        printf("\nIngrese su apellido: ");
        fflush(stdin);
        scanf("%s", &a.apellido);
        printf("\nIngrese su nombre se usuario: ");
        fflush(stdin);
        scanf("%s", &a.userName);
        printf("\nIngrese su genero (M/F/O): ");
        fflush(stdin);
        scanf("%c",&a.genero);
        printf("\nIngrese su email: ");
        fflush(stdin);
        scanf("%s",&a.mail);
        printf("\nIngrese su contrase%ca (No mas de 10 caracteres): ",164);
        fflush(stdin);
        scanf("%s",&a.password);
        fwrite(&a, sizeof(stCliente), 1, archivoDeCliente);
    }
    fclose(archivoDeCliente);
//    cliente[i].idCliente=i;
//    cliente[i].activo=1;
//
//    printf("\nIngrese su nombre: ");
//    fflush(stdin);
//    scanf("%s", &cliente[i].nombre);
//    printf("\nIngrese su apellido: ");
//    fflush(stdin);
//    scanf("%s", &cliente[i].apellido);
//    printf("\nIngrese su nombre se usuario: ");
//    fflush(stdin);
//    scanf("%s", &cliente[i].userName);
//    printf("\nIngrese su genero (M/F/O): ");
//    fflush(stdin);
//    scanf("%c",&cliente[i].genero);
//    printf("\nIngrese su email: ");
//    fflush(stdin);
//    scanf("%s",&cliente[i].mail);
//    printf("\nIngrese su contrase%ca (No mas de 10 caracteres): ",164);
//    fflush(stdin);
//    scanf("%s",&cliente[i].password);

    system("cls");

    //return i;
}

int iniciarSesion(stCliente cliente[], int validos)
{
    int i=0;
    char nombreUsuario []="NULL";
    char password []="NULL";

    int flag="NULL";
    int flag2="NULL";

    printf("\nPor favor ingrese su usuario y contrase%ca\n",164);

    do
    {
        printf("\nIngrese su nombre de usuario:");
        fflush(stdin);
        scanf("%s", &nombreUsuario);

        system("cls");

        flag=compararUsuarios(cliente,validos, nombreUsuario);
        usuarioNoExistente(flag);

        i=compararUsuariosRetrnoI(cliente,validos,nombreUsuario);

    }
    while (flag!=1);


    do
    {
        printf("\nIngrese su contrase%ca (No mas de 10 caracteres): ",164);
        fflush(stdin);
        scanf("%s",&password);

        system("cls");

        flag2=compararPassword(cliente,password,i);
        passwordIncorrecta(flag2);

        system("cls");

    }
    while (flag2!=1);

    system("cls");

    printf("Usted inicio sesion correctamente");

}

int agregarUsuarioManualAdmin (stCliente cliente[],int dim)
{
    int i=1, flag=0;
    char control = 's';
    char nombreUsuario[]="NULL";
    printf("\nUsted esta registrando un usuario nuevo\n");

    while (i<dim && control == 's')
    {
        cliente[i].idCliente=i;
        cliente[i].rol=0;
        cliente[i].activo=1;
//-------------------------------------------------------------------------------//
        printf("\nIngrese su nombre: ");
        fflush(stdin);
        scanf("%s", &cliente[i].nombre);
//-------------------------------------------------------------------------------//
        printf("\nIngrese su apellido: ");
        fflush(stdin);
        scanf("%s", &cliente[i].apellido);
//-------------------------------------------------------------------------------//
        do
        {
            printf("\nIngrese su nombre se usuario: ");
            fflush(stdin);
            scanf("%s", &nombreUsuario);
            flag=compararUsuarios(cliente, dim, nombreUsuario);
            usuarioRepetido(flag);

        }
        while (flag!=0);

        strcpy(cliente[i].userName, nombreUsuario);
//-------------------------------------------------------------------------------//
        printf("\nIngrese su genero (M/F/O): ");
        fflush(stdin);
        scanf("%c",&cliente[i].genero);
//-------------------------------------------------------------------------------//
        printf("\nIngrese su email: ");
        fflush(stdin);
        scanf("%s",&cliente[i].mail);
//-------------------------------------------------------------------------------//
        printf("\nIngrese su contrase%ca (No mas de 10 caracteres): ",164);
        fflush(stdin);
        scanf("%s",&cliente[i].password);
//-------------------------------------------------------------------------------//
        printf("\nDESEA CARGAR OTRO CLIENTE -[S]-[N]-: ");
        fflush(stdin);
        scanf("%c", &control);
        i++;
        system("cls");
    }

    return i;
}

void usuarioRepetido (int flag)
{
    if (flag==1)
    {
        printf("\nUsuario ya registrado, por favor vuelva a intentarlo\n");

    }
}

void usuarioNoExistente (int flag)
{
    if (flag==0)
    {
        printf("\nUsuario no existente, por favor vuelva a intentarlo\n");

    }
}

void passwordIncorrecta (int flag)
{
    if (flag==0)
    {
        printf("\nContrase%ca incorrecta, por favor vuelva a intentarlo\n",164);

    }
}

int compararUsuarios (stCliente cliente[],int dim, char usuario[])
{
    int i=0;
    int flag=0;

    while (i<dim && flag==0)
    {
        if(strcmp(cliente[i].userName, usuario)==0)
        {
            flag=1;
        }
        i++;
    }
    return flag;
}

int compararUsuariosRetrnoI (stCliente cliente[],int dim, char usuario[])
{
    int i=0;
    int flag=0;

    while (i<dim && flag==0)
    {
        if(strcmp(cliente[i].userName, usuario)==0)
        {
            flag=1;
        }
        i++;
    }
    return i-1;
}

int compararPassword (stCliente cliente[], char password[],int i)
{
    int flag=0;

    if(strcmp(password,cliente[i].password)==0)
    {
        flag=1;
    }
    return flag;
}

void mostrartodoslosClientes (stCliente cliente[],int validos)
{
    int i;
    system("cls");
    for(i=0; i<validos; i++)
    {
        printf("\n Nombre:%s ", cliente[i].nombre);
        printf("\n Apellido:%s", cliente[i].apellido);
        printf("\n Usuario:%s", cliente[i].userName);
        printf("\n Contrase%ca:%s",164, cliente[i].password);
        printf("\n Mail:%s", cliente[i].mail);
        printf("\n Genero:%c", cliente[i].genero);
    }
}

void mostrarUnCliente (stCliente  cliente[], int x)
{
    system("cls");
    printf("\n Nombre:%s ", cliente[x].nombre);
    printf("\n Apellido:%s", cliente[x].apellido);
    printf("\n Usuario:%s", cliente[x].userName);
    printf("\n Contrase%ca:%s",164, cliente[x].password);
    printf("\n Mail:%s", cliente[x].mail);
    printf("\n Genero:%c", cliente[x].genero);
    printf("\n Rol:%d", cliente[x].rol);
}

void mostrarTodosLosClientesAdmin (stCliente cliente[],int validos)
{
    int i;
    system("cls");
    printf("Estos son todos los clientes Admin");
    for(i=0; i<validos; i++)
    {
        printf("\n Este es el ID:[%d]",cliente[i].idCliente);
        printf("\n Este es el rol del usuario:[%d]", cliente[i].rol);
        printf("\n Nombre:%s ", cliente[i].nombre);
        printf("\n Apellido:%s", cliente[i].apellido);
        printf("\n Usuario:%s", cliente[i].userName);
        printf("\n Contrase%ca:%s",164, cliente[i].password);
        printf("\n Mail:%s", cliente[i].mail);
        printf("\n Genero:%c", cliente[i].genero);
    }
}

void mostrarUnClienteAdmin (stCliente cliente[],int x)
{
    int i;
    system("cls");
    printf("Este es el cliente buscado Admin");

    printf("\n Este es el ID:[%d]",cliente[x].idCliente);
    printf("\n Este es el rol del usuario:[%d]", cliente[x].rol);
    printf("\n Nombre:%s ", cliente[x].nombre);
    printf("\n Apellido:%s", cliente[x].apellido);
    printf("\n Usuario:%s", cliente[x].userName);
    printf("\n Contrase%ca:%s",164, cliente[x].password);
    printf("\n Mail:%s", cliente[x].mail);
    printf("\n Genero:%c", cliente[x].genero);
}

int buscarcliente (stCliente cliente[],int validos,int idCliente)
{
    int i=0, posicion=0;
    int flag=0;

    while (i<validos && flag==0)
    {
        if(cliente[i].idCliente==idCliente)
        {
            flag=1;
            posicion=i;
        }
        i++;
    }
    return posicion;
}

int darDeBaja (stCliente cliente[],int validos)
{
    int idcliente=0;
    int x=0;
    char control='s';

    do
    {
        printf("\nIntroduzca el ID del cliente al que quiere dar de baja: ");
        scanf("%d",&idcliente);
        x=buscarcliente(cliente,validos,idcliente);
        cliente[x].activo=0;
        printf("\nDesea dar de baja a otro usuario? -[S]-[N]-: ");
        fflush(stdin);
        scanf("%c", &control);
    }
    while(control=='s');
}

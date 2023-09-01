#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>      /// Incluye un soporte para amplios tipos de caracteres.
#include <locale.h>     /// Incluye el soporte para distintos tipos de formatos de fecha, moneda, texto, etc.
#include <windows.h>

#include "productos.h"
#include "ADL.h"
#include "nodo.h"
#include "arboles.h"
#include "clientes.h"

#define ESC 27
#define ENTER 13
#define FLECHAARRIBA 72
#define FLECHAABAJO 80
#define ARROBA 64

///modificar a alguien  cuando se pasa al archivo es espantoso
///verficacion para pasar cliente al archivo
///busqueda arbo binario

int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio);
void menuNavegable (stCelda adl[], int * validos, int * dimension);
int flechas (int menu,int menuinicio,int menufin, int lineainicio);
void ejey (int y);

int main()
{
    char rutaDelArchivo []= {"Clientes.dat"};

    int validos=0;

    validos=contarClientes(rutaDelArchivo);
    int dimension = validos;

    saltoDeLinea(2);
    printf("Total de clientes en archivo: %d",validos);
    saltoDeLinea(2);

    stCelda * ADL = (stCelda*) malloc(dimension*sizeof(stCelda));

    validos=deArchivoAAdl(ADL, rutaDelArchivo);

    mostrarAdlAdmin(ADL,validos);
    system("pause");

   // modificarCliente(ADL,107,validos);

    menuNavegable(ADL,&validos,&dimension);

    deAdlAlArchivo(rutaDelArchivo,ADL,validos);

    mostrarAdlAdmin(ADL,validos);


    return 0;
}

int menuConfiguracionDeUsuario (stCelda adl[],int validos, int idUser)
{
    int eleccion=0, flagVolver=0;
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuario(1,1,7,1);
    switch (eleccion)
    {
    case 1:
        system("cls");
        modificarNombre(adl,idUser,validos);
        break;
    case 2:
        system("cls");
        modificarApellido(adl,idUser,validos);
        break;
    case 3:
        system("cls");
        modificarEmail(adl,idUser,validos);
        break;
    case 4:
        system("cls");
        modificarPassword(adl,idUser,validos);
        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaUnUser(adl,idUser,validos);
        if (flagVolver==2)
        {
            mensajeDespedida();
        }
        break;
    case 6:
        system("cls");
        mostrarCliente(adl[buscaPosIdClienteCelda(adl, idUser, validos)].cliente);
        system("pause");
        break;
    case 7:
        flagVolver=0;
        break;
    default:
        system("cls");
        printf("\t\t\t*===============================:C#*#ERROR#*#:D===============================\n*");
        break;
    }
    return flagVolver;
}

int menuUsuario (int elecion,stCelda adl[],int validos,int idUser)
{
//    int dimensionFecha = 80;
//    char fecha[dimensionFecha];
    int flag2=0;
   // int  idPedidoExterno=0;

    switch(elecion)
    {
    case 1:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        altaPedido(r,p,c,idUser,fecha,dimensionFecha);
        break;
    case 2:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        mostrarUnUserPedidos(r,idUser);
//        printf("\t\t\t\t\t\n Ingrese el ID del Pedido que desea cancelar: ");
//        scanf("%d",&idPedidoExterno);
//        flag2=darDeBajaUnPedido(r,idPedidoExterno);
        break;
    case 3:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        mostrarUnUserPedidos(r,idUser);
        saltoDeLinea(1);
        system("pause");
        break;
    case 4:
        system("cls");
        flag2=menuConfiguracionDeUsuario(adl,validos,idUser);
        break;
    case 5:
        mensajeDespedida();
        flag2=2;
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }

    return flag2;
}

int menuAdmin (int elecion,stCelda adl[],int validos,int idUser)
{
//    int dimensionFecha = 80;
//    char fecha[dimensionFecha];
    int flag2=0;
    int idUserExterno=0;

    switch(elecion)
    {

    case 1:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        altaProductos(p);
        break;
    case 2:
        system("cls");
        mostrarAdlAdmin(adl,validos);
        system("pause");
        break;
    case 3:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        mostrarProductos(p);
        system("pause");
        break;
    case 4:
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        altaPedido(r,p,c,idUser,fecha,dimensionFecha);
        break;
    case 5:
        system("cls");
        mostrarAdlAdmin(adl,validos);
        printf("\t\t\t\t\t\n Ingrese el ID del usuario del cual desea ver sus pedidos: ");
        scanf("%d",&idUserExterno);
        system("cls");
        printf("Hay que ponerlo o adaptarlo");
//        mostrarUnUserPedidosAdmin(r,idUserExterno);
        saltoDeLinea(5);
        system("pause");
        break;
    case 6:
        system("cls");
        mostrarAdlAdmin(adl,validos);
        printf("\t\t\t\t\t\n Ingrese el ID del usuario que desea dar de alta o de baja: ");
        scanf("%d",&idUserExterno);
        flag2=darDeBajaODarDeAlta(adl,idUserExterno,validos);
        break;
    case 7:
        system("cls");
        printf("\t\t\t\t\t\n Ingrese el ID del usuario que desea modificar: ");
        scanf("%d",&idUserExterno);
        flag2=menuConfiguracionDeUsuario(adl,validos,idUserExterno);
        break;
    case 8:
        mensajeDespedida();
        flag2=2;
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }
    return flag2;
}

int puntosParaElegirPaso1 (int eleccion, int eleccionMenu, stCelda adl[], int * validos, int *dimension)
{
    int idUser=0;

    printf("\n\n\n\n");
    switch (eleccion)
    {
    case 1:
        system("cls");
        registrarse(adl,validos,dimension);
        break;
    case 2:
        system("cls");
        idUser=iniciarSesion(adl,*validos);
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }
    return idUser;
}

int sistemanavegableRegistrarse (int menu,int menuinicio,int menufin, int lineainicio)
{


    printf("\t\t\t*==========================ApPatacon==========================*\n");

    printf("\t\t\t\t1-Registrarse\n");
    printf("\t\t\t\t2-Iniciar sesion\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableIngresarOVolver (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t*====================================================*\n");

    printf("\n\t\t\t\t1-Ingresar ID del usuario");
    printf("\n\t\t\t\t2-Volver");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t*====================================================*\n");

    printf("\t\t\t\t1-Cambiar nombre\n");
    printf("\t\t\t\t2-Cambiar apellido\n");
    printf("\t\t\t\t3-Cambiar Email\n");
    printf("\t\t\t\t4-Cambiar contraseña\n");
    printf("\t\t\t\t5-Darse de baja\n");
    printf("\t\t\t\t6-Ver datos\n");
    printf("\t\t\t\t7-Volver\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int flechas (int menu,int menuinicio,int menufin, int lineainicio)
{
    int opcion=0;

    ejey(lineainicio);
    printf("\t\t\t----->");

    do
    {
        Sleep(100);
        opcion=getch();
        if(opcion==224)
        {
            opcion=getch();

            if (opcion==FLECHAARRIBA)
            {
//                menu=menu==menuinicio ? menufin: --menu;
                if (menu==menuinicio)
                {
                    menu=menufin;
                }
                else
                {
                    --menu;
                }
                printf("\r                               ");
                ejey(lineainicio + menu-1);
                printf("\t\t\t----->");
            }
            else if (opcion==FLECHAABAJO)
            {
//                menu=menu==menufin ? menuinicio: ++menu;
                if(menu==menufin)
                {
                    menu=menuinicio;
                }
                else
                {
                    ++menu;
                }
                printf("\r                               ");
                ejey(lineainicio + menu-1);
                printf("\t\t\t----->");
            }
        }
    }
    while(opcion !=ENTER);
    return menu;
}

int sistemanavegableMenuBajaAlta (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t*-----------------------------------------------------------*\n");

    printf("\t\t\t\t1-Dar de baja\n");
    printf("\t\t\t\t2-Dar de alta\n");
    printf("\t\t\t\t3-Volver\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t*---------------------------ATENCION----------------------------*\n");
    printf("\t\t\t*--------------------USTED POR DARSE DE BAJA--------------------*\n");
    printf("\t\t\t*-----------NO PODRA VOLVER A INGRESAR CON ESTE USUARIO---------*\n");
    printf("\t\t\t\t1-Darse de baja\n");
    printf("\t\t\t\t2-Volver\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuBajaPedido (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t*---------------------------ATENCION----------------------------*\n");
    printf("\t\t\t*---------------USTED ESTA POR DAR DE BAJA SU PEDIDO-----------------*\n");
    printf("\t\t\t\t1-Dar de baja su pedido\n");
    printf("\t\t\t\t2-Volver\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuUsuario (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t*==========================Bienvenido==========================*\n");

    printf("\t\t\t\t1-Hacer un Pedido\n");
    printf("\t\t\t\t2-Cancelar un pedido\n");
    printf("\t\t\t\t3-Mostrar un Pedido\n");
    printf("\t\t\t\t4-Configuracion de usuario\n");
    printf("\t\t\t\t5-Cerrar sesion\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableMenuAdmin (int menu,int menuinicio,int menufin, int lineainicio)
{
    system("cls");

    printf("\t\t\t*==========================Bienvenido Admin==========================*\n");

    printf("\t\t\t\t1-Agregar productos\n");
    printf("\t\t\t\t2-Mostrar usuarios registrados\n");
    printf("\t\t\t\t3-Mostrar productos cargados en sistema\n");
    printf("\t\t\t\t4-Hacer un pedido\n");
    printf("\t\t\t\t5-Buscar pedidos de un usuario\n");
    printf("\t\t\t\t6-Dar de baja o de alta un usuario\n");
    printf("\t\t\t\t7-Modificar/ver datos de un usuario\n");
    printf("\t\t\t\t8-Cerrar sesion\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

void menuNavegable (stCelda adl[], int * validos, int * dimension)
{
    int flag=0;
    int eleccion=0;
    int eleccionMenu=0;
    int idUser=0;

    do
    {
        system("cls");

        eleccion=sistemanavegableRegistrarse(1,1,2,1);

        idUser=puntosParaElegirPaso1(eleccion,eleccionMenu,adl,validos,dimension);
        system("cls");

        if (idUser==0)
        {
            flag=1;
        }

        else if (adl[buscaPosIdClienteCelda(adl,idUser,*validos)].cliente.rol==1)
        {
            do
            {
                eleccionMenu=sistemanavegableMenuAdmin(1,1,8,1);

                flag=menuAdmin(eleccionMenu,adl,*validos,idUser);
            }
            while(flag==0);
        }
        else
        {
            do
            {
                eleccionMenu=sistemanavegableMenuUsuario(1,1,5,1);

                flag=menuUsuario(eleccionMenu,adl,*validos,idUser);

            }
            while(flag==0);
        }
    }
    while(flag==1);
}

void gotoxy (int x, int y) /// POSICIONAMIENTO DEL CURSOR PARA IMPRIMIR POR PANTALLA.
{
    HANDLE hCon; /// Identificador de consola.
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X=x;
    posicion.Y=y;
    SetConsoleCursorPosition(hCon,posicion);
}

void ejey (int y)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X=0;
    pos.Y=y;

    SetConsoleCursorPosition(hConsole, pos);
}

void  obtenerFecha(char F[],int dimension)
{
    time_t t;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);
    strftime(F,dimension,"%d-%m-%Y %I:%M%p",tm);

}





//void mostrarUserRegistro(char archivos[])
//{
//    stCliente clientes;
//
//    FILE *archivoDeCliente = fopen(archivos,"rb");
//
//    printf("\n\t\tCLIENTES REGISTRADOS .....\n");
//
//    printf("\t\t ========================== \n");
//
//    if(archivoDeCliente!= NULL)
//    {
//        while(fread(&clientes,sizeof(stCliente),1,archivoDeCliente)>0)
//        {
//            printf("IdCliente: %d \n",clientes.idCliente);
//            printf("NOMBRE: %s \n",clientes.nombre);
//            printf("APELLIDO: %s \n",clientes.apellido);
//            printf("UserName: %s \n",clientes.userName);
//            printf("pass: %s \n",clientes.password);
//            printf("EMAIL: %s \n",clientes.mail);
//            printf("GENERO: %c \n",clientes.genero);
//            printf("ROL: %d \n",clientes.rol);
//            printf("ACTIVO: %d \n",clientes.activo);
//            printf("\n ========================== \n");
//        }
//    }
//
//    printf("\nFIN DE CLIENTES REGISTRADOS....\n");
//    fclose(archivoDeCliente);
//
//}

//int registrarsearchivo (char C[])
//{
//
//    int i=0, flag=0, flag2=0;
//    int idCliente;
//    char nombreUsuario [20];
//    char mailcopy [100];
//    stCliente cl;
//
//    FILE *archivoDeCliente = fopen(C,"ab");
//
//    idCliente = ultimoIdCliente(C);
//    cl.idCliente = idCliente + 1;
//    cl.rol = 0;
//
//    if(archivoDeCliente!= NULL)
//    {
//        printf("\n\t\t\tIngrese su nombre: ");
//        fflush(stdin);
//        gets(cl.nombre);
//
//        printf("\n\t\t\tIngrese su apellido: ");
//        fflush(stdin);
//        gets(cl.apellido);
//
//        do
//        {
//            printf("\n\t\t\tIngrese su nombre se usuario: ");
//            fflush(stdin);
//            scanf("%s", nombreUsuario);
//            flag=compararUsuarios(C,nombreUsuario);
//            usuarioRepetido(flag);
//        }
//        while (flag!=0);
//        strcpy(cl.userName, nombreUsuario);
//
//        printf("\n\t\t\tIngrese su genero (Solo inicial): ");
//        fflush(stdin);
//        scanf("%c",&cl.genero);
//        do
//        {
//            printf("\n\t\t\tIngrese su email: ");
//            fflush(stdin);
//            gets(mailcopy);
//            flag2=verificacionEmail(mailcopy);                  ///Esto funciona a la inversa de la funcion comparar usuarios
//            mailInvalido(flag2);                              ///porque en este tiene que encontralo y en la funcion comparar no.
//        }
//        while(flag2==0);
//
//        strcpy(cl.mail, mailcopy);
//
//        printf("\n\t\t\tIngrese su contraseña (No mas de 10 caracteres): ");
//        fflush(stdin);
//        asteriscos(cl.password);
//
//        cl.activo = 1;
//
//        fwrite(&cl,sizeof(stCliente),1,archivoDeCliente);
//        i++;
//    }
//    fclose(archivoDeCliente);
//    system("cls");
//    saltoDeLinea(3);
//    printf("\t\t\t\t====== Usted se ha registrado exitosamente ======");
//    saltoDeLinea(2);
//    printf("\t\t\t\tPor favor. ");
//    system("pause");
//    return i;
//}
//
//int ultimoIdCliente(char C[])
//{
//    int a = 99;
//    stCliente cl;
//
//    FILE *archivoClientes = fopen(C,"rb");
//
//    if(archivoClientes != NULL)
//    {
//        while(fread(&cl,sizeof(stCliente),1,archivoClientes)>0)
//        {
//            a = cl.idCliente;
//        }
//
//    }
//
//    fclose(archivoClientes);
//
//    return a;
//}

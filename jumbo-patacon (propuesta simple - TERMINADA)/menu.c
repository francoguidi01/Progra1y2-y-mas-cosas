#include "menu.h"
int menuConfiguracionDeUsuario (stCelda adl[],int posCliente)
{
    int eleccion=0, flagVolver=0;
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuario(1,1,7,1);

    switch (eleccion)
    {
    case 1:
        system("cls");
        modificarNombre(adl,posCliente);
        break;
    case 2:
        system("cls");
        modificarApellido(adl,posCliente);
        break;
    case 3:
        system("cls");
        modificarEmail(adl,posCliente);
        break;
    case 4:
        system("cls");
        modificarPassword(adl,posCliente);
        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaUnUser(adl,posCliente);
        if (flagVolver==2)
        {
            mensajeDespedida();
        }
        break;
    case 6:
        system("cls");
        mostrarCliente(adl[posCliente].cliente);
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

int menuConfiguracionDeUsuarioParaAdmin (stCelda adl[],int posCliente)
{
    int eleccion=0, flagVolver=0;
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuarioParaAdmin(1,1,7,1);

    switch (eleccion)
    {
    case 1:
        system("cls");
        modificarNombre(adl,posCliente);
        break;
    case 2:
        system("cls");
        modificarApellido(adl,posCliente);
        break;
    case 3:
        system("cls");
        modificarEmail(adl,posCliente);
        break;
    case 4:
        system("cls");
        modificarPassword(adl,posCliente);
        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaODarDeAlta(adl,posCliente);
        if (flagVolver==2)
        {
            mensajeDespedida();
        }
        break;
    case 6:
        system("cls");
        mostrarCliente(adl[posCliente].cliente);
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
int menuUsuario (int eleccionMenu,stCelda adl[],int validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados,int * ultimoIdPedido)
{

    int flag2=0;
    stPedido dato;

    switch(eleccionMenu)
    {
    case 1:
        system("cls");

        dato=hacerPedidoMagicJohnson(adl,arbolProd,posCliente,ultimoIdPedido);
        deCabeceraAlArchivo("CabeceraPedidos.dat",dato);

        break;
    case 2:
        system("cls");
        adl[posCliente].costoTotalDelPedido=calcularTotalPrecioProductos(adl[posCliente].listaDeProductos);
        saltoDeLinea(4);
        printf("\t\t\t\t----------Usted lleva gastado: %.2f----------", adl[posCliente].costoTotalDelPedido);
        saltoDeLinea(4);
        printf("\t\t\t\tPor favor, ");
        system("pause");

        break;
    case 3:
        system("cls");

        if(adl[posCliente].listaDeProductos==NULL)
        {
            printf("No hay ningun pedido ");
        }
        else
        {
            mostrarListaRecursivaProductos(adl[posCliente].listaDeProductos);
        }
        saltoDeLinea(1);
        system("pause");
        break;
    case 4:
        system("cls");

        flag2=menuConfiguracionDeUsuario(adl,posCliente);
        modificarChabonArchi("ClientesAlta.dat",adl[posCliente].cliente);

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

int menuAdmin (int elecion,stCelda adl[],int validos,int posCliente, nodoArbol * arbolProd, nodoArbol * arbolProdAnulados, int * ultimoIdPedido)
{

    int flag2=0;
    int idUserExterno=0;
    int posUnUser=0;
    int idProducto=0;
    stPedido dato;
    switch(elecion)
    {

    case 1:
        system("cls");

        arbolProd=cargarElArbol(arbolProd);

        break;
    case 2:
        system("cls");
        mostrarAdlAdmin(adl,validos);
        system("pause");
        break;
    case 3:
        system("cls");
        saltoDeLinea(2);

        printf("\t\t------------------------------Productos en sistema------------------------------");
        saltoDeLinea(2);
        inorder(arbolProd);
        saltoDeLinea(2);

        printf("\t\t------------------------------Productos fuera de sistema------------------------------");
        saltoDeLinea(2);
        inorder(arbolProdAnulados);
        system("pause");
        break;
    case 4:
        system("cls");
        dato=hacerPedidoMagicJohnson(adl,arbolProd,posCliente,ultimoIdPedido);
        deCabeceraAlArchivo("CabeceraPedidos.dat",dato);
        break;
    case 5:
        system("cls");

        mostrarAdlAdmin(adl,validos);

        printf("\t\t\t\t\t\n Ingrese el ID del usuario del cual desea ver sus pedidos: ");
        scanf("%d",&idUserExterno);
        system("cls");

        posUnUser=buscaPosIdClienteCelda(adl,idUserExterno,validos);

        deArchivoACabecera(adl,"CabeceraPedidos.dat",validos,posUnUser,arbolProd);

        if(adl[posCliente].listaDeProductos==NULL)
        {
            printf("No hay ningun pedido ");
        }
        else
        {
            mostrarListaRecursivaProductos(adl[posUnUser].listaDeProductos);
        }

        saltoDeLinea(5);
        system("pause");
        break;
    case 6:
        system("cls");
        inorder(arbolProd);
        printf("Escriba el id producto a borrar: ");
        scanf("%d",&idProducto);
        nodoArbol * nodoABorrar=inicArbol();
        nodoABorrar=buscarPorID(arbolProd, idProducto);
        nodoABorrar->dato.productoAnulado=1;
        arbolProdAnulados = insertarPorId(arbolProdAnulados, nodoABorrar->dato);
        modificarProductoArchi("ProductosAlta.dat",nodoABorrar->dato);
        arbolProd=borrarNodoArbol(arbolProd, nodoABorrar->dato);

///modularizar
        system("pause");
        break;
    case 7:
        system("cls");
        mostrarAdlAdmin(adl,validos);

        printf("\t\t\t\t\t\n Ingrese el ID del usuario que desea modificar: ");
        scanf("%d",&idUserExterno);

        posUnUser=buscaPosIdClienteCelda(adl,idUserExterno,validos);
        flag2=menuConfiguracionDeUsuarioParaAdmin(adl,posUnUser);
        modificarChabonArchi("ClientesAlta.dat",adl[posUnUser].cliente);

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

int puntosParaElegirPaso1 (int eleccionMenu, stCelda adl[], int * validos, int *dimension)
{
    int idUser=0, posCliente=-1;

    printf("\n\n\n\n");
    switch (eleccionMenu)
    {
    case 1:
        system("cls");
        registrarse(&adl,validos,dimension);
        deAdlAlArchivoAlFinal("ClientesAlta.dat", adl[(*validos)-1].cliente);
        break;
    case 2:
        system("cls");

        idUser=iniciarSesion(adl,*validos);
        posCliente=buscaPosIdClienteCelda(adl, idUser,*validos);
        break;
    default:
        printf("\t\t\t*==========================:C#*#ERROR#*#:D==========================\n*");
        break;
    }
    return posCliente;
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
    printf("\t\t\t\t4-Cambiar contrase%ca\n",164);
    printf("\t\t\t\t5-Darse de baja\n");
    printf("\t\t\t\t6-Ver datos\n");
    printf("\t\t\t\t7-Volver\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}

int sistemanavegableConfiguracionUsuarioParaAdmin (int menu,int menuinicio,int menufin, int lineainicio)
{
    printf("\t\t\t*====================================================*\n");

    printf("\t\t\t\t1-Cambiar nombre\n");
    printf("\t\t\t\t2-Cambiar apellido\n");
    printf("\t\t\t\t3-Cambiar Email\n");
    printf("\t\t\t\t4-Cambiar contrase%ca\n",164);
    printf("\t\t\t\t5-Dar de baja o dar de alta\n");
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
    printf("\t\t\t\t2-Todo lo gastado\n");
    printf("\t\t\t\t3-Mostrar pedidos\n");
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
    printf("\t\t\t\t6-Borrar un producto\n");
    printf("\t\t\t\t7-Modificar/ver datos de un usuario\n");
    printf("\t\t\t\t8-Cerrar sesion\n");

    int menu2=0;
    menu2=flechas( menu, menuinicio, menufin, lineainicio);

    return menu2;
}



void menuNavegable (stCelda adl[], int * validos, int * dimension)
{

    //char rutaDelArchivoCabeceraPedidos []= {"CabeceraPedidos.dat"};
    int flag=0;
    int eleccionMenu=0;
    int posCliente=-1;
    int fin=0;
    int finAnulados=0;
    int ultimoIdPedido=0;
    stProducto prodAnulados[100];
    stProducto prod[100];

    nodoArbol * arbolProd=inicArbol();

    fin=deArchivoToArrayProductos(prod,"ProductosAlta.dat");

    arbolProd=deArrayToArbol(prod,0,fin-1);

    ///--------------

    nodoArbol * arbolProdAnulados=inicArbol();

    finAnulados=deArchivoToArrayProductosAnulados(prodAnulados,"ProductosAlta.dat");

    arbolProdAnulados=deArrayToArbol(prodAnulados,0,finAnulados-1);


    do
    {
        system("cls");


        eleccionMenu= sistemanavegableRegistrarse(1,1,2,1);

        posCliente= puntosParaElegirPaso1(eleccionMenu, adl, validos, dimension);

       deArchivoACabecera2(adl, "CabeceraPedidos.dat", *validos, posCliente, arbolProd, arbolProdAnulados);

        printf("4 ");
        system("pause");


        ultimoIdPedido=buscaIdUltimoPedido("CabeceraPedidos.dat");

        system("cls");

        if (posCliente==-1)
        {
            flag=1;
        }

        else if (adl[posCliente].cliente.rol==1)
        {
            do
            {

                eleccionMenu=sistemanavegableMenuAdmin(1,1,8,1);

                flag=menuAdmin(eleccionMenu, adl, *validos, posCliente, arbolProd, arbolProdAnulados, &ultimoIdPedido);
            }
            while(flag==0);
        }
        else
        {
            do
            {

                eleccionMenu=sistemanavegableMenuUsuario(1,1,5,1);

                flag=menuUsuario(eleccionMenu, adl, *validos, posCliente, arbolProd, arbolProdAnulados, &ultimoIdPedido);


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
void logo()
{
    system("color f0");
    puts("                            :=========:====     ====:====-       -==== ========-:        :-=====-:  ");
    puts("                            #@@@@@@@@*#@@@*    :@@@@=@@@@@      =@@@@@.@@@@@@@@@@@+   :+*********##+.       ");
    puts("                           #####@@@@=@@@@-    +@@@%*@@@@@+    +@@@@@*=@@@%***%@@@@: =********######*.      ");
    puts("                               :@@@@=@@@@     %@@@+%@@@@@@   +@@@@@@-#@@@+   =@@@% =******=  =######+      ");
    puts("                               +@@@#*@@@#    .@@@@=@@@%@@@= +@@@@@@@.@@@@%###@@@+ .******=    *#####*      ");
    puts("                               %@@@=@@@@=    =@@@@+@@@-%@@%*@@@-@@@#=@@@@@@@@@@@= :******-    *####**   ");
    puts("                              .@@@@-@@@@:    %@@@+%@@@ =@@@@@%.=@@@=#@@@*:::=@@@@::******+   -####**=      ");
    puts("                              +@@@%.@@@@#-:-%@@@%:@@@*  @@@@@. #@@@.@@@@-  .+@@@@: +******+:+##****+       ");
    puts("                        *-  .%@@@+ *@@@@@@@@@@#.=@@@-  *@@%.  @@@%-@@@@@@@@@@@@+   +*************=        ");
    puts("                      .%@@@%@@@@@.  -#@@@@@%*:  #@@@    ..   -@@@+*@@@@@@@@@#+.     :=********+-.         ");
    puts("                       +@@@@@@@*.      ...                                              ....              ");
    puts("                          -===-                                                                 PATACON    ");

}

void saltoDeLinea (int lineas)
{
    for (int i=0; i<lineas; i++)
    {
        printf("\n");
    }
}

void mensajeDespedida ()
{
    system("cls");
    saltoDeLinea(5);
    printf("\t\t\t *==================== GRACIAS VUELVA PRONTO ====================*");
    saltoDeLinea(12);
}

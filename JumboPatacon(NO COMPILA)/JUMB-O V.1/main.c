#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "productos.h"
#include "pedidos.c"

const char archivoClientes[]= {"clientes.dat"};

const char archivoProductos[]= {"productos.dat"};
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


void logo ();
void pantallaInicial();
///Funciones de login
void menuCliente();
void cliente(int idCliente);
void funcionLogin();
int buscarUsuario(char userIngresado[], FILE * archiC);
int verificarClave(int id,char claveIngresado[], FILE * archiC);
int verificar(char userIngresado[],char claveIngresado[],FILE * archiC);
int buscaRol(char userIngresado[], FILE * archiC);
int verificarEstado(char userIngresado[], FILE * archiC);

///funciones de admin
void cargarArchivoProducto();
void administrarPerfilAdmin(int idCliente);
void administrarClientes(int idCliente);
void administrarPedidos();
void mostrarPedidos();
void estadisticaCliente();
void cambiarRolCliente();
void modificarPedidoAdmin();
void administrarProductos ();
void menuProductos ();

///Funciones de carga de clientes
int verificarUsernameRepetido (char usernameIngresado[]);
int verificarMail(char mailIngresado[]);
stCliente CargarCliente();
void cargarArchivoCliente();
int cantidadClientes();
void mostrarStructCliente(stCliente c);

void listarClientes();
void visualizarPerfil(int id);
stCliente modificacion (stCliente c, int id);
void modificarCliente(int id);
void mostrarUnCliente();
stCliente buscarCliente(FILE * archiC,int id);
void modificarCualquierCliente ();

///funciones pedidos
void menuPedido();
void menuModificarPedidoCliente();

int main()
{
    logo();
    pantallaInicial();
    logo();
    return 0;
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
    puts("                          -===-                                                                           ");

}

void menuInicio()
{
    puts("\n\t\t\t\t\t[=================================]");
    printf("\t\t\t\t\t[       Bienvenido a JUMB-0       ]\n");
    printf("\t\t\t\t\t[ 1-Iniciar Sesion                ]\n");
    printf("\t\t\t\t\t[ 2-Registrarse                   ]\n");
    printf("\t\t\t\t\t[ 0-Salir                         ]\n");
    printf("\t\t\t\t\t[=================================]\n\n\t");
}

void menuAdmin1()
{
    puts("\n\t\t\t\t\t        Hello JUMB-O World!        ");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[--------Menu Administrador-------]\n");
    puts("\t\t\t\t\t[ 1-Perfil de administrador       ]\n");
    puts("\t\t\t\t\t[ 2-Administrar Clientes          ]\n");
    puts("\t\t\t\t\t[ 3-Administrar Pedidos           ]\n");
    puts("\t\t\t\t\t[ 4-Administrar Productos         ]\n");
    puts("\t\t\t\t\t[ 0-Salir                         ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}

void menuPerfilAdmin()
{
    puts("\n\t\t\t\t\t        Hello JUMB-O World!        ");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[-----------Administrador---------]\n");
    puts("\t\t\t\t\t[ 1-Ver perfil                    ]\n");
    puts("\t\t\t\t\t[ 2-Modificar Perfil              ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}
void menuAdminClientes()
{
    puts("\n\t\t\t\t\t        Hello JUMB-O World!        ");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[-------Administar clientes-------]\n");
    puts("\t\t\t\t\t[ 1-Lista de Clientes             ]\n");
    puts("\t\t\t\t\t[ 2-Buscar cliente                ]\n");
    puts("\t\t\t\t\t[ 3-Modificar cliente             ]\n");
    puts("\t\t\t\t\t[ 4-Dar/Quitar Rol Admin          ]\n");
    puts("\t\t\t\t\t[ 5-Estadistica cliente           ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}
void menuAdminPedidos()
{
    puts("\n\t\t\t\t\t        Hello JUMB-O World!        ");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[-------Administrar pedidos-------]\n");
    puts("\t\t\t\t\t[ 1-Lista de pedidos              ]\n");
    puts("\t\t\t\t\t[ 2-Buscar pedido                 ]\n");
    puts("\t\t\t\t\t[ 3-Modificar pedido              ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}


void menuCliente()
{
    puts("\n\t\t\t\t\t        Hello JUMB-O World!        ");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[---------Mi Cuenta JUMB-O--------]\n");
    puts("\t\t\t\t\t[ 1-Pedidos                       ]\n");
    puts("\t\t\t\t\t[ 2-Mi perfil                     ]\n");
    puts("\t\t\t\t\t[ 3-Modificar Perfil              ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}

void menuPedido()
{
    puts("\n\n");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[-----------Menu Pedidos----------]\n");
    puts("\t\t\t\t\t[ 1-Realizar Pedido               ]\n");
    puts("\t\t\t\t\t[ 2-Mis Pedidos                   ]\n");
    puts("\t\t\t\t\t[ 3-Buscar Pedido                 ]\n");
    puts("\t\t\t\t\t[ 4-Modificar Pedido              ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\t");
}
void menuProductos ()
{
    puts("\n\n");
    puts("\t\t\t\t\t[=================================]\n");
    puts("\t\t\t\t\t[-----------Menu Productos--------]\n");
    puts("\t\t\t\t\t[ 1-Cargar Productos              ]\n");
    puts("\t\t\t\t\t[ 2-Dar de baja/anular Productos  ]\n");
    puts("\t\t\t\t\t[ 3-Visualizar Productos          ]\n");
    puts("\t\t\t\t\t[ 4-Eliminar Producto             ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\t");
}

void menuModificarPerfil()
{
    puts("\n\t\t\t\t\t[=================================]");
    puts("\t\t\t\t\t[---------Modificar Perfil--------]\n");
    puts("\t\t\t\t\t[ 1-Nombre                        ]\n");
    puts("\t\t\t\t\t[ 2-Apellido                      ]\n");
    puts("\t\t\t\t\t[ 3-Usuario                       ]\n");
    puts("\t\t\t\t\t[ 4-Clave                         ]\n");
    puts("\t\t\t\t\t[ 5-Mail                          ]\n");
    puts("\t\t\t\t\t[ 6-Genero                        ]\n");
    puts("\t\t\t\t\t[ 7-Baja/Alta                     ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}

void pantallaInicial()
{
    int op1=0;
    do
    {
        system("color f0");
        menuInicio();
        puts("\n\tIngrese una opcion...");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            funcionLogin();
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            cargarArchivoCliente();
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            puts("Gracias por utilizar el servicio\n \n\t\t\t\t\tSaliendo... \n");
            break;
        }
        }
    }
    while (op1!=0);
}

///interaccion con admin
void admin1(int idCliente)
{
    int op1=0;
    do
    {
        system("cls");
        system("color f0");
        menuAdmin1();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            administrarPerfilAdmin(idCliente);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            administrarClientes(idCliente);
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            administrarPedidos();
            system("cls");
            break;
        }
        case 4:
        {
            system("cls");
            administrarProductos();
            system("cls");

            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}
void administrarProductos ()
{
    int op1=0,op=0;
    do
    {
        system("cls");
        system("color f0");
        menuProductos();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            do
            {
                cargarArchivoProducto();
                printf("\nPresione ENTER para seguir cargando productos o ESC para salir\n ");
                op=getch();
            }
            while(op!=27);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            productoAnulado();
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            mostrarProductos();
            getch();
            system("cls");
            break;
        }
        case 4:
        {
            system("cls");
            eliminarProductos();
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}

void administrarPerfilAdmin(int idCliente)
{
    int op1=0;
    do
    {
        system("cls");
        system("color f0");
        menuPerfilAdmin();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            visualizarPerfil(idCliente);
            getch();
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            modificarCliente(idCliente);
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}

void administrarClientes(int idCliente)
{
    int op1=0;
    do
    {
        system("cls");
        system("color f0");
        menuAdminClientes();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            listarClientes();
            getch();
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            mostrarUnCliente();
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            modificarCualquierCliente();
            getch();

            break;
        }
        case 4:
        {
            system("cls");
            ///cambiar rol
            cambiarRolCliente();
            break;
        }
        case 5:
        {
            system("cls");
            ///estadistica clliente
            estadisticaCliente();
            break;
        }

        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}


void administrarPedidos()
{
    int op1=0;
    do
    {
        system("cls");
        system("color f0");
        menuAdminPedidos();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            mostrarPedidos();
            getch();
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            buscarPedido();
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            modificarPedidoAdmin();
            getch();

            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}




///interaccion menu cliente
void cliente(int idCliente)
{
    int op1=0;
    do
    {
        system("cls");
        system("color f0");
        menuCliente();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            system("cls");
            pedidos(idCliente);

            break;
        }
        case 2:
        {
            system("cls");
            visualizarPerfil(idCliente);
            getch();
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            modificarCliente(idCliente);
            getch();
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}

stCliente buscarCliente(FILE * archiC,int id)
{
    stCliente aux;
    int flag=0;

    if(archiC!=NULL)
    {
        while(flag==0 && fread(&aux,sizeof(stCliente),1,archiC))
        {
            if(id==aux.idCliente)
            {
                flag=1;
            }
        }
    }
    if (flag==0)
    {
        aux.idCliente=-1;
        printf("\nNo se encontro el cliente\n");
        system("pause");
    }
    return aux;
}
void modificarCualquierCliente ()
{
    int idConsigna=0;

    FILE * archiC=fopen(archivoClientes,"rb");

    stCliente c;


    printf("\nIngrese ID del cliente a modificar:\n");
    scanf("%i", &idConsigna);

    c=buscarCliente(archiC,idConsigna);
    fclose(archiC);
    if(c.idCliente!=-1)
    {
        modificarCliente(idConsigna);
    }
}
void mostrarUnCliente()
{
    int id=-1;
    FILE * archiC=fopen(archivoClientes,"rb");
    stCliente c;
    fseek(archiC,0,SEEK_SET);
    printf("\n\n\t\tIngrese numero de ID del cliente que desea buscar: ");
    scanf("%d",&id);

    c=buscarCliente(archiC,id);

    if (c.idCliente!=-1)
    {
        mostrarStructCliente(c);
        system("pause");
    }

    fclose(archiC);

}
int buscaRol(char userIngresado[], FILE * archiC)
{
    int rol=-1;
    stCliente aux;
    fseek(archiC, 0, SEEK_SET);
    if (archiC!=NULL)
    {
        while(rol==-1 &&  fread(&aux,sizeof(stCliente),1,archiC)>0)
        {
            if(strcmp(userIngresado,aux.userName)==0)
            {
                rol=aux.rol;
            }
        }

        if (rol==-1)
        {
            printf("\nError en la verificacion de Rol\n");
            system("pause");
        }
    }
    return rol;
}
int verificarEstado(char userIngresado[], FILE * archiC)
{
    int estado=-1;
    stCliente aux;
    fseek(archiC, 0, SEEK_SET);
    if (archiC!=NULL)
    {
        while(estado==-1 &&  fread(&aux,sizeof(stCliente),1,archiC)>0)
        {
            if(strcmp(userIngresado,aux.userName)==0)
            {
                estado=aux.activo;
            }
        }

    }
    return estado;
}

void funcionLogin()
{
    char userIngresado[20];
    char claveIngresado[20];

    int control=0,ret=0,idCliente=0;

    FILE * archiC=NULL;

    archiC=fopen(archivoClientes,"rb");


    do
    {
        system("cls");
        puts("\n\t\t------------------------------Ingrese sus datos para iniciar----------------------------------\n");


        printf("\n\t <>  Usuario: ");
        fflush(stdin);
        gets(userIngresado);

        printf("\n\t <>  Clave: ");
        fflush(stdin);
        int i=-1;
        do
        {
            i++;
            fflush(stdin);
            claveIngresado[i]=getch();
            if(claveIngresado[i]==13)
            {
                claveIngresado[i]='\0';
            }
            else
            {
                printf("*");
            }

        }
        while(claveIngresado[i]!='\0');

        ret=verificar(userIngresado,claveIngresado,archiC);
        if(ret==0)
        {
            system("pause");
            control=27;
        }

    }
    while(ret!=1 && control!=27);
    if(ret==1)
    {
        idCliente=buscarUsuario(userIngresado,archiC);
        if(buscaRol(userIngresado,archiC)==1)
        {
            admin1(idCliente);
        }
        else
        {
            if(verificarEstado(userIngresado,archiC)==1)
            {
                cliente(idCliente);
            }
            else
            {
                printf("\n\n\tCuenta inactiva, para activarla comuniquese con el servicio al cliente de JUMB-O.\n");
                printf("\n\tservicios@jumb0.com.ar\n\n\t");
                system("pause");
            }

        }
        fclose(archiC);
    }

}

int buscarUsuario(char userIngresado[], FILE * archiC)
{
    int pos=-1;
    stCliente aux;
    fseek(archiC, 0, SEEK_SET);
    if (archiC!=NULL)
    {
        while(pos==-1 &&  fread(&aux,sizeof(stCliente),1,archiC)>0)
        {
            if(strcmp(userIngresado,aux.userName)==0)
            {
                pos=aux.idCliente;
            }
        }
        if (pos==-1)
        {
            printf("\nEl usuario no existe\n");
        }
    }
    return pos;
}

int verificarClave(int id, char claveIngresado[], FILE * archiC)
{
    int flag=0;
    stCliente aux;
    fseek(archiC, 0, SEEK_SET);
    if (archiC!=NULL)
    {
        while(fread(&aux,sizeof(stCliente),1,archiC)>0)
        {
            if(id==aux.idCliente)
            {
                if(strcmp(claveIngresado, aux.password)==0)///la posicion no puede ir en esta variable de aux
                {
                    flag=1;
                }
            }
        }
        if(flag==0)
        {
            printf("\nClave incorrecta\n");
        }
    }
    return flag ;
}
int verificar(char userIngresado[],char claveIngresado[],FILE * archiC)
{
    int ret=0,pos=-1;
    pos=buscarUsuario(userIngresado,archiC);
    if(pos!=-1)
    {
        if(verificarClave(pos,claveIngresado,archiC)==1)
        {
            ret=1;
        }
    }
    return ret;
}
int verificarMail(char mailIngresado[])
{
    int i=0,cantArrobas=0, posArroba=0, posPunto=0,verif=0;

    while(mailIngresado[i]!='\0')
    {
        if (mailIngresado[i]=='@')
        {
            posArroba=i;
            cantArrobas++;
        }
        i++;
    }
    if (i>0 && cantArrobas==1)
    {
        i=posArroba+1;
        while(mailIngresado[i]!='\0' && posPunto==0)
        {
            if (mailIngresado[i]=='.')
            {
                posPunto=i;
            }
            i++;
        }
        printf("\t\npos punto %i", posPunto);
        if(mailIngresado[posPunto+1]!='\0')
        {
            verif=1;
        }
    }
    else
    {
        printf("\t \t \nEl e-mail ingresado no es correcto, intentelo nuevamente.\n");
        system("pause");
    }
    return verif;
}
int verificarUsernameRepetido (char usernameIngresado[])
{
    stCliente c;
    int flag=0;
    FILE *archiC=fopen(archivoClientes, "rb");
    fseek(archiC, 0,SEEK_SET);
    if (archiC!=NULL)
    {
        while (fread(&c, sizeof(stCliente),1,archiC)>0 && flag==0)
        {
            if(strcmp(usernameIngresado, c.userName)==0)
            {
                flag=1;
                printf("\t \t \n Nombre de usuario existente, por favor seleccione otro: \n");
                system("pause");
            }
        }
    }
    fclose(archiC);
    return flag;
}

/// Carga cliente
stCliente CargarCliente()
{
    stCliente cliente;
    int idC=0,mal=0;
    char genero=' ';
    idC=cantidadClientes();
    cliente.idCliente=idC+1;
    if (idC==-1)
    {
        strcpy(cliente.userName,"admin");
        strcpy(cliente.password,"admin");
        strcpy(cliente.nombre,"JUMB-O");
        strcpy(cliente.apellido,"Servicios");
        cliente.genero='H';

        strcpy(cliente.mail,"servicio@jumb0.com");
        cliente.rol=1;
        printf("\nGeneracion de usuario administrador, para conocimiento de las credenciales refierase al manual de instrucciones: \n");
        system("pause");
    }
    else
    {

        puts("\n\t\t---------------Ingrese sus datos para registrarse--------------------");

        do
        {
            printf("\n\n\t <>  Usuario: ");
            fflush(stdin);
            gets(cliente.userName);
        }
        while(verificarUsernameRepetido(cliente.userName)==1);

        printf("\n\n\t <>  Clave: ");
        fflush(stdin);
        gets(cliente.password);
        printf("\n\n\t <>  Nombre: ");
        fflush(stdin);
        gets(cliente.nombre);
        printf("\n\n\t <>  Apellido: ");
        fflush(stdin);
        gets(cliente.apellido);
        printf("\n\n\t <>  Genero M(mujer)-H(hombre): ");
        do
        {
            fflush(stdin);
            scanf("%c", &genero);
            if(genero!='M' && genero!='H')
            {
                mal=1;
                printf("\n\tIngrese correctamente el genero(MAYUSCULA)\n");
            }
            else
            {
                mal=0;
            }
        }
        while(mal==1);
        cliente.genero=genero;
        do
        {
            printf("\n\n\t <>  Mail: ");
            fflush(stdin);
            gets(cliente.mail);
        }
        while (verificarMail(cliente.mail)==0);

        cliente.rol=0;

    }
    cliente.activo=1;
    return cliente;
}
/// pasa estructura de cliente a archivo
void cargarArchivoCliente()
{

    stCliente c;

    FILE * cliente = fopen(archivoClientes, "ab");

    if (cliente ==NULL)
    {

        printf("El archivo no existe!");

    }
    else
    {

        c=CargarCliente();

        fwrite(&c, sizeof(stCliente),1, cliente);

    }
    fclose(cliente);
}


/// cuenta la cantidad de clientes
int cantidadClientes()
{
    stCliente c;
    FILE *archiCliente= fopen(archivoClientes,"rb");
    int cantClientes=-1;

    if(archiCliente!=NULL)
    {
        while(fread(&c, sizeof(stCliente), 1, archiCliente))
        {
            cantClientes++;
        }
    }
    fclose(archiCliente);
    return cantClientes;
}
///rol 1
void listarClientes()
{
    FILE * archiC=NULL;

    archiC=fopen(archivoClientes,"rb");

    stCliente aux;

    if(archiC!=NULL)
    {
        while(fread(&aux,sizeof(stCliente),1,archiC))
        {
            mostrarStructCliente(aux);
        }
    }
    else
    {
        printf("\nERROR\n");
    }
    fclose(archiC);
}


void visualizarPerfil(int id)
{
    FILE * archiC = NULL;

    archiC=fopen(archivoClientes,"rb");

    stCliente c;


    if(archiC!=NULL)
    {
        while(fread(&c,sizeof(stCliente),1,archiC))
        {
            if(id==c.idCliente)
            {
                mostrarStructCliente(c);
            }

        }
    }
    fclose(archiC);
}

void mostrarStructCliente(stCliente c)
{

    puts("\n------------------------------------------------------------\n");
    printf("\n\tID Cliente: %d\n",c.idCliente);
    printf("\n\t    Nombre: %s\n",c.nombre);
    printf("\n\t  Apellido: %s\n",c.apellido);
    printf("\n\t  Username: %s\n",c.userName);
    printf("\n\t      Mail: %s\n",c.mail);
    printf("\n\t    Genero: %c\n",c.genero);
    if(c.activo==0)
    {
        printf("\n\t    Perfil: Inactivo\n");
    }
    else
    {
        printf("\n\t    Perfil: Activo\n");
    }
    if(c.rol==1)
    {
        printf("\n\t       Rol: Administrador\n");
    }
    else
    {
        printf("\n\t       Rol: Cliente\n");
    }

    puts("\n------------------------------------------------------------\n");
}


stCliente modificacion (stCliente c, int id)
{
    int op=0;
    do
    {
        system("color f0");
        menuModificarPerfil();
        puts("\n\tIngrese una opcion...");
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
        {
            system("cls");
            printf("\nIngrese nuevo Nombre:\n");
            fflush(stdin);
            gets(c.nombre);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            printf("\nIngrese nuevo Apellido:\n");
            fflush(stdin);
            gets(c.apellido);
            system("cls");
            break;
        }
        case 3:
        {
            do
            {
                system("cls");
                printf("\nIngrese nuevo Usuario: \n");
                fflush(stdin);
                gets(c.userName);
                system("cls");
            }
            while(verificarUsernameRepetido(c.userName)==1);
            break;
        }
        case 4:
        {
            system("cls");
            printf("\nIngrese nueva Clave:\n");
            fflush(stdin);
            gets(c.password);
            system("cls");
            break;
        }
        case 5:
        {
            do
            {
                system("cls");
                printf("\nIngrese nuevo mail:\n");
                fflush(stdin);
                gets(c.mail);
                system("cls");
            }
            while (verificarMail(c.mail)==0);
            break;
        }
        case 6:
        {
            system("cls");
            printf("\nIngrese nuevo genero:\n");
            fflush(stdin);
            scanf("%c",&c.genero);
            system("cls");
            break;
        }
        case 7:
        {
            system("cls");
            if(id>0)
            {
                if(c.activo==1)
                {
                    c.activo=0;
                    printf("\t\t\nCuenta desactivada en caso de cerrar sesion no podra volver a ingresar\n");
                    system("pause");
                }
                else
                {
                    c.activo=1;
                    printf("\t\t\nCuenta activada.\n");
                    system("pause");
                }
            }
            else
            {
                printf("\nEste usuario no puede darse de baja.\n\n\n");
                system("pause");
            }
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            puts("Regresando... \n");
            break;
        }
        }
    }
    while(op!=0);
    return c;
}


void modificarCliente( int id )
{
    FILE * archiC=fopen(archivoClientes,"r+b");
    fseek(archiC, 0, SEEK_SET);
    stCliente aux;
    stCliente modif;

    int flag=0;

    if(archiC!=NULL)
    {
        //BUSCO CLIENTE
        while(!feof(archiC)&& flag==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archiC)>0)
            {
                if(aux.idCliente==id)
                {
                    flag=1;
                }
            }
        }

        if (flag==1)
        {
            // muevo una posicion hacia atras en el id
            fseek(archiC,(-1)*sizeof(stCliente), SEEK_CUR);
            modif=modificacion(aux,id);
            fwrite(&modif, sizeof(stCliente),1,archiC);

        }
        fclose(archiC);
    }
}


///muestra todos los pedidos
void mostrarPedidos()
{
    stPedido p;
    FILE * archPedido = fopen(archivoPedidos, "rb");
    puts("\n                     -------------------------------------Pedidos------------------------------------------\n");
    if(archPedido!=NULL)
    {
        while(fread(&p, sizeof(stPedido), 1, archPedido))
        {
            mostrarStructPedido(p);
        }
    }
    fclose(archPedido);
}



///rol 1
void cargarArchivoProducto()
{

    stProducto p;

    FILE * producto = fopen(archivoProductos, "ab");

    if (producto ==NULL)
    {

        printf("El archivo no existe!");

    }
    else
    {

        p=CargarProducto();
        fwrite(&p, sizeof(stProducto),1, producto);
    }
    fclose(producto);
}


void modificarPedidoAdmin()
{
    int id=-1,flag=0;
    FILE * archiC=fopen(archivoClientes,"rb");
    fseek(archiC,0,SEEK_SET);
    stCliente c;
    if(archiC!=NULL)
    {
        printf("\nIngrese ID del cliente que desea anular pedido: ");
        scanf("%d",&id);
        while(fread(&c,sizeof(stCliente),1,archiC))
        {
            if(id==c.idCliente)
            {
                flag=1;
            }
        }
    }
    fclose(archiC);
    if (flag==1)
    {
        modificarPedido(id);
    }
    else
    {
        printf("\nEl cliente no existe. \n");
        system("pause");
    }

}

void menuModificarPedidoCliente()
{
    puts("\n\t\t\t\t\t[=================================]");
    puts("\t\t\t\t\t[---------Modificar Pedido--------]\n");
    puts("\t\t\t\t\t[ 1-Cambiar descripcion           ]\n");
    puts("\t\t\t\t\t[ 2-Anular Pedido                 ]\n");
    puts("\t\t\t\t\t[ 0-Regresar                      ]\n");
    puts("\t\t\t\t\t[=================================]\n\n\t");
}

void estadisticaCliente()
{
    FILE *archiP=fopen(archivoPedidos, "rb");
    fseek(archiP, 0,SEEK_SET);
    int idCliente=0, cantPedidos=0, montoTotal=0;
    stPedido p;
    printf("\t \t \n Ingrese la ID del Cliente a analizar:");
    scanf("%i", &idCliente);
    if(archiP!=NULL)
    {
        while(fread(&p,sizeof(stPedido),1,archiP)>0)
        {
            if(idCliente==p.idCliente)
            {
                cantPedidos++;
                montoTotal=montoTotal+p.costo;
            }
        }
        if(cantPedidos>0)
        {
            puts("\t\t\t\t\t[---------Estadisticas Cliente--------]\n");

            printf("\t\t\t\tID Nro: %i\n\n", idCliente);
            printf("\t\t\t\tCantidad de Pedidos Realizados: %i\n\n", cantPedidos);
            printf("\t\t\t\tMonto total gastado: %i\n\n", montoTotal);
            system("pause");
        }
        else
        {
            printf("\t\t\t\n No existen pedidos con el ID ingresado...\n\n");
            system("pause");
        }
        fclose(archiP);
    }

}

void cambiarRolCliente()
{
    FILE * archiC=fopen(archivoClientes,"r+b");
    fseek(archiC, 0, SEEK_SET);
    stCliente aux;
    int idCliente=0, flag=0;
    printf("\t \t \n Ingrese la ID del cliente para cambiar el rol:");
    scanf("%i", &idCliente);
    if (idCliente>0)
    {
        if(archiC!=NULL)
        {
            while(flag==0 && fread(&aux,sizeof(stCliente),1,archiC)>0)
            {
                if(aux.idCliente==idCliente)
                {
                    flag=1;
                }
            }
        }
        if (flag==1)
        {
            if(aux.rol==0)
            {
                printf("\t\t\n El usuario es ahora un ADMINISTRADOR...\n");
                aux.rol=1;
            }
            else
            {
                printf("\t\t\n El usuario es ahora un CLIENTE...\n");
                aux.rol=0;
            }
            fseek(archiC,(-1)*sizeof(stCliente), SEEK_CUR);
            fwrite(&aux, sizeof(stCliente),1,archiC);
            mostrarStructCliente(aux);
        }
        else
        {
            printf("\nNo se encontro usuario con la ID solicitada.\n");
        }
    }
    else
    {
        printf("\t\t\n Este usuario NO se puede modificar...\n");
    }
    getch();
    fclose(archiC);
}

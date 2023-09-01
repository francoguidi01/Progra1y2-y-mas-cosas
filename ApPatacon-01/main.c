#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>      /// Incluye un soporte para amplios tipos de caracteres.
#include <locale.h>     /// Incluye el soporte para distintos tipos de formatos de fecha, moneda, texto, etc.

#define ESC 27

typedef struct                  /// Estructura PEDIDOS.
{
    int idPedido;
    int idCliente;
    char fecha[20];
    char descripcion[300];
    float costo;
    int pedidoAnulado;

} stPedido;

typedef struct              /// Estructura PRODUCTOS.
{
    char producto[100];
    float costo;
    int codProducto;

} stProductos;

typedef struct              /// Estructura CLIENTES.
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

/// ------------------------------      PROTOTIPADO PEDIDOS Y PRODUCTOS.        ------------------------------
void obtenerFecha(char F[],int dimension);
void altaPedido(char R[],char C[],int dimensionFecha,char F[dimensionFecha]);
int mostrarPedido(char R[]);
void abrirArchivo(FILE *A, char rutaArchivoPedidos[], char modo[]);
int ultimoIdPedido(char R[]);
void altaProductos(char P[]);
void mostrarProductos(char P[]);
int ultimoCodProducto (char P[]);
/// ----------------------------------------------------------------------------------------------------------

/// ------------------------------      PROTOTIPADO CLIENTES.        ------------------------------
int registrarse (char R[]);
void iniciarSesion(char C[]);
void mostrarUserRegistro(char R[]);
void asteriscos (char contra[]);

/// ----------------------------------------------------------------------------------------------------------


/// ------------------------------      MENU.        ------------------------------

/// ----------------------------------------------------------------------------------------------------------


int main()
{
    setlocale(LC_ALL, "");


    int menu, numCliente, salir,i=0;

    int dimensionFecha = 80;
    char fecha[dimensionFecha];
    char rutaArchivoPedidos [] = {"archpedidos.dat"};
    char rutaArchivoProductos [] = {"archivoProductos.dat"};
    char rutaArchivoClientes [] = {"archivoDeCliente.dat"};

    do
    {

        printf("\n\t\t\t    ****    MENU    ****\n");
        printf("\n 1. Registrarse.");
        printf("\n 2. Alta de Productos.");
        printf("\n 3. Alta de Pedidos.");
        printf("\n 4. Mostrar de Usuario registrados.");
        printf("\n 5. Mostrar Productos cargados.\n");
        printf("\n 6. Alta de Pedidos.\n");


        printf("\n Ingrese una opcion: ");
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            system("cls");
            printf("\n\t\t\t REGISTRO DE CLIENTES.\n");
            numCliente=registrarse (rutaArchivoClientes);
            printf("\n\nCantidad total de clientes registrados: %d",numCliente);
            break;

        case 2:
            system("cls");
            printf("\n\t\t\t ALTAS DE PRODUCTOS.\n");
            altaProductos(rutaArchivoProductos);
            break;

        case 4:
            system("cls");
            printf("\n\t\t\t MOSTRAR USAURIOS REGISTRADOS.\n");
            mostrarUserRegistro(rutaArchivoClientes);

            break;
        case 5:
            system("cls");
            printf("\n\t\t\t PRODUCTOS CARGADOS EN SISTEMA.\n");
            mostrarProductos(rutaArchivoProductos);
            break;
        case 6:
            system("cls");
            printf("\n\t\t\t ALTA DE PEDIDOS.\n");
            altaPedido(rutaArchivoPedidos,rutaArchivoClientes,dimensionFecha,fecha);
        case 7:
            system("cls");
            printf("\n\t\t\t INICIO DE SESION.\n");
          //  iniciarSesion(rutaArchivoClientes);
            break;
        }

        printf("\n\t\t\t ESC para salir. Cualquier tecla para continuar.");
        printf("\n\t\t\t Desea continuar?.  ");
        salir=getch();
        system("cls");
    }
    while(salir!=ESC);


    return 0;
}

///         *****************       FUNCIONES       *****************
int registrarse (char R[])
{
    int i=0;
    //char contra[]="NULL";
    setlocale(LC_ALL, "");
    stCliente cl;

    FILE *archivoDeCliente = fopen(R,"ab");

    if(archivoDeCliente!= NULL)
    {

        cl.idCliente=i+1;                               ///     REPLANTEAR EL IdCLIENTE PORQUE NO FUNCIONA.!!!!!!!!!!!!!!!!!!
        cl.activo=1;

        printf("\nIngrese su nombre: ");
        fflush(stdin);
        gets(cl.nombre);
        printf("\nIngrese su apellido: ");
        fflush(stdin);
        gets(cl.apellido);
        printf("\nIngrese su nombre se usuario: ");
        fflush(stdin);
        gets(cl.userName);
        printf("\nIngrese su genero (M/F/O): ");
        fflush(stdin);
        scanf("%c",&cl.genero);
        printf("\nIngrese su email: ");
        fflush(stdin);
        gets(cl.mail);
        printf("\nIngrese su contraseña (No mas de 10 caracteres): ");
        fflush(stdin);
        asteriscos(cl.password);

        fwrite(&cl,sizeof(stCliente),1,archivoDeCliente);
        i++;
    }
    fclose(archivoDeCliente);
    return i;
}
//int iniciarSesion(char C[])
//{
//    setlocale(LC_ALL, "");
//    int i=0;
//    char nombreUsuario []="NULL";
//    char password []="NULL";
//
//    stCliente cl;
//
//    int flag=0;      /// NOS QUEDAMOS ACA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  VER CAPTURA DE IMAGEN EN DC
//    int flag1="NULL";
//    int flag2="NULL";

///system("cls"); con esto no se muestra los usuarios ponerlo despues.///

//    printf("\nPor favor ingrese su usuario y contraseña\n");
//
//    FILE *archivoDeCliente = fopen(C,"rb");
//
//
//
//    if(archivoDeCliente!= NULL)
//    {
//       while(!feof(archivoDeCliente) && flag)
//            do
//            {
//                printf("\nUsuario: ");
//                fflush(stdin);
//                gets(&nombreUsuario); //scanf("%s", &nombreUsuario);
//                flag1=strcmp(cl.userName,nombreUsuario);  //flag=compararUsuarios(cliente,validos, nombreUsuario);
//
//
//                usuarioNoExistente(flag);
//
//                i=compararUsuariosRetrnoI(cliente,validos,nombreUsuario);
//
//            }
//            while (flag!=1);
//
//
//            do
//            {
//                printf("\nIngrese Contraseña(No mas de 10 caracteres): ");
//                fflush(stdin);
//                asteriscos(&password);
//                flag2=strcmp(cl.password,&password);//flag2=compararPassword(cliente,password,i);
//                //passwordIncorrecta(flag2);
//                if (flag2==1)
//                {
//                    printf("\nContraseña incorrecta, por favor vuelva a intentarlo\n");
//
//                }
//
//            }
//            while (flag2==1);
//
//            system("cls");
//            if(flag2==0)
//            {
//                printf("\nUsted inicio sesion correctamente.");
//                while(strcmp(cl.userName,nombreUsuario)==0)
//                {
//                    a=cl.idCliente;
//                }
//
//            }
//        }
//        fclose(archivoDeCliente);
//
//
//        return a;
//    }

    void mostrarUserRegistro(char R[])
    {
        stCliente cl;

        FILE *archivoDeCliente = fopen(R,"rb");

        printf("\n\t\tCLIENTES REGISTRADOS .....\n");

        printf("\t\t ========================== \n");

        if(archivoDeCliente!= NULL)
        {
            while(fread(&cl,sizeof(stCliente),1,archivoDeCliente)>0)
            {

                printf("IdCliente: %d \n",cl.idCliente);
                printf("NOMBRE: %s \n",cl.nombre);
                printf("APELLIDO: %s \n",cl.apellido);
                printf("UserName: %s \n",cl.userName);
                printf("pass: %s \n",cl.password);
                printf("EMAIL: %s \n",cl.mail);
                printf("GENERO: %c \n",cl.genero);
                printf("ROL: %d \n",cl.rol);
                printf("ACTIVO: %d \n",cl.activo);
                printf("\n ========================== \n");
            }
        }

        printf("\nFIN DE CLIENTES REGISTRADOS....\n");
        fclose(archivoDeCliente);

    }
    void asteriscos (char contra[])
    {
        char caracter;
        int x=0;
        do
        {
            caracter=getch();
            if(caracter==13)
            {
                contra [x]='\0';

            }
            else if(caracter==8)
            {
                if(x>0)
                {
                    x--;
                    printf("\b \b");
                }
            }
            else if (x<10)
            {
                printf("*");
                contra[x]=caracter;
                x++;
            }
        }
        while(caracter!=13);



    }

    void altaProductos(char P[])
    {
        char control = 's';
        int codProducto;
        stProductos a;

        FILE *archivoProductos = fopen(P,"ab");

        codProducto = ultimoCodProducto (P);
        if(archivoProductos != NULL)
        {
            while(control == 's')
            {
                a.codProducto=  codProducto + 1;
                printf("Ingrese el producto a agregar: \n");
                fflush(stdin);
                gets (a.producto);

                printf("Ingrese el costo del producto: \n");
                scanf("%f",&a.costo);

                printf("< --- CARGAR OTRO PRODUCTO? --- >  S/N\n");
                control = getch();


                fwrite(&a,sizeof(stProductos),1,archivoProductos);
                system("cls");

            }

            fclose(archivoProductos);
        }

    }
    int ultimoCodProducto (char P[])
    {
        int a;
        stProductos pr;

        FILE *archivoProductos = fopen(P,"r");

        if(archivoProductos != NULL)
        {

            while(fread(&pr,sizeof(stProductos),1,archivoProductos)>0)
            {
                a = pr.codProducto;
            }

        }

        fclose(archivoProductos);

        return a;


    }
    void mostrarProductos(char P[])
    {
        stProductos a;

        FILE *archivoProductos = fopen(P,"r");


        if(archivoProductos != NULL)
        {

            printf("INICIANDO MUESTREO DE PRODUCTOS .....\n");

            printf(" ========================== \n");

            while(fread(&a,sizeof(stProductos),1,archivoProductos) > 0)
            {
                printf("DESCRIPCION: %s \n",a.producto);
                printf("COSTO: %.2f \n",a.costo);

                printf(" ========================== \n");
            }

            printf("FINALIZANDO MUESTREO DE PRODUCTOS....\n");
        }
        else
        {
            printf("ERROR AL LISTAR LOS PRODUCTOS: ERROR \"ARCHIVO PRODUCTOS VACIO\" \n");
        }

        fclose(archivoProductos);

    }





//
//
//
//
//
//
///     ------------------     OBTENER FECHA.    ------------------
    void  obtenerFecha(char F[],int dimension)
    {
        time_t t;
        struct tm *tm;

        t = time(NULL);
        tm = localtime(&t);
        strftime(F,dimension,"%d-%m-%Y %I:%M%p",tm);

    }
///     ------------------      ALTA DE PEDIDOS.    ------------------
    void altaPedido(char R[],char C[],int dimensionFecha,char F[dimensionFecha])
    {
        char control = 's';
        int ultimoNumPedido;
        stPedido a;


        FILE *archpedidos = fopen(R,"ab");
//    FILE *archivoDeCliente = fopen(C,"r");


        ultimoNumPedido = ultimoIdPedido(R);
        obtenerFecha(F,dimensionFecha);


        printf("|^_^| --- ALTA DE PEDIDO --- |^_^|\n\n");

        if(archpedidos != NULL)
        {


            while(control == 's')
            {
                //Numero de pedido y cliente estan asi para probar,
                // despues esto viene desde el archivo de los chicos.

                a.idPedido =  ultimoNumPedido + 1;
                printf("< --- NUMERO DE PEDIDO --- >\n %d",a.idPedido);


                printf("\n");

                printf("< --- NUMERO DE CLIENTE ---> \n");
                scanf("%d",&a.idCliente);

                printf("\n");

                printf("< --- FECHA ACTUAL --- > \n");
                strcpy(a.fecha,F);
                printf("%s \n",a.fecha);

                printf("\n");

                printf("< --- DESCRIPCION --- > \n");
                fflush(stdin);
                gets(a.descripcion);

                printf("\n");

                printf("< --- COSTO --- >  \n");
                scanf("%f",&a.costo);

                printf("\n");

                printf("< --- PEDIDO ANULADO? --- > \n");
                scanf("%d",&a.pedidoAnulado);

                fwrite(&a,sizeof(stPedido),1,archpedidos);

                printf("\n");

                printf("< --- CARGAR OTRO PEDIDO? --- >  S/N\n");
                control = getch();

                system("cls");



            }

            fclose(archpedidos);

        }

    }
///     ------------------      MOSTRAR PEDIDOS.    ------------------

    int ultimoIdPedido (char R[])
    {
        int a;
        stPedido l;


        FILE *archpedidos = fopen(R,"r");


        if(archpedidos != NULL)
        {

            while(fread(&l,sizeof(stPedido),1,archpedidos)>0)
            {
                a = l.idPedido;
            }

        }

        fclose(archpedidos);

        return a;


    }

//
//int posicionBusquedaIdPedido(char P[],int idBuscado)
//{
//    int i = -1;
//    stPedido p;
//    printf("%d \n",idBuscado);
//
//    FILE *archpedidos = fopen(P,"r");
//
//    if(archpedidos != NULL)
//    {
//
//        while(! feof(archpedidos) && p.idPedido != idBuscado)
//        {
//            fread(&p,sizeof(stPedido),1,archpedidos);
//            i++;
//
//        }
//
//        if(feof(archpedidos) != 0)
//        {
//            printf("NO SE ENCONTRO COINCIDENCIAS \n");
//        }
//
//        else
//        {
//            printf("SE ENCONTRO COINCIDENCIA EN LA POSICION %d \n",i);
//        }
//    }
//
//    fclose(archpedidos);
//
//    return i;
//}


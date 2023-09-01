#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>      /// Incluye un soporte para amplios tipos de caracteres.
#include <locale.h>     /// Incluye el soporte para distintos tipos de formatos de fecha, moneda, texto, etc.
#include <windows.h>

#define ESC 27
#define ENTER 13
#define FLECHAARRIBA 72
#define FLECHAABAJO 80
#define ARROBA 64

typedef struct                /// Estructura PEDIDOS.
{

    int pedidoAnulado;
    int idPedido;
    int idCliente;
    int codProducto;
    int cantidad;
    char producto[100];
    char fecha[12];
    char descripcion[300];
    float costoPedido;
    float costoFinal;
} stPedido;

typedef struct              /// Estructura PRODUCTOS.
{
    int codProducto;
    char producto[100];
    float costo;

} stProductos;

typedef struct              /// Estructura CLIENTES.
{
    int idCliente;
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[100];
    char genero;
    int rol;
    int activo;

} stCliente;
/// ------------------------------      PROTOTIPADO SISTEMA.        ------------------------------
void menuNavegable (int menu,int menuinicio,int menufin, int lineainicio, int opcion, char c[],char p [], char r []);
int flechas (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAlta (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaPedido (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuUsuario (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuAdmin (int menu,int menuinicio,int menufin, int lineainicio);
void mailInvalido (int flag);
void saltoDeLinea (int lineas);
int verificarSiEstaActivo (char C[],int idUser);
void noExiste (int flag, int idUserExterno);
void gotoxy (int x, int y);
int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio);
int darDeBajaUnUser (char nombreArchivo[],int idUser);
/// ----------------------------------------------------------------------------------------------------------

/// ------------------------------      PROTOTIPADO PEDIDOS Y PRODUCTOS.        ------------------------------
void obtenerFecha(char F[],int dimension);
void altaPedido(char R[],char C[],char P[],int idUser,char F[],int dimensionFecha);
void abrirArchivo(FILE *A, char rutaArchivoPedidos[], char modo[]);
int ultimoIdPedido(char R[]);
void altaProductos(char P[]);
void mostrarProductos(char P[]);
int ultimoCodProducto (char P[]);
void buscarPedidosIdClienteAdmin(char R[],char C[]);
void mostrarPedidoAdmin(char R[]);
float obtenerCosto(char P[],int seleccion);
float seleccionarProductos(char P[]);
int noExistePedido (int flag, int idPedidoExterno);
/// ----------------------------------------------------------------------------------------------------------

/// ------------------------------      PROTOTIPADO CLIENTES.        ------------------------------
int registrarse (char C[]);
int iniciarSesion(char C[]);
void mostrarUserRegistro(char R[]);
void asteriscos (char contra[]);
int buscaIdCliente (char C[],char usuario[]);
int compararPassword (char C[], char password[]);
int compararUsuarios (char C[],char usuario[]);
int ultimoIdCliente (char C[]);
void usuarioRepetido (int flag);
int verificacionEmail (char email[]);

/// ----------------------------------------------------------------------------------------------------------

/// ------------------------------      MENU.        ------------------------------



int main()
{
    ///  cliente es C
    /// pedidos es R
    /// productos es p
    setlocale(LC_ALL, "");


   // int menu, numCliente, salir,idUser;

   // int dimensionFecha = 80;
   // char fecha[dimensionFecha];
    char rutaArchivoPedidos [] = {"archpedidos.dat"};
    char rutaArchivoProductos [] = {"archivoProductos.dat"};
    char rutaArchivoClientes [] = {"archivoDeCliente.dat"};

    int menuy=0,menuinicioy=0,menufiny=0,lineainicioy=0, opciony=0;

    menuNavegable(menuy,menuinicioy,menufiny,lineainicioy,opciony,rutaArchivoClientes,rutaArchivoProductos,rutaArchivoPedidos);

    return 0;
}

///         *****************       FUNCIONES       *****************
int registrarse(char C[])
{
    setlocale(LC_ALL, "");

    int i=0, flag=0, flag2=0;
    int idCliente;
    char nombreUsuario [20];
    char mailcopy [100];
    stCliente cl;

    FILE *archivoDeCliente = fopen(C,"ab");

    idCliente = ultimoIdCliente(C);
    cl.idCliente = idCliente + 1;
    cl.rol = 0;

    if(archivoDeCliente!= NULL)
    {
        printf("\n\t\t\tIngrese su nombre: ");
        fflush(stdin);
        gets(cl.nombre);

        printf("\n\t\t\tIngrese su apellido: ");
        fflush(stdin);
        gets(cl.apellido);

        do
        {
            printf("\n\t\t\tIngrese su nombre se usuario: ");
            fflush(stdin);
            scanf("%s", &nombreUsuario); /// ?????
            flag=compararUsuarios(C,nombreUsuario);
            usuarioRepetido(flag);
        }
        while (flag!=0);
        strcpy(cl.userName, nombreUsuario);

        printf("\n\t\t\tIngrese su genero (Solo inicial): ");
        fflush(stdin);
        scanf("%c",&cl.genero);
        do
        {
            printf("\n\t\t\tIngrese su email: ");
            fflush(stdin);
            gets(mailcopy);
            flag2=verificacionEmail(mailcopy);                  ///Esto funciona a la inversa de la funcion comparar usuarios
            mailInvalido(flag2);                              ///porque en este tiene que encontralo y en la funcion comparar no.
        }
        while(flag2==0);

        strcpy(cl.mail, mailcopy);

        printf("\n\t\t\tIngrese su contraseña (No mas de 10 caracteres): ");
        fflush(stdin);
        asteriscos(cl.password);

        cl.activo = 1;

        fwrite(&cl,sizeof(stCliente),1,archivoDeCliente);
        i++;
    }
    fclose(archivoDeCliente);
    system("cls");
    saltoDeLinea(3);
    printf("\t\t\t\t====== Usted se ha registrado exitosamente ======");
    saltoDeLinea(2);
    printf("\t\t\t\tPor favor. ");
    system("pause");
    return i;
}

int iniciarSesion(char C[])
{
    setlocale(LC_ALL, "");
    int idUser=0,flag1=0,flag2=0, intentos=0;
    char nombreUsuario []="NULL", password []="NULL";
    printf("\n\t\t\t\t =====Por favor ingrese su usuario y contraseña=====");

    do
    {
        printf("\n\n\t\t\t Usuario: ");
        fflush(stdin);
        gets(nombreUsuario);

        flag1=compararUsuarios(C,nombreUsuario);

        if(flag1==1)
        {
            idUser=buscaIdCliente (C,nombreUsuario);
        }
        else
        {
            system("cls");
            printf("\n\t\t\t =====Usuario inexistente. Intentelo nuevamente.=====");
        }
    }
    while (flag1!=1);

    do
    {
        printf("\n\n\t\t\t Contraseña: ");
        fflush(stdin);
        asteriscos(password);
        flag2=compararPassword (C,password);
        if (flag2==0)
        {
            system("cls");
            printf("\n\t\t\t =====Contraseña incorrecta, por favor vuelva a intentarlo=====");
        }
        idUser=verificarSiEstaActivo(C,idUser);
        intentos++;

        if (intentos==3)
        {
            system("cls");
            printf("\n\t\t\t Has sobrepasado el limite de intentos. ");
            system("\t\t\t pause");
            idUser=0;
        }

    }
    while (flag2==0 && intentos!=3 && idUser!=0);

    return idUser;
}

int compararproductos (char p[],int producto)
{
    int flag=0;
    stProductos pr;
    FILE *archivoDeCliente = fopen(p,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&pr, sizeof (stProductos), 1, archivoDeCliente) > 0)
        {
            if (pr.codProducto==producto)
            {
                flag=1;
            }
        }

    }
    fclose(archivoDeCliente);
    return flag;
}

int compararUsuarios (char C[],char usuario[])
{
    int flag=0;
    stCliente cl;
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (strcmp (cl.userName, usuario) == 0)
            {
                flag=1;
            }
        }

    }
    fclose(archivoDeCliente);
    return flag;
}

void modificarPassword(char c[],int idUserExterno)
{
    FILE*archi=fopen(c,"r+b");
    stCliente aux;
    char nuevoPassword[30];
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUserExterno)
                {
                    flag=1;
                }
            }
        }
    }

    if(flag ==1)
    {
        printf("\n\t\t\tIntroduzca su nuevo password:  ");
        fflush(stdin);
        asteriscos(nuevoPassword);
        strcpy(aux.password, nuevoPassword);
        fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
        fwrite(&aux,sizeof(stCliente),1,archi);

    }

    noExiste(flag, idUserExterno);

    fclose(archi);
}

void modificarEmail(char c[],int idUserExterno)
{
    FILE*archi=fopen(c,"r+b");
    stCliente aux;
    char nuevoEmail[100];
    int flag=0;
    int flag2=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUserExterno)
                {
                    flag=1;
                }
            }
        }
    }

    if(flag ==1)
    {
        do
        {
            printf("\n\t\t\tIntroduzca su nuevo email:  ");
            fflush(stdin);
            gets(nuevoEmail);
            flag2=verificacionEmail(nuevoEmail);
            mailInvalido(flag2);
        }
        while(flag2==0);

        strcpy(aux.mail, nuevoEmail);

        fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
        fwrite(&aux,sizeof(stCliente),1,archi);

    }

    noExiste(flag, idUserExterno);

    fclose(archi);
}

void modificarApellido(char c[],int idUserExterno)
{
    FILE*archi=fopen(c,"r+b");
    stCliente aux;
    char nuevoApellido[30];
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUserExterno)
                {
                    flag=1;
                }
            }
        }
    }
    if(flag ==1)
    {
        printf("\n\t\t\tIntroduzca su nuevo apellido:  ");
        fflush(stdin);
        gets(nuevoApellido);
        strcpy(aux.apellido,nuevoApellido);
        fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
        fwrite(&aux,sizeof(stCliente),1,archi);

    }
    noExiste (flag, idUserExterno);

    fclose(archi);
}

void modificarNombre(char c[],int idUserExterno)
{
    FILE*archi=fopen(c,"r+b");
    stCliente aux;
    char nuevoNombre[30];
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUserExterno)
                {
                    flag=1;
                }
            }
        }
    }
    if(flag ==1)
    {
        printf("\n\t\t\tIntroduzca su nuevo nombre:  ");
        fflush(stdin);
        gets(nuevoNombre);
        strcpy(aux.nombre,nuevoNombre);
        fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
        fwrite(&aux,sizeof(stCliente),1,archi);

    }
    noExiste (flag, idUserExterno);

    fclose(archi);
}

int verificacionEmail (char email[])
{

    int flag=0;
    int i=0;
   // char string [10]= {"@"};

    if (i= strchr (email, 64) != 0)
    {
        flag=1;
    }
    return flag;
}

void mailInvalido (int flag)
{
    if (flag==0)
    {
        system("cls");
        printf("\n\t\t\t=====Email invalido, por favor vuelva a intentarlo=====");

    }
}

void productoInvalido (int flag)
{

    if (flag==0)
    {
        printf("\n\t\t\t Producto invalido. Por favor ");
        system("pause");
    }
}

void usuarioRepetido (int flag)
{

    if (flag==1)
    {
        system("cls");
        printf("\n\t\t\t=====Usuario ya registrado, por favor vuelva a intentarlo=====");

    }
}

int noExistePedido (int flag, int idPedidoExterno)
{
    if (flag!=1)
    {
        system("cls");
        saltoDeLinea(5);
        printf("\n\t\t\t\t\tNo existe el numero de pedido: %d. ", idPedidoExterno);
        saltoDeLinea(3);
        system("pause");
    }
    return flag;
}

void noExiste (int flag, int idUserExterno)
{
    if (flag!=1)
    {
        system("cls");
        printf("\n\t\t\tNo existe el ID de usuario: %d. ", idUserExterno);
        system("pause");
    }
}

void saltoDeEspacio (int lineas)
{
    for (int i=0; i<lineas; i++)
    {
        printf("\t");
    }
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

int compararPassword (char C[], char password[])
{
    int flag=0;
    stCliente cl;
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (strcmp (cl.password, password) == 0)
            {
                flag=1;
            }
        }

    }
    fclose(archivoDeCliente);
    return flag;
}

int buscaRolCliente (char C[],int idUser)
{
    int userRol=0;
    stCliente cl;
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (cl.idCliente==idUser)
            {
                userRol=cl.rol;
            }
        }

    }
    fclose(archivoDeCliente);
    return userRol;
}

int buscaIdCliente (char C[],char usuario[])
{
    int idUser;
    stCliente cl;
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (strcmp (cl.userName, usuario) == 0)
            {
                idUser=cl.idCliente;
            }
        }

    }
    fclose(archivoDeCliente);
    return idUser;
}

int verificarSiEstaActivo (char C[],int idUser)
{
    stCliente cl;
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (cl.idCliente==idUser)
            {
                if (cl.activo==1)
                {
                    idUser=cl.idCliente;
                }

                else
                {
                    printf("\n\n\t\t=====Este usuario ya no se encuentra activo.Si desea activarlo comuniquese al 0800-428-7627===== \n\n\t\t\t\t\tPor favor, ");
                    system("pause");
                    idUser=0;
                }
            }
        }

    }
    fclose(archivoDeCliente);
    return idUser;
}

int verificarPedido (char nombreArchivo[],int idPedidoExterno)
{
    FILE*archi=fopen(nombreArchivo,"r+b");
    stPedido aux;
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stPedido),1,archi)>0)
            {
                if(aux.idPedido == idPedidoExterno)
                {
                    if (aux.pedidoAnulado==1)
                    {
                        flag=0;
                    }

                    else
                    {
                        system("cls");
                        saltoDeEspacio(5);
                        printf("\n\t\t Este Pedido ya fue dado de baja Anteriormente. Por favor, ");
                        system("pause");
                        flag=1;
                    }
                }
            }
        }
    }
    fclose(archi);
    return flag;
}

void mostrarUnUserRegistro(char C[],int idUser)
{
    stCliente cl;

    FILE *archivoDeCliente = fopen(C,"rb");

    printf("\n\t\t\t ==========================TUS DATOS==========================\n");

    if(archivoDeCliente!= NULL)
    {
        while ( fread (&cl, sizeof (stCliente), 1, archivoDeCliente) > 0)
        {
            if (cl.idCliente==idUser)
            {
                printf("\n\t\t\t IdCliente: %d \n",cl.idCliente);
                printf("\n\t\t\t Nombre: %s \n",cl.nombre);
                printf("\n\t\t\t Apellido: %s \n",cl.apellido);
                printf("\n\t\t\t UserName: %s \n",cl.userName);
                printf("\n\t\t\t Contraseña: %s \n",cl.password);
                printf("\n\t\t\t Email: %s \n",cl.mail);
                printf("\n\t\t\t Genero: %c \n",cl.genero);
                printf("\n\t\t\t ============================================================== \n");
                printf("\t\t\t\t\t");
                system("pause");
            }
        }
    }
    fclose(archivoDeCliente);
}

void mostrarUnUserPedidos(char R[],int idUser)
{
    stPedido cl;

    FILE *archivoDePedidos = fopen(R,"rb");
    int comparar=0, comparar2=0;
    int i=0;

    if(archivoDePedidos!= NULL)
    {

        while(fread(&cl,sizeof(stPedido),1,archivoDePedidos)>0)
        {
            if (cl.idCliente==idUser && cl.pedidoAnulado == 1)
            {

                if(comparar != cl.idPedido)
                {
                    saltoDeLinea(2);
                    printf("\n\t\t\t================================= PEDIDO N°: %d ================================", cl.idPedido);
                    saltoDeLinea(1);
                    printf("\t\t\t FECHA: %s ",cl.fecha);
                    if(cl.pedidoAnulado==1)
                    {
                        printf("\t\t\t\t\t PEDIDO APROBADO \n");
                        printf("\t\t\t==================================================================================");
                        i++;
                    }
                    else if (cl.pedidoAnulado==0)
                    {
                        printf("\t\t\t\t\t PEDIDO ANULADO \n");
                        printf("\t\t\t==================================================================================");
                    }
                    else
                    {
                        saltoDeLinea(1);
                        printf("\t\t\t ERROR EN EL SISTEMA POR FAVOR CIERRE SESION Y COMUNIQUESE AL 0800-428-7627 \n");
                    }
                }
                printf("\n\t\t\t PRODUCTO \t\tCANTIDAD \t\t\t\t\t IMPORTE");
                saltoDeLinea(1);
                printf("\n\t\t\t %s ",cl.producto);
                printf("\t\t\t %d ",cl.cantidad);
                printf("\t\t\t\t\t %0.2f",cl.costoPedido);
                saltoDeLinea(1);
                if(comparar2==cl.idPedido)
                {
                    printf("\n\n\t\t\t\t\t\t\t\t\t COSTO TOTAL DEL PEDIDO: %0.2f ",cl.costoFinal);
                    printf("\n\t\t\t==================================================================================");
                }
            }

            if(comparar2!=cl.idPedido)
            {
                comparar2=cl.idPedido;

            }
            else if(comparar2==cl.idPedido)
            {
                comparar2=0;
            }
            comparar=cl.idPedido;
        }



        if(i==0)
        {
            saltoDeLinea(3);
            printf("\n\t\t\t==================USTED NO TIENE PEDIDO HECHOS==================");
            saltoDeLinea(3);
        }
    }
    fclose(archivoDePedidos);
}

void mostrarUnUserPedidosAdmin (char R[],int idUserExterno)
{
    stPedido cl;

    FILE *archivoDePedidos = fopen(R,"rb");

    int comparar=0;
    int comparar2=0;
    int i=0;

    if(archivoDePedidos!= NULL)
    {
        while(fread(&cl,sizeof(stPedido),1,archivoDePedidos)>0 && idUserExterno==cl.idCliente)
        {
            if (cl.idCliente==idUserExterno)
            {
                if(comparar != cl.idPedido)
                {
                    saltoDeLinea(2);
                    printf("\n\t\t\t================================= PEDIDO N°: %d ================================", cl.idPedido);
                    saltoDeLinea(1);
                    printf("\t\t\t FECHA: %s ",cl.fecha);
                    if(cl.pedidoAnulado==1)
                    {
                        printf("\t\t\t\t\t PEDIDO APROBADO \n");
                        printf("\t\t\t==================================================================================");
                        i++;
                    }
                    else if (cl.pedidoAnulado==0)
                    {
                        printf("\t\t\t\t\t PEDIDO ANULADO \n");
                        printf("\t\t\t==================================================================================");
                    }
                    else
                    {
                        saltoDeLinea(1);
                        printf("\t\t\t ERROR EN EL SISTEMA POR FAVOR CIERRE SESION Y COMUNIQUESE AL 0800-428-7627 \n");
                    }
                }
                printf("\n\t\t\t PRODUCTO \t\tCANTIDAD \t\t\t\t\t IMPORTE");
                saltoDeLinea(1);
                printf("\n\t\t\t %s ",cl.producto);
                printf("\t\t\t %d ",cl.cantidad);
                printf("\t\t\t\t\t %0.2f",cl.costoPedido);
                saltoDeLinea(1);
                if(comparar2==cl.idPedido)
                {
                    printf("\n\n\t\t\t\t\t\t\t\t\t COSTO TOTAL DEL PEDIDO: %0.2f ",cl.costoFinal);
                    printf("\n\t\t\t==================================================================================");
                }
            }

            if(comparar2!=cl.idPedido)
            {
                comparar2=cl.idPedido;

            }
            else if(comparar2==cl.idPedido)
            {
                comparar2=0;
            }
            comparar=cl.idPedido;
        }

    }
    fclose(archivoDePedidos);
}


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

    codProducto = ultimoCodProducto(P);
    a.codProducto = codProducto + 1;
    do
    {

        printf("CODIGO DE PRODUCTO: %d \n",a.codProducto);

        printf("INGRESE EL PRODUCTO A AGREGAR: \n");
        fflush(stdin);
        gets(a.producto);

        printf("INGRESE EL PRECIO DEL PRODUCTO: \n");
        scanf("%f",&a.costo);

        fwrite(&a,sizeof(stProductos),1,archivoProductos);

        a.codProducto ++;

        printf("< --- CARGAR OTRO PRODUCTO? --- >  S/N\n");
        fflush(stdin);
        control = getch();

        system("cls");

    }
    while(control == 's');




    fclose(archivoProductos);

}
int ultimoCodProducto(char P[])
{
    int a = 0;
    stProductos pr;

    FILE *archivoProductos = fopen(P,"rb");

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

    FILE *archivoProductos = fopen(P,"rb");

    if(archivoProductos != NULL)
    {
        gotoxy(34,2);
        printf("=============   LISTA DE PRODUCTOS  =============");
        gotoxy(9,3);
        printf("========================================================================================================");

        while(fread(&a,sizeof(stProductos),1,archivoProductos) > 0)
        {
            printf("\n\t CODIGO: %d \n",a.codProducto);
            printf("\n\t PRODUCTO: %s \n",a.producto);
            printf("\n\t PRECIO: %.2f \n",a.costo);

            printf("\n\t ========================== \n");
        }

    }
    else
    {
        printf("\n\t ERROR AL LISTAR LOS PRODUCTOS: ERROR \"ARCHIVO PRODUCTOS VACIO\" \n");
    }

    fclose(archivoProductos);

}

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
void altaPedido(char pD[],char pR[],char C[],int idUser,char F[],int dimensionFecha)
{
    char control = 's';
    char nomUser[30];
    int ultimoPedido,codProd=0,pdCant=0,flag=0;
    float costo=0, calc=0,acumulador=0;

    stCliente cl;
    stPedido pd;
    stProductos pr;

    FILE *archivoDeCliente = fopen(C,"rb");

    if (archivoDeCliente!=NULL)
    {
        while(fread(&cl,sizeof(stCliente),1,archivoDeCliente)>0)
        {
            if(cl.idCliente == idUser)
            {
                strcpy(nomUser,cl.userName);
            }
        }
    }

    ultimoPedido=ultimoIdPedido (pD);
    pd.idPedido =  ultimoPedido + 1;

    pd.idCliente=idUser;
    obtenerFecha(F,dimensionFecha);
    strcpy(pd.fecha,F);

    FILE *archivoPedidos = fopen(pD,"ab");

    if(archivoPedidos != NULL)
    {

        FILE *archivoProductos = fopen(pR,"rb");
        do
        {
            do
            {
                system("cls");
                mostrarProductos(pR);
                printf("\n\t\t\t\t *SELECCIONE EL CODIGO DEL PRODUCTO: ");
                scanf("%d",&codProd);
                flag=compararproductos(pR,codProd);
                productoInvalido(flag);
            }
            while(flag==0);

            rewind(archivoProductos);

            while(fread(&pr,sizeof(stProductos),1,archivoProductos) > 0)
            {
                if(codProd==pr.codProducto)
                {
                    strcpy(pd.producto, pr.producto);
                    costo = pr.costo;
                }
            }

            printf("\n\t\t\t\t *INGRESE LA CANTIDAD DE UNIDADES A COMPRAR: ");
            scanf("%d",&pdCant);
            pd.cantidad=pdCant;
            calc = (costo * pdCant);

            acumulador =  acumulador + calc;
            printf("\n\t\t\t\t *USTED VA GASTANDO: %0.2f",acumulador);
            pd.costoPedido=calc;
            pd.costoFinal=acumulador;

            saltoDeLinea(1);

            printf("\n\t\t\t\t *DESEA AGREGAR MAS PRODUCTOS AL CARRO? (S/N): ");
            fflush(stdin);
            control = getch();

            saltoDeLinea(1);

            printf("\n\t\t\t\t *EL VALOR FINAL DEL PEDIDO ES: %0.2f ",pd.costoFinal);
            pd.pedidoAnulado=1;
            fwrite(&pd,sizeof(stPedido),1,archivoPedidos);

        }
        while(control != 'n');

        saltoDeLinea(1);
        printf("\n\t\t\t Pedido concluido. Por favor ");
        system("pause");

        pd.idPedido++;
        fclose(archivoPedidos);
        fclose(archivoDeCliente);
    }
}

int menuConfiguracionDeUsuario (char c[], int idUser)
{
    int eleccion=0, flagVolver=0;
    system("cls");
    eleccion=sistemanavegableConfiguracionUsuario(1,1,7,1);
    switch (eleccion)
    {
    case 1:
        system("cls");
        modificarNombre(c,idUser);
        break;

    case 2:
        system("cls");
        modificarApellido(c,idUser);
        break;
    case 3:
        system("cls");
        modificarEmail(c,idUser);
        break;
    case 4:
        system("cls");
        modificarPassword(c,idUser);
        break;
    case 5:
        system("cls");
        flagVolver=darDeBajaUnUser(c,idUser);
        if (flagVolver==2)
        {
            mensajeDespedida();
        }
        break;
    case 6:
        system("cls");
        mostrarUnUserRegistro(c,idUser);
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

int darDeBajaODarDeAlta (char nombreArchivo[],int idUserExterno)
{
    FILE*archi=fopen(nombreArchivo,"r+b");
    stCliente aux;
    int flag=0;
    int flag2=0;
    int flagAPasar=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUserExterno)
                {
                    flag=1;
                }
            }
        }
    }

    if (flag==1)
    {
        flag2=sistemanavegableMenuBajaAlta(1,1,3,1);

        if(flag2==1)
        {
            if (aux.activo==1)
            {
                aux.activo=0;
                fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
                fwrite(&aux,sizeof(stCliente),1,archi);
            }
            else
            {
                system("cls");
                printf("\n\t\t\t Este usuario ya esta dado de baja. ");
                system("pause");
            }
        }
        if(flag2==2)
        {
            if (aux.activo==0)
            {
                aux.activo=1;
                fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
                fwrite(&aux,sizeof(stCliente),1,archi);
            }
            else
            {
                system("cls");
                printf("\n\t\t\t Este usuario ya esta dado de alta. ");
                system("pause");
            }
        }
        if(flag2==3)
        {
            flagAPasar=0;
        }
        fclose(archi);
    }
    noExiste(flag, idUserExterno);

    return flagAPasar;
}

int darDeBajaUnUser (char nombreArchivo[],int idUser)
{
    FILE*archi=fopen(nombreArchivo,"r+b");
    stCliente aux;
    int flag=0;
    int flag2=0;
    int flagAPasar=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stCliente),1,archi)>0)
            {
                if(aux.idCliente == idUser)
                {
                    flag=1;
                }
            }
        }
    }

    if (flag==1)
    {
        flag2=sistemanavegableMenuBajaAltaUnUser(1,1,2,3);

        if(flag2==1)
        {
            if (aux.activo==1)
            {
                aux.activo=0;
                fseek(archi, -1*sizeof(stCliente),SEEK_CUR);
                fwrite(&aux,sizeof(stCliente),1,archi);
                flagAPasar=2;
            }
            else
            {
                system("cls");
                printf("\n\t\t\t Este usuario ya esta dado de baja. ");
                system("pause");
            }
        }
    }
    noExiste(flag, idUser);
    fclose(archi);
    return flagAPasar;
}

int encontrarPedido (char nombreArchivo[],int idPedidoExterno)
{
    FILE*archi=fopen(nombreArchivo,"r+b");
    stPedido aux;
    int flag=0;
    if(archi!=NULL)
    {
        while(!feof(archi)&& flag ==0)
        {
            if(fread(&aux,sizeof(stPedido),1,archi)>0)
            {
                if(aux.idPedido == idPedidoExterno)
                {
                    flag=1;
                }
            }
        }
    }
    flag=noExistePedido(flag, idPedidoExterno);
    fclose(archi);
    return flag;
}

int darDeBajaUnPedido (char nombreArchivo[],int idPedidoExterno)
{
    int flag2=0, flagAPasar=0, flag=0,flag3=0;
    stPedido aux;
    flag=encontrarPedido(nombreArchivo, idPedidoExterno);
    flag3=verificarPedido(nombreArchivo,idPedidoExterno);

    if (flag!=0 && flag3==0)
    {
        FILE *archi=fopen(nombreArchivo,"r+b");
        if(archi!=NULL)
        {
            flag2=sistemanavegableMenuBajaPedido(1,1,2,2);
            if(flag2==1)
            {
                while(fread(&aux,sizeof(stPedido),1,archi) )
                {

                    if (aux.idPedido == idPedidoExterno)
                    {

                        if (aux.pedidoAnulado==1)
                        {
                            fseek(archi, -1*sizeof(stPedido),SEEK_CUR);
                            aux.pedidoAnulado=0;
                            fwrite(&aux,sizeof(stPedido),1,archi);
                            flagAPasar=0;
                            rewind(archi);
                        }

                    }
                }
                if (aux.pedidoAnulado==0)
                {
                    system("cls");
                    printf("\n\t\t\t El pedido N° %d fue dado de baja. ",idPedidoExterno);
                    system("pause");
                }
            }
        }
        fclose(archi);
    }
    return flagAPasar;
//    int flag=0;
//    int flag2=0;
//    int flagAPasar=0;
//
//    stPedido aux;
//    FILE*archi=fopen(nombreArchivo,"r+b");
//    if(archi!=NULL)
//    {
//        while(!feof(archi))
//        {
//            printf("***********");
//                if(aux.idPedido == idPedidoExterno)
//                {
//                    flag=1;
//                }
//        }
//    }
//
//    if (flag==1)
//    {
//        flag2=sistemanavegableMenuBajaPedido(1,1,2,2);
//
//        if(flag2==1)
//        {
//            if (aux.pedidoAnulado==1)
//            {
//                aux.pedidoAnulado=0;
//                fseek(archi, -1*sizeof(stPedido),SEEK_CUR);
//                fwrite(&aux,sizeof(stPedido),1,archi);
//                flagAPasar=0;
//            }
//            else
//            {
//                system("cls");
//                printf("\n\t\t\t Este pedido ya fue dado de baja con anteriormente. ");
//                system("pause");
//            }
//        }
//    }
//    noExistePedido(flag, idPedidoExterno);
//    fclose(archi);
//    return flagAPasar;
}

int ultimoIdPedido (char R[])
{
    int a = 999;
    stPedido l;


    FILE *archpedidos = fopen(R,"rb");


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
int ultimoIdCliente(char C[])
{
    int a = 99;
    stCliente cl;

    FILE *archivoClientes = fopen(C,"rb");

    if(archivoClientes != NULL)
    {
        while(fread(&cl,sizeof(stCliente),1,archivoClientes)>0)
        {
            a = cl.idCliente;
        }

    }

    fclose(archivoClientes);

    return a;
}
void buscarPedidosIdClienteAdmin(char R[], char C[]) /// Funciona
{
    stPedido p;
    stCliente cl;
    char control = 's';
    char nombreUser[30];
    int flag = 0;
    int idUser;

    FILE *archpedidos = fopen(R,"rb");
    FILE *archivoDeCliente = fopen(C,"rb");

    if(archpedidos != NULL)
    {
        while(control == 's')
        {
            printf("INGRESE NOMBRE DE USUARIO \n\n");
            fflush(stdin);
            gets(nombreUser);

            if(archivoDeCliente!=NULL)
            {
                idUser = buscaIdCliente(C,nombreUser);

                printf("NUMERO DE CLIENTE: %d \n",idUser);

                while (fread(&p,sizeof(stPedido),1,archpedidos) > 0)
                {
                    if(cl.idCliente == idUser)
                    {
                        printf(" =============================== \n");

                        flag = 1;
                        printf("PEDIDO: %d \n",p.idPedido);
                        printf("CLIENTE: %d \n",p.idCliente);
                        printf("FECHA: %s \n",p.fecha);
                        printf("DESCRIPCION: %s \n",p.descripcion);
                        printf("COSTO: %0.2f \n",p.costoPedido);

                        printf(" =============================== \n\n");
                    }
                }
            }
            if (flag == 0)
            {
                printf("EL CLIENTE NO POSEE PEDIDOS \n\n");
            }


            printf("DESEA BUSCAR PEDIDOS DE OTRO CLIENTE?  S/N \n\n");
            fflush(stdin);
            control = getch();
            flag = 0;
            rewind(archpedidos);
        }
    }
    else
    {
        printf("EL ARCHIVO DE PEDIDOS ESTA VACIO, CARGUE UN PEDIDO \n");
    }

    fclose(archpedidos);
    fclose(archivoDeCliente);
}

float obtenerCosto(char P[],int seleccion)
{
    stProductos p;
    float costo = 0;


    FILE *archivoProductos = fopen(P,"rb");

    if(archivoProductos != NULL)
    {
        while(fread(&p,sizeof(stProductos),1,archivoProductos)>0)
        {
            if(p.codProducto == seleccion)
            {
                costo = p.costo;
            }

        }

        rewind(archivoProductos);
    }

    fclose(archivoProductos);

    return costo;
}


float seleccionarProductos(char P[])
{
    float costo;
    int seleccion;
    int cantidad;
    float calc = 0;
    float acumulador = 0;
    char control = 's';

    mostrarProductos(P);

    printf("\n");

    do
    {

        printf("< --- SELECCIONE EL CODIGO DEL PRODUCTO --- >  \n");
        scanf("%d",&seleccion);

        costo = obtenerCosto(P,seleccion);

        printf("INGRESE LA CANTIDAD DE UNIDADES A COMPRAR: \n");
        scanf("%d",&cantidad);

        calc = (costo * cantidad);

        acumulador =  acumulador + calc;

        printf("DESEA AGREGAR MAS PRODUCTOS AL CARRO?? \n");
        fflush(stdin);
        control = getch();

        printf("VA GASTANDO: %0.2f \n",acumulador);


    }
    while(control == 's');

    return acumulador;
}

void ejey (int y)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X=0;
    pos.Y=y;

    SetConsoleCursorPosition(hConsole, pos);
}

int menuUsuario (int elecion, char c[], char p [], char r [], int idUser)
{
    int dimensionFecha = 80;
    char fecha[dimensionFecha];
    int flag2=0;
    int  idPedidoExterno=0;

    switch(elecion)
    {
    case 1:
        system("cls");
        altaPedido(r,p,c,idUser,fecha,dimensionFecha);
        break;
    case 2:
        system("cls");
        mostrarUnUserPedidos(r,idUser);
        printf("\t\t\t\t\t\n Ingrese el ID del Pedido que desea cancelar: ");
        scanf("%d",&idPedidoExterno);
        flag2=darDeBajaUnPedido(r,idPedidoExterno);
        break;
    case 3:
        system("cls");
        mostrarUnUserPedidos(r,idUser);
        saltoDeLinea(1);
        system("pause");
        break;
    case 4:
        system("cls");
        flag2=menuConfiguracionDeUsuario(c,idUser);
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
///--------------------------------------------------------------------------------------------------------------
int menuAdmin (int elecion, char c[], char p [], char r [], int idUser)
{
    int dimensionFecha = 80;
    char fecha[dimensionFecha];
    int flag2=0;
    int idUserExterno=0;

    switch(elecion)
    {

    case 1:
        system("cls");
        altaProductos(p);
        break;

    case 2:
        system("cls");
        mostrarUserRegistro(c);
        system("pause");
        break;
    case 3:
        system("cls");
        mostrarProductos(p);
        system("pause");
        break;

    case 4:
        system("cls");
        altaPedido(r,p,c,idUser,fecha,dimensionFecha);
        break;

    case 5:
        system("cls");
        mostrarUserRegistro(c);
        printf("\t\t\t\t\t\n Ingrese el ID del usuario del cual desea ver su pedido: ");
        scanf("%d",&idUserExterno);
        system("cls");
        mostrarUnUserPedidosAdmin(r,idUserExterno);
        saltoDeLinea(5);
        system("pause");
        break;
    case 6:
        system("cls");

        mostrarUserRegistro(c);
        printf("\t\t\t\t\t\n Ingrese el ID del usuario que desea dar de alta o de baja: ");
        scanf("%d",&idUserExterno);
        flag2=darDeBajaODarDeAlta(c,idUserExterno);
        break;
    case 7:
        system("cls");
        printf("\t\t\t\t\t\n Ingrese el ID del usuario que desea modificar: ");
        scanf("%d",&idUserExterno);
        flag2=menuConfiguracionDeUsuario(c,idUserExterno);
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

int puntosParaElegirPaso1 (int eleccion, int eleccionMenu, char c[],char p [], char r [])
{
    int idUser=0;

    printf("\n\n\n\n");
    switch (eleccion)
    {
    case 1:
        system("cls");
        registrarse (c);
        break;
    case 2:
        system("cls");
        idUser=iniciarSesion(c);
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
                menu=menu==menuinicio ? menufin: --menu;
                printf("\r                               ");
                ejey(lineainicio + menu-1);
                printf("\t\t\t----->");
            }
            else if (opcion==FLECHAABAJO)
            {
                menu=menu==menufin ? menuinicio: ++menu;
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

void menuNavegable (int menu,int menuinicio,int menufin, int lineainicio, int opcion, char c[],char p [], char r [])
{
    int flag=0;
    int eleccion=0;
    int eleccionMenu=0;
    int idUser=0;
    int rolUser=0;

    do
    {
        system("cls");

        eleccion=sistemanavegableRegistrarse(1,1,2,1);

        idUser=puntosParaElegirPaso1(eleccion,eleccionMenu,c,p,r);
        rolUser=buscaRolCliente(c,idUser);

        system("cls");


        if (idUser==0)
        {
            flag=1;
        }

        else if (rolUser==1)
        {
            do
            {
                eleccionMenu=sistemanavegableMenuAdmin(1,1,8,1);

                flag=menuAdmin(eleccionMenu,c,p,r,idUser);
            }
            while(flag==0);
        }

        else
        {
            do
            {
                eleccionMenu=sistemanavegableMenuUsuario(1,1,5,1);

                flag=menuUsuario(eleccionMenu,c,p,r,idUser);

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

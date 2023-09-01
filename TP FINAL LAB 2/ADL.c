#include "ADL.h"


int alta (stCelda adl[], stCliente cliente, stProducto x, int validos)
{
    nodoListaProducto * aux = crearNodo(x);
    //Te pide otra cosas nuesra funcion
    int pos = buscaPosIdClienteCelda(adl, cliente.idCliente, validos);
    if(pos==-1)
    {
        validos=agregarClienteCelda(adl,cliente, validos);
        pos=validos-1;

    }
    adl[pos].listaDeProductos=agregarNodoNuevoAlPrincipio((adl[pos].listaDeProductos), aux);
    return validos;
}

int buscaPosIdClienteCelda (stCelda adl[], int idCliente,int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos) && (rta==-1))
    {
        if (adl[i].cliente.idCliente==idCliente)
        {
            rta=i;
        }
        i++;

    }
    return rta;
}

int buscarIdPorNombreAdl (stCelda adl[], char nombreUsuario [],int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos) && (rta==-1))
    {
        if (strcmp(adl[i].cliente.userName,nombreUsuario)==0)
        {
            rta=adl[i].cliente.idCliente;
        }
        i++;

    }
    return rta;
}

int agregarClienteCelda (stCelda adl[], stCliente cliente, int validos)
{
    adl[validos].cliente=cliente;
    adl[validos].listaDeProductos = inicLista();
    validos++;
    return validos;
}

int agrandarAdl (stCelda ** adl, int validos, int dimension)
{
    (*adl)=realloc((*adl),(validos+10)*sizeof(stCelda));
    return dimension+10;
}

void mostrarAdlAdmin(stCelda adl[], int validos)
{
    int i=0;
    while(i<validos)
    {
        puts("\t\t\t =============================== ");

        mostrarCliente(adl[i].cliente);
        mostrarClienteAdmin(adl[i].cliente);

        puts("\t\t\t =============================== ");
        i++;
    }
}

void mostrarAdlUser(stCelda adl[], int validos)
{
    int i=0;
    while(i<validos)
    {
        mostrarCliente(adl[i].cliente);
        i++;
    }
}

void mostrarClienteAdmin(stCliente cliente)
{
    printf("\n\t\t\t Rol: %d \n",cliente.rol);
    printf("\n\t\t\t Activo: %d \n",cliente.activo);
}

void mostrarCliente(stCliente cliente)
{
    printf("\n\t\t\t IdCliente: %d \n",cliente.idCliente);
    printf("\n\t\t\t Nombre: %s \n",cliente.nombre);
    printf("\n\t\t\t Apellido: %s \n",cliente.apellido);
    printf("\n\t\t\t UserName: %s \n",cliente.userName);
    printf("\n\t\t\t Contraseña: %s \n",cliente.password);
    printf("\n\t\t\t Email: %s \n",cliente.mail);
    printf("\n\t\t\t Genero: %c \n",cliente.genero);
}

int contarClientes(char archivoClientes[])
{
    int cantidad=0;
    FILE*clientes;
    clientes=fopen(archivoClientes,"rb");
    if(clientes!=NULL)
    {
        fseek(clientes,0,SEEK_END);

        cantidad= ftell(clientes)/sizeof(stCliente);
        fclose(clientes);
    }
    return cantidad;

}

int deArchivoAAdl (stCelda ADL[], char archivo [])
{
    FILE * clientes=fopen(archivo,"rb");
    stCliente aux;
    int i=0;

    if (clientes)
    {
        while(fread(&aux,sizeof(stCliente),1,clientes)>0)
        {
            i=agregarClienteCelda(ADL,aux,i);
        }
        fclose(clientes);
    }
    return i;
}

void deAdlAlArchivo(char archivoAPasar[], stCelda adl[], int validos)
{
    FILE * archivoDeClientes=fopen(archivoAPasar,"wb");

    int i=0;
    if (archivoDeClientes!=NULL)
    {
        while (i<validos)
        {
            fwrite(&adl[i].cliente,sizeof(stCliente),1,archivoDeClientes);
            i++;
        }
    }
    fclose(archivoDeClientes);
}

void registrarse(stCelda adl [], int * validos, int *dimension)
{
    setlocale(LC_ALL, "");

    int flag=0,i=0, flag2=0;
    char nombreUsuario [20];
    char mailcopy [100];

    i=(*validos);

    if (*dimension==*validos)
    {
        *dimension=agrandarAdl(adl, *validos, *dimension);
    }

    adl[i].cliente.idCliente=buscaPosUltima(adl,*validos)+1;

    adl[i].cliente.rol= 1;


    printf("\n\t\t\tIngrese su nombre: ");
    fflush(stdin);
    gets(adl[i].cliente.nombre);

    printf("\n\t\t\tIngrese su apellido: ");
    fflush(stdin);
    gets(adl[i].cliente.apellido);

    do
    {
        printf("\n\t\t\tIngrese su nombre se usuario: ");
        fflush(stdin);
        scanf("%s", nombreUsuario);
        flag=compararUsuarios(adl,nombreUsuario,*validos);
        usuarioRepetido(flag);

    }
    while (flag!=0);

    strcpy(adl[i].cliente.userName, nombreUsuario);

    printf("\n\t\t\tIngrese su genero (Solo inicial): ");
    fflush(stdin);
    scanf("%c",&adl[i].cliente.genero);

    do
    {
        printf("\n\t\t\tIngrese su email: ");
        fflush(stdin);
        gets(mailcopy);
        flag2=verificacionEmail(mailcopy);
        mailInvalido(flag2);
    }
    while(flag2==0);

    strcpy(adl[i].cliente.mail, mailcopy);

    printf("\n\t\t\tIngrese su contraseña (No mas de 10 caracteres): ");
    fflush(stdin);
    asteriscos(adl[i].cliente.password);

    adl[i].cliente.activo = 1;

    i++;
    *validos = i;

    system("cls");
    saltoDeLinea(3);
    printf("\t\t\t\t====== Usted se ha registrado exitosamente ======");
    saltoDeLinea(2);
    printf("\t\t\t\tPor favor. ");
    system("pause");

}

int iniciarSesion(stCelda adl[],int validos)
{
    setlocale(LC_ALL, "");
    int idUser=0,flag1=0,flag2=0, intentoscontra=0,intentosnombre=0;
    char nombreUsuario []="NULL", password []="NULL";
    printf("\n\t\t\t\t =====Por favor ingrese su usuario y contraseña=====");

    do
    {
        printf("\n\n\t\t\t Usuario: ");
        fflush(stdin);
        gets(nombreUsuario);

        flag1=compararUsuarios(adl,nombreUsuario,validos);

        if(flag1==1)
        {
            idUser=buscarIdPorNombreAdl(adl,nombreUsuario,validos);
        }
        else
        {
            system("cls");
            printf("\n\t\t\t =====Usuario inexistente. Intentelo nuevamente.=====");
            intentosnombre++;
        }

    }
    while (flag1!=1 && intentosnombre!=3);

    if (intentosnombre==3)
    {
        system("cls");
        printf("\n\t\t Has sobrepasado el limite de intentos para el nombre. ");
        system("pause");
        idUser=0;
    }

    if (idUser!=0)
    {
        do
        {
            printf("\n\n\t\t\t Contraseña: ");
            fflush(stdin);
            asteriscos(password);
            flag2=compararPassword (adl,password,validos);
            if (flag2==0)
            {
                system("cls");
                printf("\n\t\t\t =====Contraseña incorrecta, por favor vuelva a intentarlo=====");
            }

            if(adl[buscaPosIdClienteCelda(adl,idUser,validos)].cliente.activo==0)
            {
                printf("\n\n\t\t=====Este usuario ya no se encuentra activo.Si desea activarlo comuniquese al 0800-428-7627===== \n\n\t\t\t\t\tPor favor, ");
                system("pause");
                idUser=0;
            }

            intentoscontra++;

            if (intentoscontra==3)
            {
                system("cls");
                printf("\n\t\t Has sobrepasado el limite de intentos para la contraseña. ");
                system("pause");
                idUser=0;
            }

        }
        while (flag2==0 && intentoscontra!=3 && idUser!=0);
    }
    return idUser;
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

void usuarioRepetido (int flag)
{

    if (flag==1)
    {
        system("cls");
        printf("\n\t\t\t=====Usuario ya registrado, por favor vuelva a intentarlo=====");
    }
}

int buscaPosUltima (stCelda adl[],int validos)
{
    int rta=-1;
    int i=0;
    while(i<validos-1)
    {
        i++;
    }

    rta=adl[i].cliente.idCliente;

    return rta;
}

int verificacionEmail (char email[])
{

    int flag=0;

    if ((strchr (email, 64)) != 0)
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

int compararUsuarios (stCelda adl[],char usuario[], int validos)
{
    int flag=0, i=0;
    while (i<validos && flag==0)
    {
        if (strcmp (adl[i].cliente.userName, usuario) == 0)
        {
            flag=1;
        }
        i++;
    }

    return flag;
}

int compararPassword (stCelda adl[],char password[], int validos)
{
    int flag=0, i=0;
    while (i<validos && flag==0)
    {
        if (strcmp (adl[i].cliente.password, password) == 0)
        {
            flag=1;
        }
        i++;
    }

    return flag;
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

void saltoDeLinea (int lineas)
{
    for (int i=0; i<lineas; i++)
    {
        printf("\n");
    }
}

int darDeBajaUnUser (stCelda adl[],int idUser,int validos)
{
    int i=0;
    int flag=0;
    int flag2=0;
    int flagAPasar=0;

    while(i<validos && flag==0)
    {
        if(adl[i].cliente.idCliente == idUser)
        {
            flag=1;
        }
        i++;
    }
    i--;
    if (flag==1)
    {
        flag2=sistemanavegableMenuBajaAltaUnUser(1,1,2,3);

        if(flag2==1)
        {
            if (adl[i].cliente.activo==1)
            {
                adl[i].cliente.activo=0;
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
    if (flag!=1)
    {
        noExiste(idUser);
    }

    return flagAPasar;
}

int darDeBajaODarDeAlta (stCelda adl[],int idUserExterno,int validos)
{

    int i=0;
    int flag=0;
    int flag2=0;
    int flagAPasar=0;

    while(i<validos && flag==0)
    {
        if(adl[i].cliente.idCliente == idUserExterno)
        {
            flag=1;
        }
        i++;
    }
    i--;

    if (flag==1)
    {
        flag2=sistemanavegableMenuBajaAlta(1,1,3,1);

        if(flag2==1)
        {
            if (adl[i].cliente.activo==1)
            {
                adl[i].cliente.activo=0;
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
            if (adl[i].cliente.activo==0)
            {
                adl[i].cliente.activo=1;
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
    }

    if (flag!=1)
    {
        noExiste(idUserExterno);
    }
    return flagAPasar;
}

void noExiste (int idUserExterno)
{
    system("cls");
    printf("\n\t\t\t No existe el ID de usuario: %d. ", idUserExterno);
    system("pause");
}

void modificarNombre(stCelda adl[],int idUserExterno, int validos)
{

    char nuevoNombre[30];
    int i=0;

    i=buscaPosIdClienteCelda(adl,idUserExterno,validos);

    if(i != -1)
    {
        printf("\n\t\t\tIntroduzca su nuevo nombre:  ");
        fflush(stdin);
        gets(nuevoNombre);
        strcpy(adl[i].cliente.nombre,nuevoNombre);
    }
    else
    {
        noExiste(idUserExterno);
    }
}

void modificarApellido(stCelda adl[],int idUserExterno, int validos)
{
    char nuevoApellido[30];
    int i=0;

    i=buscaPosIdClienteCelda(adl,idUserExterno,validos);

    if(i != -1)
    {
        printf("\n\t\t\tIntroduzca su nuevo apellido:  ");
        fflush(stdin);
        gets(nuevoApellido);
        strcpy(adl[i].cliente.apellido,nuevoApellido);
    }
    else
    {
        noExiste(idUserExterno);
    }
}

void modificarEmail(stCelda adl[],int idUserExterno, int validos)
{
    char nuevoEmail[100];
    int i=0;
    int flag2=0;

    i=buscaPosIdClienteCelda(adl,idUserExterno,validos);

    if(i != -1)
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

        strcpy(adl[i].cliente.mail, nuevoEmail);

    }
    else
    {
        noExiste(idUserExterno);
    }
}


void modificarPassword(stCelda adl[],int idUserExterno, int validos)
{
    char nuevoPassword[30];
    int i=0;

    i=buscaPosIdClienteCelda(adl,idUserExterno,validos);

    if(i != -1)
    {
        printf("\n\t\t\tIntroduzca su nuevo password:  ");
        fflush(stdin);
        asteriscos(nuevoPassword);
        strcpy(adl[i].cliente.password, nuevoPassword);
    }
    else
    {
        noExiste(idUserExterno);
    }

}

//stCliente modificacion (stCliente c, int id,int op)
//{
//    int op=0;
//    do
//    {
//        system("color f0");
//        menuModificarPerfil();
//        puts("\n\tIngrese una opcion...");
//        fflush(stdin);
//        scanf("%d",&op);
//        switch(op)
//        {
//        case 1:
//        {
//            system("cls");
//            printf("\nIngrese nuevo Nombre:\n");
//            fflush(stdin);
//            gets(c.nombre);
//            system("cls");
//            break;
//        }
//        case 2:
//        {
//            system("cls");
//            printf("\nIngrese nuevo Apellido:\n");
//            fflush(stdin);
//            gets(c.apellido);
//            system("cls");
//            break;
//        }
//        case 3:
//        {
//            do
//            {
//                system("cls");
//                printf("\nIngrese nuevo Usuario: \n");
//                fflush(stdin);
//                gets(c.userName);
//                system("cls");
//            }
//            while(verificarUsernameRepetido(c.userName)==1);
//            break;
//        }
//        case 4:
//        {
//            system("cls");
//            printf("\nIngrese nueva Clave:\n");
//            fflush(stdin);
//            gets(c.password);
//            system("cls");
//            break;
//        }
//        case 5:
//        {
//            do
//            {
//                system("cls");
//                printf("\nIngrese nuevo mail:\n");
//                fflush(stdin);
//                gets(c.mail);
//                system("cls");
//            }
//            while (verificarMail(c.mail)==0);
//            break;
//        }
//        case 6:
//        {
//            system("cls");
//            printf("\nIngrese nuevo genero:\n");
//            fflush(stdin);
//            scanf("%c",&c.genero);
//            system("cls");
//            break;
//        }
//        case 7:
//        {
//            system("cls");
//            if(id>0)
//            {
//                if(c.activo==1)
//                {
//                    c.activo=0;
//                    printf("\t\t\nCuenta desactivada en caso de cerrar sesion no podra volver a ingresar\n");
//                    system("pause");
//                }
//                else
//                {
//                    c.activo=1;
//                    printf("\t\t\nCuenta activada.\n");
//                    system("pause");
//                }
//            }
//            else
//            {
//                printf("\nEste usuario no puede darse de baja.\n\n\n");
//                system("pause");
//            }
//            system("cls");
//            break;
//        }
//        case 0:
//        {
//            system("cls");
//            puts("Regresando... \n");
//            break;
//        }
//        }
//    }
//    while(op!=0);
//    return c;
//}


//void modificarCliente(stCelda adl[],int id, int validos)
//{
//    int i=buscaPosIdClienteCelda(adl,id,validos);
//    adl[i].cliente=modificacion(adl[i].cliente,id);
//}

void mensajeDespedida ()
{
    system("cls");
    saltoDeLinea(5);
    printf("\t\t\t *==================== GRACIAS VUELVA PRONTO ====================*");
    saltoDeLinea(12);
}

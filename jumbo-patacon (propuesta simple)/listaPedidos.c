#include "listaPedidos.h"

///Funcion fecha comentada esta en la linea 105 mas menos

const char archivoPedidos[]= {"pedidos.dat"};
void pedidos(int idCliente)
{
    stPedido pedidos;
    int op1;

    do
    {
        system("color f0");
//        menuPedido();
        puts("\n\tIngrese una opcion... \t");
        fflush(stdin);
        scanf("%d",&op1);
        switch(op1)
        {
        case 1:
        {
            archAltaPedido(pedidos,idCliente);
            break;
        }
        case 2:
        {
            system("cls");
            mostrarPedidosCliente(idCliente);
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            buscarPedidoCliente(idCliente);
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            system("cls");
            modificarPedido(idCliente);
            system("pause");
            system("cls");
            break;
        }
        case 0:
        {
            system("cls");
            break;
        }
        }
    }
    while(op1!=0);
}
stPedido cargarPedido(stPedido p, int idCliente, int idPedido)
{
   // int pedidos=0;
    //int confirmar=0, estadoPedido=0;
    //pedidos=cantidadPedidos();
    system("cls");
    puts("\n\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>-Realizar pedido-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");


    printf("\n\t\t\t Id Pedido: %d", idPedido+1);
    p.idPedido=idPedido+1;


    printf("\n\t\t\t Id Cliente: %d\n", idCliente);
    p.idCliente=idCliente;


//    fechaPedido(&p);
//    printf("\n\t\t\t\t\t\t\t\t\t\tFecha y Hora: %s", p.fecha);
//
//  //  p.costo=costoPedido();
//
//    printf("\n\nDescripcion del pedido(opcional): ");
//    fflush(stdin);
//    gets(p.descripcion);
//
//    printf("\n\n\t\t\t\t\tEl valor del pedido es de %.2f\n\n", p.costo);

  //  printf("\n\n\tPara confirmar el pedido presione cualquier tecla - Esc para anular...\n\n");
 //   confirmar=getch();
//    if(confirmar!=27)
//    {
//        p.pedidoAnulado=estadoPedido;
//        puts("\nPedido Confirmado\n");
//    }
//    else
//    {
//
//        p.pedidoAnulado=estadoPedido+1;
//        puts("\nPedido anulado\n");
//    }
 //   system("pause");
    return p;
}



//void fechaPedido(stPedido * p)
//{
//    int i=0;
//    time_t t = time(NULL);
//    struct tm tiempoLocal = *localtime(&t);
//    char *formato = "%d-%m-%Y %H:%M:%S";
//
//    strftime(p[i].fecha, sizeof p[i].fecha, formato, &tiempoLocal);
//}
void mostrarPedidosCliente(int idCliente)
{
    stPedido p;
    FILE * archPedido = fopen(archivoPedidos, "rb");
    if(archPedido!=NULL)
    {
        puts("\n                     -------------------------------------Mis Pedidos------------------------------------------\n");
        while(fread(&p, sizeof(stPedido), 1, archPedido))
        {
            if(idCliente==p.idCliente)
            {
                mostrarStructPedido(p);
            }
        }
    }
    fclose(archPedido);
}
int cantidadPedidos()
{
    stPedido p;
    FILE *archPedido= fopen(archivoPedidos,"rb");
    int cantidadPedidos=0;

    if(archPedido!=NULL)
    {
        while(fread(&p, sizeof(stPedido), 1, archPedido))
        {
            cantidadPedidos++;
        }
    }
    fclose(archPedido);
    return cantidadPedidos;
}

void buscarPedido()
{
    FILE * archiP = NULL;
    int idPed;
    printf("\n-----------------Buscar Pedido-------------------\n");
    printf("\n Ingresa el Id de pedido para buscar: ");
    scanf("%d", &idPed);

    archiP=fopen(archivoPedidos,"rb");
    fseek(archiP,0,SEEK_SET);
    stPedido p;

    if(archiP!=NULL)
    {
        while(fread(&p,sizeof(stPedido),1,archiP))
        {
            if(idPed==p.idPedido)
            {
                mostrarStructPedido(p);
                system("pause");
            }
        }
    }
    fclose(archiP);
}

void buscarPedidoCliente(int idCliente)
{
    FILE * archiP = NULL;
    int idPed;
    printf("\n-----------------Buscar Pedido-------------------\n");
    printf("\n Ingresa el Id de pedido para buscar: ");
    scanf("%d", &idPed);

    archiP=fopen(archivoPedidos,"rb");

    stPedido p;

    if(archiP!=NULL)
    {
        while(fread(&p,sizeof(stPedido),1,archiP))
        {
            if(idPed==p.idPedido)
            {
                if(idCliente==p.idCliente)
                {
                    mostrarStructPedido(p);
                }
                else
                {
                    printf("\nEl pedido no fue encontrado\n\n");
                }
            }
        }
    }
    fclose(archiP);
}

void archAltaPedido(stPedido p, int idCliente)
{
    FILE * archPedido = fopen(archivoPedidos, "ab");

    if(archPedido!=NULL)
    {
        system("cls");
        //    p=cargarPedido(p,idCliente);
        system("cls");
        fwrite(&p, sizeof(stPedido), 1, archPedido);
    }
    fclose(archPedido);
}
//stPedido anularPedido (int idPedido, int idCliente,FILE *  archiP)
//{
//    stPedido p;
//
//    while(fread(&p, sizeof(stPedido), 1, archiP)>0)
//    {
//        if(idPedido==p.idPedido && idCliente==p.idCliente)
//        {
//            p.pedidoAnulado=1;
//        }
//    }
//    if(p.pedidoAnulado==1)
//    {
//        printf(" \t \n Pedido %i anulado con exito.\n\n", p.idPedido);
//        system("pause");
//    }
//    else
//    {
//        if(fread(&p, sizeof(stPedido), 1, archiP)==0)
//        {
//            printf("\t \t \n No se encontro el pedido");
//            system("pause");
//        }
//    }
//    fseek(archiP,(-1)*sizeof(stPedido), SEEK_CUR);
//    return p;
//}

void modificarPedido(int idCliente)
{
    stPedido aux;
    stPedido modif;
    int idPedido=0;
    printf("\t \t \n Ingrese la ID del Pedido a Modificar:");
    scanf("%i", &idPedido);
    system("cls");
    int flag=0;
    FILE * archiP=fopen(archivoPedidos,"r+b");
    fseek(archiP, 0, SEEK_SET);
    if(archiP!=NULL)
    {
        while(!feof(archiP)&& flag==0)
        {
            if(fread(&aux,sizeof(stPedido),1,archiP)>0)
            {
                if(aux.idPedido==idPedido)
                {
                    flag=1;
                }
            }
        }
        if (flag==1)
        {
            fseek(archiP,(-1)*sizeof(stPedido), SEEK_CUR);
            modif=modificacionPedidoCliente(aux, idPedido,  idCliente, archiP);
            fwrite(&modif, sizeof(stPedido),1,archiP);
        }
        else
        {
            printf("\nNo se encontro pedido con esa ID\n");
        }
    }
    fclose(archiP);
}
stPedido modificacionPedidoCliente (stPedido p,int idPedido, int idCliente, FILE * archiP)
{
    int op=0;
    if (p.idCliente==idCliente)
    {
        do
        {
            system("color f0");
//            menuModificarPedidoCliente();
            puts("\n\tIngrese una opcion...");
            fflush(stdin);
            scanf("%d",&op);
            system("cls");
            switch(op)
            {
            case 1:
            {
                system("cls");
                printf("\t \t \nIngrese nueva descripcion:\n");
                fflush(stdin);
               // gets(p.descripcion);
                system("cls");
                break;
            }
            case 2:
            {
                system("cls");
                //p=anularPedido (idPedido,idCliente,archiP);
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
    }
    return p;
}
void mostrarStructPedido(stPedido p)
{
    puts("\n------------------------------------------------------------\n");
    printf("\nId Pedido: %d\n", p.idPedido);
    printf("\n\nId Cliente: %d\n", p.idCliente);
    printf("\n\nId Producto: %d\n", p.idProducto);
//    printf("\n\nFecha: %s\n", p.fecha);
  //  printf("\n\nDescripcion: %s\n", p.descripcion);
  //  printf("\n\nCosto: %.2f\n", p.costo);
//    if(p.pedidoAnulado==0)
//    {
//        printf("\nPedido: Activo\n");
//    }
//    else
//    {
//        printf("\nPedido: Anulado\n");
//    }

    puts("\n------------------------------------------------------------\n");
}

///Lista Pedidos

nodoListaPedidos * inicListaPedidos()
{
    return NULL;
}

nodoListaPedidos * crearNodoListaPedidos(stPedido p)
{
    nodoListaPedidos *aux = (nodoListaPedidos *) malloc(sizeof(nodoListaPedidos));
    aux->p = p;
    aux->listaDeProductos=inicListaProducto();
    aux->siguiente=NULL;
    return aux;
}



nodoListaPedidos * agregarAlPrincipioPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = lista;
    }
    lista = nuevoNodo;
    return lista;
}

nodoListaPedidos * agregarAlFinalPedido(nodoListaPedidos * lista, nodoListaPedidos * nuevo)
{
    if(lista== NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoListaPedidos * ultimo = buscarUltimoNodoPedidos(lista);
        ultimo->siguiente=nuevo;
    }
    return lista;
}

nodoListaPedidos * buscarUltimoNodoPedidos(nodoListaPedidos * lista)
{
    nodoListaPedidos * ultimo=lista;
    if(ultimo!=NULL)
    {
        while(ultimo->siguiente != NULL)
        {
            ultimo=ultimo->siguiente;
        }
    }
    return ultimo;
}

void mostrarListaRecursivaPedidos(nodoListaPedidos * lista)
{
    if(lista)
    {
        mostrarStructPedido(lista->p);
        mostrarListaRecursivaPedidos(lista->siguiente);
    }
}

nodoListaPedidos * borrarNodoPorIdPedido(nodoListaPedidos * lista, int id)
{
    nodoListaPedidos * seg=lista;
    nodoListaPedidos * ante;
    while((seg!=NULL)&& (lista->p.idPedido!=id))
    {
        ante=seg;
        seg=seg->siguiente;
    }
    if(seg!=NULL)
    {
        ante->siguiente=seg->siguiente;
        free(seg);
    }
    return lista;
}

nodoListaPedidos * borrarTodaLaListaPedidos(nodoListaPedidos * lista)
{
    nodoListaPedidos * actual=lista;

    while (lista!=NULL)
    {
        actual=lista;
        lista=lista->siguiente;
        free(actual);
    }
    return lista;
}

nodoListaPedidos * agregaProductosListaPedidos(nodoListaPedidos * listaPedido, stProducto p)
{
    nodoListaProducto * prod=inicListaProducto();
    prod=crearNodoListaProducto(p);
    listaPedido->listaDeProductos=agregarAlPrincipioProducto(listaPedido->listaDeProductos, prod);
    return listaPedido;
}

//void muestraProductosPedido(nodoListaProducto * lista)
//{
//    if (lista)
//    {
//        mostrarUnProducto(lista->p);
//        muestraProductosPedido (lista->siguiente);
//    }
//}

nodoListaPedidos * hacerPedido(nodoListaPedidos * lista, nodoArbol * arbol, int * idPedido)
{
   // int id=0;
   // char salir= ' ';
  //  nodoArbol * aux=inicArbol();
   // stProducto prod;
//    while (salir!='s')
//    {
//        inorder(arbol);
//        printf("Que producto desea agregar al pedido? (Ingrese la ID)\n");
//        scanf("%i",  &id);
//        aux=buscarPorID(arbol, id);
//        prod=retornaProdNodo(aux);
//        lista=agregaProductosListaPedidos(&lista, prod);
//        printf("Desea continuar agregando productos? (s para salir)\n");
//        salir=getch();
//        system("cls");
//        mostrarUnProducto(lista->producto->p);
//        system("pause");
//    }
    return lista;
}

int buscaIdUltimoPedido(char rutaDelArchivoPedido[])
{
    int rta=-1;
    stPedido aux;
    FILE * archi = fopen(rutaDelArchivoPedido, "rb");
    if (archi)
    {
        while(fread(&aux, sizeof(stPedido), 1, archi)>0)
        {
            if(aux.idPedido>rta)
            {
                rta=aux.idPedido;
            }
        }
        fclose(archi);
    }
    return rta;
}


#include "productos.h"



stProducto cargarUnProducto ()
{
    stProducto a;

        printf("\nIngrese nombre del producto: ");
        fflush(stdin);
        gets(a.nombreProducto);
        printf("\nIngrese la descripcion del producto: ");
        fflush(stdin);
        gets(a.descripcionProducto);
        printf("\nIngrese el precio del producto: ");
        scanf("%f", &a.valor);
        printf("\nEl producto se encuentra eliminado? 1/0: ");
        scanf("%d", &a.productoAnulado);
    return a;
}
void mostrarMuchosProducto(stProducto a[], int validos)
{
    int i=0;
    while (i<validos)
    {
        mostrarUnProducto(a[i]);
        i++;
    }
}

void mostrarUnProducto(stProducto a)
{
    puts("\n---------------");
    printf("\n ID del producto: %d",a.idProducto);
    printf("\n Nombre del producto: %s",a.nombreProducto);
    printf("\n Descripcion: %s",a.descripcionProducto);
    printf("\n El precio del producto: %0.02f", a.valor);
    printf("\n Quedan: %d", a.cantidad);
    estadoDelProducto(a.productoAnulado);
    puts("\n---------------");
}


void estadoDelProducto(int numero)
{
    if (numero==1)
    {
        printf("\n El producto se no encuentra eliminado: %d", numero);
    }
    else if (numero==0)
    {
        printf("\n El producto  se encuentra eliminado: %d", numero);
    }
    else
    {
        printf("\n ERROR: %d", numero);
    }
}

int contarProductos(char archivoProductos[])
{
    int cantidad=0;

    FILE*productos;

    productos=fopen(archivoProductos,"rb");

    if(productos!=NULL)
    {
        fseek(productos,0,SEEK_END);

        cantidad= ftell(productos)/sizeof(stProducto);
        fclose(productos);
    }
    return cantidad;
}

int deArchivoToArrayProductos (stProducto prods[], char archivo [])
{
    FILE * produtos=fopen(archivo,"rb");
    stProducto aux;
    int i=0;

    if (produtos)
    {
        while(fread(&aux,sizeof(stProducto),1,produtos)>0)
        {
            prods[i]=aux;
            i++;
        }
    }
    fclose(produtos);
    return i;
}
void agregarDeArrayAArchivo(char archivoAPasar[], stProducto prods)
{
    FILE * archi=fopen(archivoAPasar,"ab");
    if (archi!=NULL)
    {
        fwrite(&prods,sizeof(stProducto),1,archi);
    }
    fclose(archi);
}
void deArrayAArchivo(char archivoAPasar[], stProducto prods[], int validos)
{
    FILE * archi=fopen(archivoAPasar,"wb");

    int i=0;
    if (archi!=NULL)
    {
        while (i<validos)
        {
            fwrite(&prods[i],sizeof(stProducto),1,archi);
            i++;
        }
    }
    fclose(archi);
}

///Lista Prod.

nodoListaProducto * inicListaProducto()
{
    return NULL;
}
nodoListaProducto * crearNodoListaProducto(stProducto p)
{
    nodoListaProducto *aux = (nodoListaProducto *) malloc(sizeof(nodoListaProducto));
    aux ->p = p;
    aux ->siguiente =NULL;
    return aux;
}
nodoListaProducto * agregarAlPrincipioProducto(nodoListaProducto * lista, nodoListaProducto * nuevoNodo)
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
nodoListaProducto * agregarAlFinalProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{
    if(lista== NULL)
    {
        lista=nuevo;
    }
    else
    {
        nodoListaProducto * ultimo = inicListaProducto();
        ultimo=buscarUltimoNodoProducto(lista);
        ultimo->siguiente=nuevo;
    }return lista;
}
nodoListaProducto * buscarUltimoNodoProducto(nodoListaProducto * lista)
{
	nodoListaProducto * ultimo=lista;
	if(ultimo!=NULL){
	while(ultimo->siguiente != NULL)
	{
		ultimo=ultimo->siguiente;
	}
	}return ultimo;
}
nodoListaProducto * agregarEnOrdenPorNombreProducto(nodoListaProducto * lista, nodoListaProducto * nuevo)
{

	if(lista==NULL)
	{
		lista=nuevo;
	}
	else
	{
	    if(strcmp(nuevo->p.nombreProducto,lista->p.nombreProducto)<0)
	    {
	        lista=agregarAlPrincipioProducto(lista,nuevo);
	    }
	    else
        {
            nodoListaProducto * ante=lista;
            nodoListaProducto * sig=lista->siguiente;
            while(sig!=NULL && strcmp(sig->p.nombreProducto,nuevo->p.nombreProducto)<0)
            {
                ante=sig;
                sig=sig->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=sig;
        }
	}
return lista;
}
void mostrarListaRecursivaProductos(nodoListaProducto * lista)
{
    if(lista!=NULL)
    {
        mostrarUnProducto(lista->p);
        mostrarListaRecursivaProductos(lista->siguiente);
    }
}
nodoListaProducto * borrarNodoPorIdProducto(nodoListaProducto * lista, int id)
{
    nodoListaProducto * seg=lista;
    nodoListaProducto * ante;
    while((seg!=NULL)&& (lista->p.idProducto!=id))
    {
        ante=seg;
        seg=seg->siguiente;
    }
    if(seg!=NULL)
    {
        ante->siguiente=seg->siguiente;
        free(seg);
    }return lista;
}

nodoListaProducto * borrarTodaLaListaProducto(nodoListaProducto * lista)
{
    nodoListaProducto * actual=lista;

    while (lista!=NULL)
    {
        actual=lista;
        lista=lista->siguiente;
        free(actual);
    }
    return lista;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "productos.h"
#include "listaProductos.h"
#include "arbolProductos.h"


const char archivoProductos[]= {"productos.dat"};
const char archivoTemp[]= {"temp.dat"};
float costoPedido ()
{
    stProducto prod;
    char salida=0;
    int idProd=0,flag=0,cantProd=0;
    float costo=0;
    FILE *archi = fopen(archivoProductos, "rb");
    fseek(archi, 0,SEEK_SET);
    FILE *temp =fopen(archivoTemp, "wb");
    fseek(temp, 0, SEEK_SET);
    if (archi!=NULL)
    {
        printf("\n\n------>>>Lista de productos:\n\n");
        while (fread(&prod, sizeof(stProducto),1, archi)>0)
        {
            if(prod.productoAnulado!=1)
            {
                muestraProducto(prod);
            }
        }

        while (salida!=13)
        {
            do
            {
                fseek(archi,0,SEEK_SET);
                flag=0;
                printf("\nQue Nro de producto desea ordenar: ");
                scanf("%i", &idProd);
                while (flag==0 && fread(&prod,sizeof(stProducto),1,archi)>0)
                {
                    if(idProd==prod.idProducto && prod.productoAnulado!=1)
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    printf("\nProducto no disponible.\n");

                }

            }
            while(flag==0);

            prod.valor=buscarPrecio(prod.idProducto,archi);

            do
            {
                printf("Que cantidad desea ordenar: ");
                scanf("%i", &cantProd);
                if(cantProd>0)
                {
                    prod.cantidad=cantProd;
                }
                else
                {
                    printf("\nCantidad no valida\n");
                }
            }
            while(cantProd<=0);
            printf("\nPara ordenar mas productos presione cualquier tecla - ENTER para confirmar pedido...");
            salida=getch();
            fwrite(&prod, sizeof(stProducto), 1, temp);

        }
        fclose(temp);

        costo=calcularCosto();
    }
    fclose(archi);
    return costo;
}
float calcularCosto ()
{
    FILE * temp=fopen(archivoTemp, "rb");
    fseek(temp, 0, SEEK_SET);
    stProducto p;
    float aux=0;
    while(fread(&p, sizeof(stProducto), 1, temp)>0)
    {
        aux=(p.cantidad*p.valor)+aux;
    }
    fclose(temp);
    return aux;
}
void muestraProducto(stProducto p)
{
    printf("\nProducto Nro %i\t\n", p.idProducto);
    printf("%s",p.nombreProducto);
    printf("\n\nDescripcion:\t\t");
    printf("%s", p.descripcionProducto);
    printf("\n\n\t\t\t\t\t\tCosto: %.2f", p.valor);
    if (p.productoAnulado==1)
    {
        printf("\nStock=AGOTADO\n");
    }

    puts("\n----------------------------------------------------------------------------\n");
}
stProducto CargarProducto()
{
    stProducto producto;
    int idP=0;

    printf("\nIngrese nombre del producto: \n");
    fflush(stdin);
    gets(producto.nombreProducto);
    printf("Ingrese descripcion del producto: \n");
    fflush(stdin);
    gets(producto.descripcionProducto);
    printf("Ingrese valor del producto en pesos: \n");
    fflush(stdin);
    scanf("%f", &producto.valor);
    producto.productoAnulado=0;

    idP=cantidadProductos();
    producto.idProducto=idP+1;

    return producto;
}
int cantidadProductos()
{
    stProducto p;
    FILE *archiProd= fopen(archivoProductos,"rb");
    int cantProd=-1;

    if(archiProd!=NULL)
    {
        while(fread(&p, sizeof(stProducto), 1, archiProd))
        {
            cantProd++;
        }
    }
    fclose(archiProd);
    return cantProd;
}
void mostrarProductos()
{
    stProducto p;
    FILE * archiProd = fopen(archivoProductos, "rb");
    if(archiProd!=NULL)
    {
        while(fread(&p, sizeof(stProducto), 1, archiProd)>0)
        {
            muestraProducto(p);

        }
    }
    else
    {
        puts("\nEl arcivo no existe\n");
    }
    fclose(archiProd);
}
float buscarPrecio(int idProducto,FILE * archiProd)
{
    stProducto aux;
    float valor=0;
    fseek(archiProd, 0, SEEK_SET);
    while(fread(&aux,sizeof(stProducto),1,archiProd)>0)
    {
        if(idProducto==aux.idProducto)
        {
            valor=aux.valor;
        }
    }
    return valor;
}
stProducto anularProducto (int idProducto,FILE *  archiP)
{
    stProducto p;

    while(fread(&p, sizeof(stProducto), 1, archiP)>0)
    {
        if(idProducto==p.idProducto)
        {
            p.productoAnulado=1;
        }
    }
    if(p.productoAnulado==1)
    {
        printf(" \t \n Producto %i anulado con exito.\n\n", p.idProducto);
        system("pause");
    }
    else
    {
        if(fread(&p, sizeof(stProducto), 1, archiP)==0)
        {
            printf("\t \t \n No se encontro el producto");
            system("pause");
        }
    }
    fseek(archiP,(-1)*sizeof(stProducto), SEEK_CUR);
    return p;
}
void eliminarProductos()
{
    FILE * arch=NULL;
    arch=fopen(archivoProductos,"rb");

    printf("Ingrese el ID de producto a eliminar: ");
    int id=0,i=0;
    scanf("%i", &id);
    stProducto producto;

    FILE * nuevo=NULL;
    nuevo=fopen(archivoTemp,"wb");

    int existe=0;
    fread(&producto, sizeof(stProducto), 1, arch);
    while(!feof(arch))
    {
        if (id == producto.idProducto)
        {
            printf("Producto %i Eliminado: %s, valor:$%0.2f\n", producto.idProducto, producto.descripcionProducto, producto.valor);
            system("pause");
            existe=1;
        }
        else
        {
            producto.idProducto=i;
            fwrite(&producto, sizeof(stProducto), 1, nuevo);
            i++;
        }
        fread(&producto, sizeof(stProducto), 1, arch);
    }
    if (existe==0)
    {
        printf("No existe un producto con esta ID\n");
        system("pause");
    }
    fclose(arch);
    fclose(nuevo);

    remove(archivoProductos);
    rename(archivoTemp, archivoProductos);
}
void productoAnulado ()
{
    int idProd=0;
    FILE * archiProd = fopen(archivoProductos,"r+b");
    stProducto prod;
    fseek(archiProd,0,SEEK_SET);

    if (archiProd!=NULL)
    {
        printf("\nIngrese ID del producto a anular:");
        fflush(stdin);
        scanf("%d",&idProd);
        prod=anularProducto(idProd,archiProd);
        fwrite(&prod,sizeof(stProducto),1,archiProd);

    }
    fclose(archiProd);
}

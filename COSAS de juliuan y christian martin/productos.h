#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED


typedef struct
{
    int idProducto;
    char nombreProducto [30];
    char descripcionProducto [140];
    float valor;
    int cantidad;
    int productoAnulado;
} stProducto;

///FUNCIONES PEDIDO

float costoPedido ();
float calcularCosto ();
void muestraProducto (stProducto p);
stProducto CargarProducto();
int cantidadProductos();
void mostrarProductos();
float buscarPrecio(int idProducto,FILE * archiProd);
stProducto anularProducto (int idProducto,FILE *  archiP);
void productoAnulado ();
void eliminarProductos ();


#endif // PRODUCTOS_H_INCLUDED

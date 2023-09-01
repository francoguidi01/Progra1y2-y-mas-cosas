#include <stdio.h>
#include <stdlib.h>
/********************************* TIPOS *************************************/
typedef struct RegCategoria {
 char categoria;
 int escala;
 float porcentaje;
} Categoria;

typedef struct RegEmpleado {
 char categoria;
 int legajo;
 char * nombre;
 float sueldo;
} Empleado;

typedef struct NodoListaEmpleados {
 Empleado empleado;
 struct NodoListaEmpleados * sig;
} ListaEmpleados;

typedef struct RegArregloCategorias {
 Categoria categoria;
 ListaEmpleados * empleados;
} ArregloCategorias;

typedef struct NodoListaCategorias {
 Categoria categoria;
 ListaEmpleados * empleados;
 struct NodoListaCategorias * sig;
} ListaCategorias;

typedef struct NodoArbolCategorias {
 Categoria categoria;
 ListaEmpleados * empleados;
 struct NodoArbolCategorias * izq;
 struct NodoArbolCategorias * der;
} ArbolCategorias;

/*** TDA CATEGORIAS *************************************************************/
Categoria InicializarCategoria() {
 Categoria cat;
 cat.categoria = ' ';
 cat.escala = 0;
 cat.porcentaje = 0;
 return cat;
}
Categoria NuevaCategoria(char categoria, int escala, float porcen) {
 Categoria cat;
 cat.categoria = categoria;
 cat.escala = escala;
 cat.porcentaje = porcen;
 return cat;
}
void CargarCategoria(Categoria *categoria, char cat, int escala, float porcen) {
 (*categoria).categoria = cat;
 (*categoria).escala = escala;
 (*categoria).porcentaje = porcen;
}
void ImprimirCategoria(Categoria cat) {
 printf("\nCategoria: %c", cat.categoria);
 printf(" | Escala: %d", cat.escala);
 printf(" | Porcentaje: %.2f", cat.porcentaje);
}
/*** TDA EMPLEADOS ***************************************************************/
Empleado NuevoEmpleado(char cat, int legajo, char * nombre, float sueldo) {
 Empleado e;
 e.categoria = cat;
 e.legajo = legajo;
 e.nombre = nombre;
 e.sueldo = sueldo;
 return e;
}
void ImprimirEmpleado(Empleado e) {
 printf("\nEmpleado: %s", e.nombre);
 printf(" | Categoria: %c", e.categoria);
 printf(" | Legajo: %d", e.legajo);
 printf(" | Sueldo: %.2f", e.sueldo);
}
/*** TDA LISTA de EMPLEADOS ******************************************************/
ListaEmpleados * CrearNodo(Empleado e) {
 ListaEmpleados * nodo = (ListaEmpleados *) malloc(sizeof(ListaEmpleados));
 nodo->empleado = e;
 nodo->sig = NULL;
 return nodo;
}
ListaEmpleados * AgregarAlPpio(ListaEmpleados * lista, ListaEmpleados * nuevoNodo) {
 if (lista == NULL) {
 lista = nuevoNodo;
 }
 else {
 nuevoNodo->sig = lista;
 lista = nuevoNodo;
 }
 return lista;
}
void MostrarListaEmpleados(ListaEmpleados * lista) {
 ListaEmpleados * aux = lista;
 if (aux == NULL) {
 printf("\nSin Empleados");
 }
 else {
 while (aux != NULL) {
 ImprimirEmpleado(aux->empleado);
 aux = aux->sig;
 }
 }
}
/*** TDA LISTA de CATEGORIAS *****************************************************/
ListaCategorias * CrearNodoCategoria(Categoria cat) {
 ListaCategorias * nodo = (ListaCategorias *) malloc(sizeof(ListaCategorias));
 nodo->categoria = cat;
 nodo->empleados = NULL;
 nodo->sig = NULL;
 return nodo;
}
ListaCategorias * AgregarAlPpioListaCat(ListaCategorias * lista, ListaCategorias * nuevoNodo) {
 if (lista == NULL) {
 lista = nuevoNodo;
 }
 else {
 nuevoNodo->sig = lista;
 lista = nuevoNodo;
 }
 return lista;
}

void MostrarListaCategorias(ListaCategorias * lista) {
 ListaCategorias * aux = lista;
 if (aux == NULL) {
 printf("\nSin Categorias");
 }
 else {
 while (aux != NULL) {
 ImprimirCategoria(aux->categoria);
 MostrarListaEmpleados(aux->empleados);
 aux = aux->sig;
 printf("\n"); // paso a otra categoría
 }
 }
}
/*** MAIN *******************************************************************/
int main()
{
 ArregloCategorias a[100];
 a[0].categoria = InicializarCategoria();
 ImprimirCategoria(a[0].categoria);
 CargarCategoria(&a[0].categoria, 'A', 1, 100);
 ImprimirCategoria(a[0].categoria);
 printf("\n");
 Empleado e = NuevoEmpleado('A', 1, "Ramiro", 5000);
 ListaEmpleados * empleados;
 empleados = NULL;
 empleados = AgregarAlPpio(empleados, CrearNodo(e));
 empleados = AgregarAlPpio(empleados, CrearNodo(NuevoEmpleado('A', 2, "Jorge", 3000)));
 MostrarListaEmpleados(empleados);
 printf("\n");
 ListaCategorias * categorias;
 categorias = NULL;
 categorias = AgregarAlPpioListaCat(categorias, CrearNodoCategoria(NuevaCategoria('B', 2, 80)));
 categorias = AgregarAlPpioListaCat(categorias, CrearNodoCategoria(a[0].categoria));
 // la siguiente asignación se utiliza por la simplicidad del ejemplo (el TDA debería proveer
 // un método para cargar empleados o una lista completa de empleados validando que se ingresen
 // en la categoría correspondiente)
 categorias->empleados = empleados;
 MostrarListaCategorias(categorias);
 printf("\n\n¡Fin del programa!\n");
 return 0;
}

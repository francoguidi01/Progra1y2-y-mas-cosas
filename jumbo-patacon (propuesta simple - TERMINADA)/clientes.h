#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//#include "menu.h"
#include "listaPedidos.h"

typedef struct
{
    int idCliente;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[100];
    char genero;
    int rol;                      // 1: es admin - 0: es común
    int activo;                   // indica 1 o 0 si el cliente está activo
} stCliente;

typedef struct
{
    stCliente cliente;
    nodoListaProducto * listaDeProductos;
    float costoTotalDelPedido;
} stCelda;

int buscaPosUltima (stCelda adl[],int validos);
int buscaPosIdClienteCelda (stCelda adl[], int idCliente,int validos);
int agregarClienteCelda (stCelda adl[], stCliente cliente, int validos);

int agrandarAdl (stCelda ** adl, int validos, int dimesion);
int deArchivoAAdl (stCelda ADL[], char archivo []);
void mostrarAdlUser(stCelda adl[], int validos);
void mostrarAdlAdmin(stCelda adl[], int validos);
void deAdlAlArchivo(char archivoAPasar[], stCelda adl[], int validos);
void deAdlAlArchivoAlFinal(char archivoAPasar[], stCliente dato);
int darDeBajaODarDeAlta (stCelda adl[],int pos);
int darDeBajaUnUser (stCelda adl[],int posCliente);



void asteriscos (char contra[]);

void noExiste (int id);


void registrarse(stCelda** adl, int * validos, int *dimension);
int iniciarSesion(stCelda adl[],int validos);
int contarClientes(char archivoClientes[]);
void mostrarClienteAdmin(stCliente cliente);
void mostrarCliente(stCliente cliente);
void usuarioRepetido (int flag);
int compararUsuarios (stCelda adl[],char usuario[], int validos);
int compararPassword (stCelda adl[],char password[], int validos);
int verificacionEmail (char email[]);
void mailInvalido (int flag);
void modificarPassword(stCelda adl[],int posCliente);
void modificarEmail(stCelda adl[],int posCliente);
void modificarApellido(stCelda adl[],int posCliente);
void modificarNombre(stCelda adl[],int posCliente);


stPedido hacerPedidoMagicJohnson(stCelda adl[], nodoArbol * arbolProductos, int pos, int * ultimoIdPedido);

void deArchivoACabecera (stCelda adl[], char archivo [], int validos, int pos, nodoArbol * arbolProductos);
void deCabeceraAlArchivo(char archivoAPasar[], stPedido pedidoCliente);

void modificarChabonArchi (char archi[],stCliente dato);

#endif // CLIENTES_H_INCLUDED

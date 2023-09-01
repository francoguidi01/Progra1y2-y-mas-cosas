#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

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


#endif // CLIENTES_H_INCLUDED

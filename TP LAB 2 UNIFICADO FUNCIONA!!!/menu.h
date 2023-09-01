#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "clientes.h"

#define ESC 27
#define ENTER 13
#define FLECHAARRIBA 72
#define FLECHAABAJO 80
#define ARROBA 64

int menuConfiguracionDeUsuario (stCelda adl[],int validos, int idUser);
int menuUsuario (int elecion,stCelda adl[],int validos,int idUser);
int menuAdmin (int elecion,stCelda adl[],int validos,int idUser);
int puntosParaElegirPaso1 (int eleccion, int eleccionMenu, stCelda adl[], int * validos, int *dimension);
int sistemanavegableRegistrarse (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableIngresarOVolver (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableConfiguracionUsuario (int menu,int menuinicio,int menufin, int lineainicio);
int flechas (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAlta (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaAltaUnUser (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuBajaPedido (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuUsuario (int menu,int menuinicio,int menufin, int lineainicio);
int sistemanavegableMenuAdmin (int menu,int menuinicio,int menufin, int lineainicio);
void menuNavegable (stCelda adl[], int * validos, int * dimension);
void gotoxy (int x, int y);
void ejey (int y);
void  obtenerFecha(char F[],int dimension);
void logo();
void saltoDeLinea (int lineas);
void mensajeDespedida();


#endif // MENU_H_INCLUDED

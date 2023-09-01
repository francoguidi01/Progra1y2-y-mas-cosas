#ifndef STJUGADOR_H_INCLUDED
#define STJUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idJugador;
    char nombre[20];
    char apellido[20];
    char dni[10];
    int edad;
    char posicion[12];              /// Arquero, Defensa, Medio Campo, Delantero
    char equipo[30];
    int goles;
    float promedioDeGol;            /// indica el promedio de gol del jugador (en el torneo se jugaron 30 fechas)
} stJugador;

void replicante(char c, int n);
void mostrarUnRegistro(stJugador j);
void mostrarRegistros(char archivo[]);
void mostrarRegistrosMejorProm(char archivo[]);

#endif // STJUGADOR_H_INCLUDED

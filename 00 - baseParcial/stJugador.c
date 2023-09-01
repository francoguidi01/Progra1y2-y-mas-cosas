#include "stJugador.h"

void replicante(char c, int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%c",c);
    }
}

/// Se muestra un dato de tipo stJugador
void mostrarUnRegistro(stJugador j)
{
    printf("\n Id Jugador......................: %d",j.idJugador);
    printf("\n Nombre..........................: %s",j.nombre);
    printf("\n Apellido........................: %s",j.apellido);
    printf("\n DNI.............................: %s",j.dni);
    printf("\n Edad............................: %d",j.edad);
    printf("\n Posicion........................: %s",j.posicion);
    printf("\n Equipo..........................: %s",j.equipo);
    printf("\n Goles...........................: %d",j.goles);
    printf("\n Promedio de gol.................: %.2f\n",j.promedioDeGol);
    printf("-----------------------------------------------------------------------------------");
}

/// Se recorre el archivo y usando la funcion mostrarUnRegistro() se muestran los datos del archivo
void mostrarRegistros(char archivo[])
{
    stJugador j;
    FILE* pArchRegistro = fopen(archivo,"rb");
    if(pArchRegistro)
    {
        while(fread(&j,sizeof(stJugador),1,pArchRegistro)>0)
        {
            mostrarUnRegistro(j);
        }
        fclose(pArchRegistro);
    }
}

void mostrarRegistrosMejorProm(char archivo[])
{
    stJugador j;
    int i=0;
    FILE* pArchRegistro = fopen(archivo,"rb");
    if(pArchRegistro)
    {
        while(fread(&j,sizeof(stJugador),1,pArchRegistro)>0)
        {
            if(j.promedioDeGol>0.5){
                mostrarUnRegistro(j);
                i++;
            }
        }
        printf("total %d", i);

        fclose(pArchRegistro);
    }
}

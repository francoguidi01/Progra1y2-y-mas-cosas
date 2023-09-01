//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

int main()
{
    char arEspecie[20];
    int validos=50;
    int i =1;
    arEspecie[0]='\0';

    while(1)
    {


        strcat (arEspecie,"z");
        strcat (arEspecie,".dat");
        FILE* paArch = fopen(arEspecie, "ab");
        fwrite(&arEspecie, sizeof(char), 1, paArch);
        arEspecie[0]='z';
        arEspecie[i]='\0';
        fclose (paArch);
        i++;
   // printf("holaaa");


    }


    return 0;
}

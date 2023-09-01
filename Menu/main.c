#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

void menuNavegable (int menu,int menuinicio,int menufin, int lineainicio, int eleccion,int opcion);
int sistemanavegable (int menu,int menuinicio,int menufin, int lineainicio, int eleccion);
int siono (int menu,int menuinicio,int menufin, int lineainicio, int eleccion,int opcion);
void puntosParaElegir (int eleccion);
void ejey(int y);

int main()
{
    int menuy=0,elecciony=0,menuinicioy=0,menufiny=0,lineainicioy=0;
    int opciony=0;

   // menuNavegable(menuy,menuinicioy,menufiny,lineainicioy,elecciony,opciony);
    menuNavegable(0,0,5,3,0,6);

    return 0;
}

void menuNavegable (int menu,int menuinicio,int menufin, int lineainicio, int eleccion,int opcion)
{
    do
    {
        system("cls");
       // eleccion=sistemanavegable(menu,menuinicio,menufin,lineainicio,eleccion);
        eleccion=sistemanavegable(0,0,5,3,0);
        puntosParaElegir(eleccion);
///La linea de abajo era el error ahora esta bien
        //system("cls");
        //opcion=siono(menu,menuinicio,menufin,lineainicio,eleccion,opcion);
        opcion=siono(0,0,5,3,0,6);

    }
    while(opcion==1);

}

//int sistemanavegable (int menu,int menuinicio,int menufin, int lineainicio, int eleccion)
void sistemanavegable ()
{

    printf("\t\t\t*----------------------MENU----------------------*\n");

    printf("\t\t\t\t1-:D\n");
    printf("\t\t\t\t2-:C\n");
    printf("\t\t\t\t3-;S\n");
    printf("\t\t\t\t4-:o\n");
    printf("\t\t\t\t5-UwU\n");

    menu=1;
    menuinicio=1;
    menufin=5;
    lineainicio=1;

    ejey(lineainicio);
    printf("\t\t\t----->");


    while (1)
    {
        Sleep(100);
        if (GetAsyncKeyState(VK_UP))
        {
            menu=menu==menuinicio ? menufin: --menu;
            printf("\r                               ");
            ejey(lineainicio + menu-1);
            printf("\t\t\t----->");
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            menu=menu==menufin ? menuinicio: ++menu;
            printf("\r                               ");
            ejey(lineainicio + menu-1);
            printf("\t\t\t----->");
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            eleccion=menu;
            break;
        }
    }
}


int siono (int menu,int menuinicio,int menufin, int lineainicio, int eleccion,int opcion)
{

    printf("\t\t\t*----------------------Cancer Continuar?----------------------*\n");


    printf("\t\t\t\tSI\n");
    printf("\t\t\t\tNO\n");

    menu=1;
    menuinicio=1;
    menufin=2;
    lineainicio=2; ///Aca le puse un 2 en ves de un 1, entonces se ve bien
    opcion=0;

    ejey(lineainicio);

    printf("\t\t\t----->");

    while(1)
    {
        Sleep(100);

        if (GetAsyncKeyState(VK_UP))
        {
            menu=menu==menuinicio ? menufin: --menu;
            printf("\r                               ");
            ejey(lineainicio + menu-1);
            printf("\t\t\t----->");
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            menu=menu==menufin ? menuinicio: ++menu;
            printf("\r                               ");
            ejey(lineainicio + menu-1);
            printf("\t\t\t----->");
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            fflush(stdin);

            opcion=menu;
            break;
        }

    }
}
void puntosParaElegir (int eleccion)
{
    printf("\n\n\n\n");
    switch (eleccion)
    {
    case 1:
        system("cls");
        printf("\t\t\t*---------------------ALFONSIN--------------------*\n");

        break;
    case 2:
        system("cls");
        printf("\t\t\t*---------------------PATACON---------------------*\n"); ///puto el que lee

        fflush(stdin);
        break;
    case 3:
        system("cls");
        printf("\t\t\t*--------------------CORRALITO--------------------*\n");

        break;
    case 4:
        system("cls");
        printf("\t\t\t*----------------------MENEM----------------------*\n");

        break;
    case 5:
        system("cls");
        printf("\t\t\t*--------------Son las 2 ya me canse--------------*\n");

        break;
    default:
        printf("\t\t\t*-----------------:C#*#ERROR#*#:D-----------------\n*");

        break;
    }
    //system("pause");
}

void ejey (int y)
{
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X=0;
    pos.Y=y;

    SetConsoleCursorPosition(hConsole, pos);
}






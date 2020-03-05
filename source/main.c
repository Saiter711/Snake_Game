#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <unistd.h>
#include <conio.h>
#define DLUGOSC_POCZATKOWA 3

bool koniec_gry;
bool gracz = false;
int ogonX[800], ogonY[200];
int x, y, jablkoX, jablkoY, score, dlugosc_weza=DLUGOSC_POCZATKOWA;
typedef enum  {poczatek, gora, dol, lewo, prawo} kierunek_weza;
typedef enum {latwy, sredni, trudny} poziom;
poziom poziom_trudnosci;
kierunek_weza waz;
int q = 0;

// Funkcja do drukowania planszy na ekranie
void plansza(int szerokosc, int wysokosc, int a, int tabX[50], int tabY[50])
{
    system("cls");
    printf("\n");
    for(int i = 0;i < szerokosc;i++)
    {
        printf("%c",30);
    }
    printf("\n");
    for(int i = 0;i < wysokosc;i++)
    {
        for(int j = 0;j < szerokosc;j++)
        {
            if(j == 0 || j == szerokosc-1)
                printf("%c",30);
            else if(i == jablkoY && j == jablkoX)
            {
                printf("@");
            }
            else if(i == tabY[q] && j == tabX[q])
                printf("@");
            else
            {
                bool print = false;
                for(int k = 0;k < dlugosc_weza;k++)
                {
                    if(ogonX[k] == j && ogonY[k] == i)
                    {
                        printf("X");
                        print = true;
                    }
                }
                if(!print)
                    printf(" ");
            }
        }
        printf("\n");
    }
    for(int j = 0 ;j < szerokosc+1;j++)
        printf("%c",30);
    printf("\n");
    for(int j = 0 ;j < szerokosc/2;j++)
        printf(" ");
    printf("Dlugosc weza:%d", dlugosc_weza);
    int szybkosc_weza;
    if(poziom_trudnosci == latwy)
        szybkosc_weza = 100;
    else if(poziom_trudnosci == sredni)
        szybkosc_weza = 50;
    else if(poziom_trudnosci == trudny)
        szybkosc_weza = 10;
    Sleep(szybkosc_weza+ 100);
}
// Funkcja do poruszania siê weza
void zamiana(int szerokosc, int wysokosc, int tabX[50], int tabY[50])
{
    srand(time(NULL));
    int glowax = ogonX[0];
    int gloway = ogonY[0];

    // Zmienne tymczasowe potrzebne do zamiany wartoœci zmiennych
    int zmienna1, zmienna2;
    ogonX[0] = x;
    ogonY[0] = y;

    // Porusznie siê weza z ogonem
    for(int i = 1; i < dlugosc_weza;i++)
    {
        zmienna1 = ogonX[i];
        zmienna2 = ogonY[i];
        ogonX[i] = glowax;
        ogonY[i] = gloway;
        glowax = zmienna1;
        gloway = zmienna2;
    }
    switch(waz)
    {
        case gora:
            y--;
            break;
        case dol:
            y++;
            break;
        case lewo:
            x--;
            break;
        case prawo:
            x++;
            break;
    }

    // Sytuacja, gdy gracz nie kliknie nic (na poczatku)
    if(!gracz)
        y++;

    // Sprawdzenie czy nie wyjechalismy wezem za pole
    if(x < 0 || szerokosc < x+1 || y < 0 || wysokosc < y)
    {
        koniec_gry = true;
        system("cls");
        printf("\t\tKoniec gry :(\n");
        printf("\t\tWynik: %d", dlugosc_weza);
    }

    // Sprawdzenie czy waz zjadl owoc
    if(x == tabX[q] && y == tabY[q])
    {
        dlugosc_weza++;
        q++;
    }
    if(x == jablkoX && y == jablkoY)
    {
        dlugosc_weza++;
        q++;
        jablkoX = rand() % (szerokosc - 1) + 1;
        jablkoY = rand() % (wysokosc - 1) + 1;
    }

    // Sprawdzenie, czy waz nie zjada sam siebie
    for(int i = 0;i < dlugosc_weza;i++)
        if(x == ogonX[i] && y == ogonY[i])
        {
            koniec_gry = true;
            system("cls");
            printf("\t\tKoniec gry :(\n");
            printf("\t\tWynik: %d", dlugosc_weza);
        }
}

// Funkcja sluzaca do sterowania wezem
void sterowanie()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                {
                    if(waz == prawo)
                        waz = prawo;
                    else
                        waz = lewo;
                    gracz = true;
                    break;
                }
            case 'w':
                {
                    if(waz == dol)
                        waz = dol;
                    else
                        waz = gora;
                    gracz = true;
                    break;
                }
            case 's':
                {
                    if(waz == gora)
                        waz=gora;
                    else
                        waz = dol;
                    gracz = true;
                    break;
                }
            case 'd':
                {
                    if(waz == lewo)
                        waz= lewo;
                    else
                        waz = prawo;
                    gracz = true;
                    break;
                }
            default:
                break;
        }
    }
}

// Funkcja do wczytania danych poczatkowych
void dane_poczatkowe(int szerokosc, int wysokosc)
{
    srand(time(NULL));
    koniec_gry = false;
    waz = poczatek;
    x = szerokosc/2;
    y = wysokosc/2;
    jablkoX = rand() % (szerokosc - 1) + 1;
    jablkoY = rand() % (wysokosc - 1) + 1;
}

void napis_poczatkowy()
{
    printf("    XXXX  XX    X       X       X   X   XXXXXX \n");
    printf("    X     X X   X     X   X     X  X    XX \n");
    printf("    XXXX  X  X  X    X X X X    X X     XXXXXX \n");
    printf("       X  X   X X   X       X   X  X    XX \n");
    printf("    XXXX  X    XX  X         X  X   X   XXXXXX \n\n");

}
int main()
{
    int tabX[50], tabY[50];
    const int szerokosc, wysokosc;
    int a;
    napis_poczatkowy();
    printf("      Witaj w grze SNAKE - edycja konsolowa \n \nSTEROWANIE: Uzyj klawiszy A W S D, aby poruszac sie wezem. ");
    printf("    Znaki @ to owoce, ktore musisz zbierac. \nPowodzenia :) \n\n");
    printf("Jakie wymiary ma miec plansza? (zalecane 20 na 10): ");
    scanf("%d%d", &szerokosc, &wysokosc);
    printf("\nJaki poziom trudnosci?\n 0 - Latwy \n 1 - Sredni \n 2 - Trudny ");
    scanf("%d", &poziom_trudnosci);
    printf("    Wcisnij dowolny klawisz by rozpoczac\n");
    getch();

    dane_poczatkowe(szerokosc, wysokosc);
    plansza(szerokosc,wysokosc,a,tabX,tabY);
    while(!koniec_gry)
    {
        plansza(szerokosc,wysokosc,a,tabX,tabY);
        sterowanie();
        zamiana(szerokosc, wysokosc,tabX,tabY);
    }

    return 0;
}

#include <iostream>
#include <cstdlib>
#include<stdio.h>
using namespace std;

static const int TAB_WYSOKOSC = 11;
static const int TAB_SZEROKOSC = 23;
static const int GORA = 0;
static const int PRAWO = 1;
static const int DOL = 2;
static const int LEWO = 3;

char tab[TAB_WYSOKOSC][TAB_SZEROKOSC];

void ResetujTab()
{
    for (int x=0; x<TAB_WYSOKOSC; x++)
    {
        for(int y = 0; y<TAB_SZEROKOSC; y++)
        {
            tab[x][y] = '#';
        }
    }
}

bool JestWGranicach(int x, int y)
{
    if(x >= 0 && x < TAB_WYSOKOSC && y >= 0 && y < TAB_SZEROKOSC)
    {
        return true;
    }
    return false;
}

void PrintTab()
{
    for (int x=0; x<TAB_WYSOKOSC; x++)
    {
        for (int y=0; y<TAB_SZEROKOSC; y++)
        {
            cout << tab[x][y];
        }
        cout << endl;
    }
}

void PrintTab1()
{
    for (int x=0; x<TAB_WYSOKOSC; x++)
    {
        for (int y=0; y<TAB_SZEROKOSC; y++)
        {
            if(tab[x][y] == '1'){
                tab[x][y] = ' ';
            }
        }
    }
}

void StworzLabirynt(int x, int y)
{
    tab[x][y] = ' ';
    int dir[4];
    dir[0] = GORA;
    dir[1] = PRAWO;
    dir[2] = DOL;
    dir[3] = LEWO;

    //pomieszaj tablice dir
    for (int i=0; i<4; ++i)
    {
        int r = rand() % 4; //dowolny numer od 0 do 3
        int temp = dir[r]; //wybierz dowolne miejsce z tablicy i swap
        dir[r]  = dir[i];
        dir[i]  = temp;
    }

    //sprobuj pojsc w kazda strone
    for (int i=0; i<4; ++i)
    {
        //dx, dy to zmienne chwilowe, potrzebne do ruchu
        int dx = 0;
        int dy = 0;
        switch (dir[i])
        {
            case GORA:
                dy = -1;
                break;
            case DOL:
                dy =  1;
                break;
            case PRAWO:
                dx =  1;
                break;
            case LEWO:
                dx = -1;
                break;
        }
        // przechodze od 2 miejsca w wybrana strone, zeby nie wyjsc poza tablice (na krancach)
        int x2 = x + (dx*2);
        int y2 = y + (dy*2);
        if (JestWGranicach(x2,y2))
        {
            if (tab[x2][y2] == '#')
            {
                // jezeli na x2, y2 jest sciana, to usun sciane pomiedzy (x,y) a (x2,y2)
                tab[x2 - dx][y2 - dy] = ' ';
                //Wykonaj funkcje rekurencyjnie
                StworzLabirynt(x2,y2);
            }
        }
    }
}

bool przeszukajLabirynt(int x, int y)
{
    tab[x][y] = '1';
    //Jezeli dojdzie do mety, return true
    if(x == (TAB_WYSOKOSC-2) && y == (TAB_SZEROKOSC-2))
    {
        tab[x][y] = '.';
        return true;
    }

    //sprobuj pojsc w kazda strone
    for (int i=0; i<4; ++i)
    {
        //dx, dy to zmienne chwilowe, potrzebne do ruchu
        int dx = 0;
        int dy = 0;
        switch (i)
        {
            case 0:
                dy = -1;
                break;
            case 1:
                dy =  1;
                break;
            case 2:
                dx =  1;
                break;
            case 3:
                dx = -1;
                break;
        }

        int x2 = x + dx;
        int y2 = y + dy;
        if (JestWGranicach(x2,y2))
        {
            if (tab[x2][y2] == ' ')
            {
                //Wykonaj funkcje rekurencyjnie
                bool b = przeszukajLabirynt(x2, y2);
                if (b)
                {
                    tab[x2][y2] = '.';
                    return true;

                }
            }
        }
    }
    return false;
}

int main()
{
    srand(time(0));
    ResetujTab();
    StworzLabirynt(1,1);
    PrintTab();
    cout << endl << endl << "\".\" - rozwiazanie, \"_\" - sprawdzone sciezki" << endl << endl;
    if(przeszukajLabirynt(1, 1) == false) {
        printf("Brak rozwiazania\n");
        tab[0][1] = ' '; //start
        tab[TAB_WYSOKOSC-1][TAB_SZEROKOSC-2] = ' '; //meta
    } else {
        tab[1][1] = '.';
        tab[0][1] = '.'; //start
        tab[TAB_WYSOKOSC-1][TAB_SZEROKOSC-2] = '.'; //meta
    }

    PrintTab1();
    PrintTab();
    return 0;
}

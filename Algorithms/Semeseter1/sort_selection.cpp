#include<iostream>
#include <cstdlib>
#include<stdio.h>
#include <ctime>
#define N 100
using namespace std;

int liczbaOperacji = 0;

void sort_selection(int tab[])
{

    for (int i = 0; i < N-1; i++)
    {
        int min = i;
        for(int j=i+1; j<N; j++)
        {
            liczbaOperacji++;
            if (tab[j] < tab[min])
            {
                min = j;
            }
        }
        int temp = tab[min];
        tab[min] = tab[i];
        tab[i] = temp;
    }
}

int main()
{
    int tab1[N]; //losowa
    int tab2[N]; //posortowana malejąco
    int tab3[N]; //posortowana rosnąco
    srand((int)time(0));

    //wpisz dane do tabic
    for(int i=0;i<N;i++)
    {
        //losowa od 0 do 1000
        int r1 = rand() % 1000 + 1;
        tab1[i] = r1;

        //posortowana malejaco od 0 do 1000
        int r2 = ((99-i)*10) + ( rand() % ( (1000-(i*10)) - ((99-i)*10) + 1 ) );
        tab2[i] = r2;

        //posortowana rosnaco od 0 do 1000
        int r3 = ((99-i)*10) + ( rand() % ( (1000-(i*10)) - ((99-i)*10) + 1 ) );
        tab3[N-i-1] = r3;
    }

    sort_selection(tab1);
    cout<< "Tablica losowa: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab1[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl << endl;

    liczbaOperacji = 0;
    sort_selection(tab2);
    cout<< "Tablica posortowana malejaco: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab2[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl << endl;

    liczbaOperacji = 0;
    sort_selection(tab3);
    cout<< "Tablica posortowana rosnaco: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab3[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl;

    return 0;
}

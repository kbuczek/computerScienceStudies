#include<iostream>
#include <cstdlib>
#include<stdio.h>
#include <ctime>
#define N 100
using namespace std;

int liczbaOperacji = 0;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        liczbaOperacji++;
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    quickSort(tab1, 0, N - 1);
    cout<< "Tablica losowa: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab1[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl << endl;

    liczbaOperacji = 0;
    quickSort(tab2, 0, N - 1);
    cout<< "Tablica posortowana malejaco: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab2[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl << endl;

    liczbaOperacji = 0;
    quickSort(tab3, 0, N - 1);
    cout<< "Tablica posortowana rosnaco: " << endl;
    for(int i=0; i < N; i++)
    {
        cout << tab3[i] << " ";
    }
    cout << endl << "Liczba operacji: " << liczbaOperacji << endl;
}

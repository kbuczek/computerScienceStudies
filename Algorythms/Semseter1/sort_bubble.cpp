#include<iostream>
#include<cstdlib>
#define N 5
using namespace std;

void sortowanie_babelkowe_it(int tab[])
{
    for(int i=0;i<N;i++)
    {
        for (int j = 1; j < N - i; j++)
        {
            if (tab[j - 1] > tab[j])
            {
                int temp = tab[j];
                tab[j] = tab[j - 1];
                tab[j - 1] = temp;
            }
        }
    }
}

void sortowanie_babelkowe_rek(int tab[], int size)
{
    if(size == 0)
    {
        return;
    }
    for (int i = 0; i < size - 1; i++)
    {
        if (tab[i] > tab[i + 1])
        {
            int temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
        }
    }

    sortowanie_babelkowe_rek(tab, size-1);
}

int main()
{
    int tab[N];

    for(int i=0;i<N;i++)
    {
        cin >> tab[i];
    }

    //sortowanie_babelkowe_it(tab);
    sortowanie_babelkowe_rek(tab, N);

    for(int i=0; i < N; i++)
    {
        cout << tab[i] << " ";
    }

    cout << endl;
    return 0;
}
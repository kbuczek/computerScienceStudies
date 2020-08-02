#include <iostream>
using namespace std;

int main(){
    int tab[7];
    tab[0] = 7; tab[1] = 5; tab[2] = 9; tab[3] = 6; tab[4] = 7; tab[5] = 8; tab[6] = 10;

    //tworzenie kopca
    for(int i = 1; i < 7; i++)
    {
        int k = i;
        while(k > 0)
        {
            if(tab[k] > tab[(k-1)/2])
            {
                int temp = tab[k];
                tab[k] = tab[(k-1)/2];
                tab[(k-1)/2] = temp;
            }
            k = (k-1)/2;
        }
    }

    cout << "Utworzony kopiec: " << endl;
    for(int i = 0; i < 7; i++)
    {
        cout << tab[i] << endl;
    }

    //rozbiurka kopca
    for(int i = 6; i < 7; i--)
    {
       // tab[];
    }
    return 0;
}

#include <iostream>
#include <cmath>

int bin_to_dec(std::string bin)
{
    int dec = 0;
    for(int i = 0; i < bin.length() ; i++)
    {
        if(bin[i] == '1')
        {
            dec += pow(2, bin.length()-1 - i);
        }
    }
    return dec;
}

void dec_to_ter(int dec)
{
    int tab[30], i = 0;

    while(dec)
    {
        tab[i] = dec % 3;
        dec = dec / 3;
        i++;
    }

    for(int k = i-1; k >= 0; k--)
    {
        std::cout << tab[k];
    }
}

int main() {
    std::string bin;
    std::cin >> bin;
    int dec = bin_to_dec(bin);

    std::cout << "dziesietny: " << dec << std::endl;
    std::cout << "trojkowy: ";
    dec_to_ter(dec);
    return 0;
}
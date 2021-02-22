#include <iostream>

double power_it(double x, double y)
{
    double result = 1;
    for(int i = 1; i <= y; i++)
    {
            result *= x;
    }
    return result;
}

double power_rek(double x, double y)
{
    if(y == 0)
    {
	return 1;
    }
    else
    {
        return x = x * power_rek(x, y-1);
    }
}

double power_param(double x, double y, double res = 1)
{
    if(y == 0)
    {
	return res;
    }
    else
    {
        return power_param(x, y-1, x * res);
    }
}

int main()
{
    double a, b;
    std::cout << "liczba pierwiastkowana: ";
    std::cin >> a;
    std::cout << std::endl << "do potegi: ";
    std::cin >> b;
    if(b == 0)
    {
        std::cout << "wynik: " << 1;
        return 0;
    }
    std::cout << std::endl << "wynik_it: " << power_it(a, b);
    std::cout << std::endl << "wynik_rek: " << power_rek(a, b);
    std::cout << std::endl << "wynik_param: " << power_param(a, b);
    return 0;
}

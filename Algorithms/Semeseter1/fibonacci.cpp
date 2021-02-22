#include <iostream>

double fib_rek(double n) // rekurencyjna
{
    std::cout << "n:" << n << std::endl;
    return n < 2 ? n : fib_rek(n - 1) + fib_rek(n - 2);

}

double fib_it(double n) // iteracyjna
{
    int x0 = 0;
    int x1 = 1;

    for(int i = 0; i < n; ++i)
    {
        int temp = x0 + x1;
        x0 = x1;
        x1 = temp;
        std::cout<<"x0:" << x0 << " x1:" << x1 << std::endl;
    }
    return x0;
}

int main()
{
    double a;
    std::cin >> a;
    //double f = fib2(a);
    //double x = fib(a);
    std::cout << "iteracyjna" << std::endl;
    std::cout << fib_it(a) << std::endl;
    std::cout << "rekurencyjna" << std::endl;
    std::cout << fib_rek(a) << std::endl;
    return 0;
}

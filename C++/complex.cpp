#include <cmath>
#include <iostream>

class Complex
{
    friend double getAbs(const Complex &);
    public:
    Complex(double a, double b) { re = a; im = b; };
    Complex(double a) { re = a; im = 0; };
    Complex() { re = 0;  im = 0; };
    private:
    double re, im;
};

double getAbs(const Complex& c)
{
    return sqrt(pow(c.re, 2) + pow(c.im, 2));
}

int main(void)
{
    Complex c1(3, 1); //postać skrócona
    Complex c2 = Complex(4); // postać jawna
    Complex c3;
    std::cout << getAbs(c1) << std::endl;
    std::cout << getAbs(c2) << std::endl;
    std::cout << getAbs(c3) << std::endl;
    return 0;
}

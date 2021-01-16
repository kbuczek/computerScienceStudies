#include <iostream>
#include <cmath>
using namespace std;

const double pktX = 0.3;

double functionA(double x, double h){
    return ((cos(x+h) - cos(x))/h);
}

double functionB(double x, double h){
    return ((cos(x+h) - cos(x-h))/(2*h));
}

int main() {
    double fA, fA_blad, fB, fB_blad;
    double hMinA = 2, bladMinA = 2;
    double hMinB = 2, bladMinB = 2;

	for (double h = 1e-16; h <= 1; h *= 1.01)
	{
        // printf("h: %.30lf\n", h);
        fA = functionA(pktX, h);
        fA_blad = abs(fA + sin(pktX));
        fB = functionB(pktX, h);
        fB_blad = abs(fB + sin(pktX));

	printf("Funkcja A, wartosc h = %.30lf , wartosc bledu = %.30lf\n\n", h, fA_blad);
    printf("Funkcja B, wartosc h = %.30lf , wartosc bledu = %.30lf\n\n", h, fB_blad);

		
		if (bladMinA > fA_blad)
		{
        printf("bladMinA = %.30lf, hMinA = %.30lf\n", bladMinA, hMinA);
		bladMinA = fA_blad;
		hMinA = h;
		}

        if (bladMinB > fB_blad)
		{
        printf("bladMinB = %.30lf, hMinB = %.30lf\n", bladMinB, hMinB);
		bladMinB = fB_blad;
		hMinB = h;
		}

	}
    printf("Funkcja A, optymalna wartosc h = %.30lf , wartosc bledu minimalnego = %.30lf\n\n", hMinA, bladMinA);
    printf("Funkcja B, optymalna wartosc h = %.30lf , wartosc bledu minimalnego = %.30lf\n\n", hMinB, bladMinB);

    return 0;
}
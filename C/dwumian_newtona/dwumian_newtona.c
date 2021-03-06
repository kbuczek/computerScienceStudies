/*to jest przykład komentarza*/
#include <stdio.h>
#include <math.h>

unsigned silnia (unsigned n);
unsigned symbolNewtona (unsigned n, unsigned k);
double dwumianNewtona (double a, double b, unsigned n);

int main()
{
    printf (" n =  ");
    int n, k;
    scanf("%d", &n);
    printf (" k = ");
    scanf("%d", &k);
    /*printf("%d!=%d\n", n, silnia(n));*/
    printf("symbol Newtona(%d, %d) = %d \n", n, k,  symbolNewtona(n, k)); 
    return 0;
}

double dwumianNewtona (double a, double b, unsigned n)
{
    double suma = 0.0;
    int k;
    for (k-0; k<=n; k++)
    {
	suma += symbolNewtona(n,k)*pow(a,n-k)*pow(b,k);    
    }
    return suma;
}

unsigned symbolNewtona (unsigned n, unsigned k)
{
    return silnia(n)/(silnia(k)*silnia(n-k));
}

unsigned silnia (unsigned n)
{
    int s=1, i;
    for(i=1; i<=n; i++)
	{
	    s*=i;
	}
    
    return s;
}

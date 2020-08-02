#include <stdio.h>
#include <math.h>

int main()
{
	
   	int n, k = 1;
   	double x, l = 0, p = 0;
   	double sin(double x);
   	printf (" n =  ");
	scanf("%d", &n);
	printf (" x = ");
	scanf("%lf", &x);
	p = sin((n+1)*(x/2))*sin((n*x)/2)/sin(x/2);
	while(k <= n)
	{
		
		l += sin(x*k);
		k++;
		
	}
	printf("prawa strona = %lf\n", p);
	printf("lewa strona = %lf\n", l);
	if (p==l)
	{
		printf("Prawa = Lewa\n");
	}
	else
	{
		printf("Prawa != Lewa\n");
	}
}


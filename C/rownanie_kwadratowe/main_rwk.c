#include <stdio.h>

int rownanieKwadratowe (double, double, double, double*, double*);

int main()
{
	double a, b, c;
	printf("Podaj parametry równania kwadratowego:");
	printf("a = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	printf("c = ");
	scanf("%lf", &c);
	printf("Podane parametry to: a=%lf, b=%lf, c=%lf \n", a, b, c);
	
	double x1, x2;
	int n = rownanieKwadratowe( a, b, c, &x1, &x2);
	if (n == 0)
	{
		printf("Równanie nie ma pierwastków \n");
	}
	if (n == 1)
	{
		printf("Równanie ma jeden pierwiastek: x1 = %lf \n", x1);
	}
	if (n == 2)
	{
		printf("Rówanie ma dwa pierwiastki: x1 = %lf, x2 = %lf \n", x1, x2);
	}
}


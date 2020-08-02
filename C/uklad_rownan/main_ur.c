#include <stdio.h>

int uklad2 (double [][2], double [], double []);

main()
{
	double a[2][2];
	double b[2];
	double x[2];
	printf("podaj uklad rownan porstaci: \n");
	printf("a11x + a12y = b1 \n");
	printf("a21x + a22y = b2 \n");
	scanf("%lfx %lfy = %lf", &a[0][0], &a[0][1], &b[0]);
	scanf("%lfx %lfy = %lf", &a[1][0], &a[1][1], &b[1]);
	
	int n = uklad2(a, b, x);
	if (n == 0)
	{
		printf("Układ równań jest sprzeczny.\n");
	}
	if (n == 1)
	{
		printf("Układ równań ma rozwiązanie: x1=%lf, x2=%lf", x[0], x[1]);
	
	}
	if (n > 2)
	{
		printf("Układ równań ma nieskończenie wiele rozwiązań.\n");
	}

}




#include <stdio.h>
#include <math.h>

int wyznacznik (double  a[][2])
{
	return a[0][0] * a[1][1] - a[1][0] * a[0][1];
}

int uklad2 (double a[][2], double b[], double x[])
{	
	double w = wyznacznik(a);
	double t[2][2];
	t[0][0] = b[0];
	t[1][1] = a[1][1];
	t[1][0] = b[1];
	t[0][1] = a[0][1];
	double w1 = wyznacznik(t);
	t[0][0] = a[0][0]; 
	t[1][1] = b[1];
	t[1][0] = a[1][0];
	t[0][1] = b[0];
	double w2 = wyznacznik(t);
	
	if(w != 0.0)
	{
		x[0] = w1/w;
		x[1] = w2/w;
		return 1;
	}
	if(w1 == 0.0 && w2 == 0)
	{
		return 99;
	}
	return 0;
}

#include <stdio.h>
#include <math.h>

int rownanieKwadratowe (double a, double b, double c, double*x1, double *x2)
{
	double delta=b*b-4*a*c;
	if (delta < 0.0)
	{
		return 0;
	} 
	if (delta == 0.0)
	{
		*x1 = -b/(2*a);
		return 1;
	}
	delta = sqrt(delta);
	*x1 = (-b-delta)/(2*a);
	*x2 = (-b+delta)/(2*a);
	return 2;
}

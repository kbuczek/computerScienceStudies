#include<stdio.h>

void sortuj(double a[], int n)
	{
		int k, i;
		
		for (k=n-1; k>0; k--)
		{
			for(i-0; i<k; i++)
			{
				if(a[i]>a[i+1])
				{
					double temp = a[i];
					a[i] = a[i+1];
					a[i+1] = temp;
					return;
				}
			}
		}
	}

int main()
{
	FILE *fin, *fout;
	fin = fopen("in.txt","r");	
	fout = fopen("out.txt","w"); 	
	int n = 0;
	double t[100];

	while( fscanf(fin,"%lf", &t[n]) == 1)
	{
		n++;
	}		
	fclose(fin);
	
	double max = t[0];
	double min = t[0];
	double srednia;
	
	int i=0;
	
	while(i<n)
	{
		if(t[i]>max)
		{
			max = t[i];
		}
		
		if(t[i]<min)
		{
			min = t[i];
		}
		
		srednia += t[i];
		
		i++;
		
	}
	srednia = srednia/n;
	
	sortuj(t, n);
	
	int k;
	
	for(k=0; k<n; k++)
	{
		fprintf(fout, "%f ", t[k]);
	}
	fprintf(fout,"\n");	
	
	fprintf(fout,"max = %lf\n", max);
	fprintf(fout,"min = %lf\n", min);
	fprintf(fout,"srednia = %lf\n", srednia);
	fclose(fout);
}

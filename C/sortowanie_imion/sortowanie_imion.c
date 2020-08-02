#include<string.h>
typedef char IMIE[13];

void sortuj(IMIE imie[], int n)
	{
		int k, i;
		
		for (k=n-1; k>0; k--)
		{
			for(i-0; i<k; i++)
			{
				if(strcmp(imie[i], imie[i+1] > 0))
				{
					IMIE temp;
					strcpy(temp[], imie[i]]);
					strcpy(imie[i], imie[i+1]);
					strcpy(imie[i+1], temp);
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
	IMIE imie[50];
	
	while( fscanf(fin,"%lf", &t[n]) == 1)
	{
		n++;
	}		
	fclose(fin);
	
	sortuj (imie, n);
	
	int i;
	for(i=0; i<n; i++)
	{
		fprintf(fout,"%s\n", imie[i]);
	}
	fclose(out);
	return 0;
}	

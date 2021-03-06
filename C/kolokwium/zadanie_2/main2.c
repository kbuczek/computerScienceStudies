#include<stdio.h>

typedef struct Liczby LICZBY;

struct Liczby
{
	int pierwsza;
	int druga;
	int trzecia;
};

int wczytajLiczby(FILE *fin, LICZBY liczby[])
{
	int n = 0;
	while(fscanf(fin,"%d %d %d", &liczby[n].pierwsza, &liczby[n].druga, &liczby[n].trzecia)==3)
	{
		n++;
	}
	return n;
}

void sortuj(LICZBY l[], int n, int (por)(LICZBY, LICZBY))
{
	int i, k;
	for(k = n-1; k > 0; k--)
	{
		for(i = 0; i < k; i++)
		{
			if(por(l[i], l[i+1]) > 0)
			{
				LICZBY temp = l[i];
				l[i] = l[i+1];
				l[i+1] = temp;
			}
		}
	}
	return;
}

int porownajLiczby(LICZBY l1, LICZBY l2)
{
	int n = l1.pierwsza - l2.pierwsza;
	if(n != 0) return n;
	n = l1.druga - l2.druga;
	if(n != 0) return n;
	n = l1.trzecia - l2.trzecia;
	if(n != 0) return n;
	return 0;
}

int main()
{
	FILE *fin, *fout;
	fin = fopen("in.txt", "r");
	fout = fopen("out.txt","w");
	LICZBY liczby[100];
	int n = wczytajLiczby(fin, liczby);
	
	sortuj(liczby, n, porownajLiczby);
	int i;
	//wypisz liczby
	for(i=0; i<n; i++)
	{
		fprintf(fout,"%d %d %d\n", liczby[i].pierwsza, liczby[i].druga, liczby[i].trzecia);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}

#include<stdio.h>
#include <string.h>

struct Osoba
{
	char imie[15];
	char nazwisko[20];
	int wiek;
	double zarobki;
};

typedef struct Osoba OSOBA;

int wczytajosoby(FILE *fin, OSOBA osoba[])
{
	int n = 0;
	while(fscanf(fin,"%s %s %d %lf", osoba[n].imie, osoba[n].nazwisko, &osoba[n].wiek, &osoba[n].zarobki)==4)
	{
		n++;
	}
	return n;
}

void wypiszosoby(OSOBA osoba[], int n)
{
	int i;
	printf("|	Imie	|	Nazwisko	|	Wiek	|	Zarobki	|\n");
	printf("_____________________________________________________\n");
	for(i = 0; i < n; i++)
	{
		int id = strlen(osoba[i].imie);
		int nd = strlen(osoba[i].nazwisko);
		int wd = sizeof(osoba[i].wiek);
		printf("| %-10s | %-10s | %4d | %10.2f |\n", osoba[i].imie, osoba[i].nazwisko, osoba[i].wiek, osoba[i].zarobki);
		printf("_____________________________________________________\n");
	}
	return;
}

int porownajosobyniwz(OSOBA os1, OSOBA os2)
{
	int n = strcmp(os1.nazwisko, os2.nazwisko);
	if(n != 0) return n;
	n = strcmp(os1.imie, os2.imie);
	if(n != 0) return n;
	n = os1.wiek - os2.wiek;
	if(n != 0) return n;
	return (int)100*(os1.zarobki - os2.zarobki);
}

void sortuj(OSOBA os[], int n, int (por)(OSOBA, OSOBA))
{
	int i, k;
	for(k = n-1; k > 0; k--)
	{
		for(i = 0; i < k; i++)
		{
			if(por(os[i], os[i+1]) > 0)
			{
				OSOBA temp = os[i];
				os[i] = os[i+1];
				os[i+1] = temp;
			}
		}
	}
	return;
}

/*void dodajosobe()
{
    FILE *fin = fopen("dane.txt", "w");
    OSOBA strIn[100];
	printf("Dodaj osobe w kolejności: imie, nazwisko, wiek, zarobki\n");
	strcat(fin, "\n");
	scanf("%s", strIn);
	strcat(fin, strIn);
	n = wczytajosoby(fin, strIn);
	fclose(out);
	wypiszosoby(osoba, n);
	sortuj(osoba, n, porownajosobyniwz);
	return;
}*/

/*void usunosobe() 
{
	
}*/

int main()
{
	FILE *fin;
	fin = fopen("dane.txt", "r");
	OSOBA osoba[100];
	int n = wczytajosoby(fin, osoba);
	printf("wczytano dane %d osob \n", n);
	fclose(fin);
	sortuj(osoba, n, porownajosobyniwz);
	wypiszosoby(osoba, n);
	//dodajosobe();
	//usunosobe();
	return 0;
}

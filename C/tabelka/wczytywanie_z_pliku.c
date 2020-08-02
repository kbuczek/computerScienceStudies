#include <stdio.h>
#include <string.h>
typedef struct
{
	int id;
	char imie[15];
	char nazwisko[15];
	int wiek;
	double zarobki;
} Osoba;

int wczytaj_z_pliku()
{

    Osoba tablica[50];

    FILE *fin = fopen("osoby.txt", "r");

int n = 0;
while(fscanf(fin, "%s %s %d %lf", tablica[n].imie, tablica[n].nazwisko, &tablica[n].wiek, &tablica[n].zarobki  ) == 4) n++;

fclose(fin);

FILE *fout = fopen("imiona_out.txt", "w");

int i;
for (i=0; i<n; i++) fprintf(fout, "%d %s %s %d %lf \n", i+1, tablica[i].imie, tablica[i].nazwisko, tablica[i].wiek, tablica[i].zarobki );

fclose(fout);

printf("Czytano %i osob \n", i);
return 0;

}

int wypisz_tabelke()
{
    Osoba tablica[50];

    FILE *fin = fopen("imiona_out.txt", "r");


    int n = 0;

    while(fscanf(fin, "%d %s %s %d %lf", &tablica[n].id, tablica[n].imie, tablica[n].nazwisko, &tablica[n].wiek, &tablica[n].zarobki  ) == 5) n++;

    fclose(fin);

   FILE *fout = fopen("imiona_out_tabelka.txt", "w");

    fprintf(fout, " \n \t%7s\t || \t%-10s\t || \t%-10s\t || \t%-10s\t || \t%-10s\t  \n =============================================================================================\n", "ID", "Imie", "Nazwisko", "Wiek", "Zarobki");

    int i;

    for (i=0; i<n; i++) fprintf(fout, "\t%7i\t || %-10s\t \t || %-10s\t \t || \t%10d\t || \t%10.2lf\t  \n =============================================================================================\n", tablica[i].id, tablica[i].imie, tablica[i].nazwisko, tablica[i].wiek, tablica[i].zarobki );

    fclose(fout);

   // int id = tablica[3].id;

   // printf("ID = %d \n", id);

    printf("Tabelka wypisana w pliku imiona_out_tabelka \n");

    return 0;
}

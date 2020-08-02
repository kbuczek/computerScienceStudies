
#include <stdio.h>
#include <string.h>

typedef struct OSOBY{
    int id;
    char imie[15];
    char nazwisko[15];
    int wiek;
    double zarobki;
} Osoba;

void dodaj_osobe_do_tablicy(char imie[80], char nazwisko[80], int wiek, float zarobki)
    {
    Osoba tablica[50];

    FILE *fin = fopen("imiona_out.txt", "r");


    int n = 0;

    while(fscanf(fin, "%d %s %s %d %lf", &tablica[n].id, tablica[n].imie, tablica[n].nazwisko, &tablica[n].wiek, &tablica[n].zarobki  ) == 5) n++;

    fclose(fin);


    FILE *fout = fopen("imiona_out.txt", "w");

    int i;

    for (i=0; i<n; i++) fprintf(fout, "%d %s %s %d %lf \n", tablica[i].id, tablica[i].imie, tablica[i].nazwisko, tablica[i].wiek, tablica[i].zarobki );


    fprintf(fout, "%d %s %s %d %lf \n", i+1, imie, nazwisko, wiek, zarobki);

    fclose(fout);
}


void dodaj_osobe() {

    char imie[80];
    char nazwisko[80];
    int wiek;
    float zarobki;

    printf("Podaj imie \n");

    scanf("%s", &imie);

    printf("\n Podaj nazwisko \n");

    scanf("%s", &nazwisko);

    printf("\n Podaj wiek \n");

    scanf("%d", &wiek);

    printf("\n Podaj zarobki\n");

    scanf("%f", &zarobki);

    dodaj_osobe_do_tablicy(imie, nazwisko, wiek, zarobki);

    printf("\n Dodano osobe %s %s do tablicy. \n", imie, nazwisko);

    main();

}

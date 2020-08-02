#include <stdio.h>
#include <string.h>

typedef struct OSOBY{
    int id;
    char imie[15];
    char nazwisko[15];
    int wiek;
    double zarobki;
} Osoba;


void usun_osobe(int id)
    {
    Osoba tablica[50];

    FILE *fin = fopen("imiona_out.txt", "r");


    int n = 0;

    while(fscanf(fin, "%d %s %s %d %lf", &tablica[n].id, tablica[n].imie, tablica[n].nazwisko, &tablica[n].wiek, &tablica[n].zarobki  ) == 5) n++;

    fclose(fin);

    int j = 0;

    int msc_w_tablicy_loop(){
        for (j=0; j<n; j++) {

            if (id == tablica[j].id) {

                return j;
                break;

            }

        }
    }

    int msc_w_tablicy = msc_w_tablicy_loop();

    printf("msc to %d", msc_w_tablicy);

    for (msc_w_tablicy; msc_w_tablicy<n; msc_w_tablicy++) {

        tablica[msc_w_tablicy].id = tablica[msc_w_tablicy + 1].id;
        strcpy(tablica[msc_w_tablicy].imie, tablica[msc_w_tablicy + 1].imie);
        strcpy(tablica[msc_w_tablicy].nazwisko, tablica[msc_w_tablicy + 1].nazwisko);
        tablica[msc_w_tablicy].wiek = tablica[msc_w_tablicy + 1].wiek;
        tablica[msc_w_tablicy].zarobki = tablica[msc_w_tablicy + 1].zarobki;

        }

    FILE *fout = fopen("imiona_out.txt", "w");

    int i;

    for (i=0; i<n - 1; i++) fprintf(fout, "%d %s %s %d %lf \n", tablica[i].id, tablica[i].imie, tablica[i].nazwisko, tablica[i].wiek, tablica[i].zarobki );

    fclose(fout);
}


void usun_osobe_menu() {

    int id;

    printf("Podaj ID osoby do usuniecia \n");

    scanf("%d", &id);

    usun_osobe(id);

    printf("\n Usunieto osobe o id = %d \n", id);

    main();

}

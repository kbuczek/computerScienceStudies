
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


int porownajosoby_nazwiskiem(Osoba os1, Osoba os2)
{
    int n = strcmp(os1.nazwisko, os2.nazwisko);
        if(n != 0) return n;

        n = strcmp(os1.imie, os2.imie);
        if( n != 0) return n;

        n = os1.wiek - os2.wiek;
            if(n!=0) return n;

            return os1.zarobki-os2.zarobki;
}

int porownajosoby_imieniem(Osoba os1, Osoba os2)
{
    int n = strcmp(os1.imie, os2.imie);
        if( n != 0) return n;

    n = strcmp(os1.nazwisko, os2.nazwisko);
        if(n != 0) return n;



        n = os1.wiek - os2.wiek;
            if(n!=0) return n;

            return os1.zarobki-os2.zarobki;
}

int porownajosoby_wiekiem(Osoba os1, Osoba os2)
{
    int n = os1.wiek - os2.wiek;

    if( n != 0) return n;
            n = strcmp(os1.nazwisko, os2.nazwisko);

    if(n!=0) return n;
             n = strcmp(os1.imie, os2.imie);



    if(n != 0) return n;

    return os1.zarobki-os2.zarobki;
}

int porownajosoby_zarobkami(Osoba os1, Osoba os2)
{
    return os1.zarobki-os2.zarobki;

    int n = strcmp(os1.nazwisko, os2.nazwisko);
        if(n != 0) return n;

        n = strcmp(os1.imie, os2.imie);
        if( n != 0) return n;

        n = os1.wiek - os2.wiek;
            if(n!=0) return n;
}

void imiona_bubble_sort(Osoba tablica[], int n, int opcja){

if(opcja == 1) {
  int i, k;
  Osoba temp;

  for (k = n-1; k>0; k--)
  {
    for (i = 0 ; i < k; i++)
    {
//Specjalna funkcja do porównywania stringów strcmp(. , . ) - zwraca dodatnia - jesli jest wyzej w alfabcie
      if (porownajosoby_nazwiskiem(tablica[i], tablica[i+1]) > 0 )
      {
// strcpy - funkcja do kopiowania
        temp = tablica[i];
        tablica[i] = tablica[i + 1];
        tablica[i + 1] = temp;
      }
    }
  }
}

if(opcja == 2) {
  int i, k;
  Osoba temp;

  for (k = n-1; k>0; k--)
  {
    for (i = 0 ; i < k; i++)
    {
//Specjalna funkcja do porównywania stringów strcmp(. , . ) - zwraca dodatnia - jesli jest wyzej w alfabcie
      if (porownajosoby_imieniem(tablica[i], tablica[i+1]) > 0 )
      {
// strcpy - funkcja do kopiowania
        temp = tablica[i];
        tablica[i] = tablica[i + 1];
        tablica[i + 1] = temp;
      }
    }
  }
}

if(opcja == 3) {
  int i, k;
  Osoba temp;

  for (k = n-1; k>0; k--)
  {
    for (i = 0 ; i < k; i++)
    {
//Specjalna funkcja do porównywania stringów strcmp(. , . ) - zwraca dodatnia - jesli jest wyzej w alfabcie
      if (porownajosoby_wiekiem(tablica[i], tablica[i+1]) > 0 )
      {
// strcpy - funkcja do kopiowania
        temp = tablica[i];
        tablica[i] = tablica[i + 1];
        tablica[i + 1] = temp;
      }
    }
  }
}

if(opcja == 4) {
  int i, k;
  Osoba temp;

  for (k = n-1; k>0; k--)
  {
    for (i = 0 ; i < k; i++)
    {
//Specjalna funkcja do porównywania stringów strcmp(. , . ) - zwraca dodatnia - jesli jest wyzej w alfabcie
      if (porownajosoby_zarobkami(tablica[i], tablica[i+1]) > 0 )
      {
// strcpy - funkcja do kopiowania
        temp = tablica[i];
        tablica[i] = tablica[i + 1];
        tablica[i + 1] = temp;
      }
    }
  }
}
}



int sortowanie_menu() {
int opcja;

printf("\n \n 1. Sortuj nazwisko, imie, wiek, zarobki \n");
printf("2. Sortuj imie, nazwisko, wiek, zarobki  \n");
printf("3. Sortuj wiek, nazwisko, imie, zarobki \n");
printf("4. Sortuj zarobki, nazwisko, imie, wiek \n");
printf("5. Powrót do glownego menu \n");

scanf("%d", &opcja);

return opcja;

}

int wypisz_sortowanie_menu()
 {
    while(1) {
     switch (sortowanie_menu()) {
        case 1:
            sortuj_dane(1);
            printf("\n \n 1. Wczytano i posortowano dane: nazwisko, imie, wiek, zarobki \n");
            break;
        case 2:
            sortuj_dane(2);
            printf("\n \n 1. Wczytano i posortowano dane: imie, nazwisko, wiek, zarobki  \n");
            break;
        case 3:
            sortuj_dane(3);
            printf("\n \n 1. Wczytano i posortowano dane: wiek, nazwisko, imie, zarobki \n");
            break;
        case 4:
            sortuj_dane(4);
            printf("\n \n 1. Wczytano i posortowano dane: zarobki, nazwisko, imie, wiek \n");
            break;
        case 5:
            main();
            break;
        default:
            printf("\n \n \n Wybierz jedna z 5 mozliwych opcji: \n \n \n");
            sortowanie_menu();
            break;
     }
    }
 }

int sortuj_dane(int opcja) {


Osoba tablica[50];

FILE *fin = fopen("imiona_out.txt", "r");


int n = 0;

while(fscanf(fin, "%d %s %s %d %lf", &tablica[n].id, tablica[n].imie, tablica[n].nazwisko, &tablica[n].wiek, &tablica[n].zarobki  ) == 5) n++;

fclose(fin);

imiona_bubble_sort(tablica, n, opcja);

FILE *fout = fopen("imiona_out.txt", "w");

int i;

for (i=0; i<n; i++) fprintf(fout, "%d %s %s %d %lf \n", tablica[i].id, tablica[i].imie, tablica[i].nazwisko, tablica[i].wiek, tablica[i].zarobki );

    fclose(fout);

return 0;
}

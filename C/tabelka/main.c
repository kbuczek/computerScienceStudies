/*

1. Wczytaj osoby z pliku - komunikat - wczytano dane 15 albo 16 osób
2. Wypisz dane w postaci tabelki - pojawi się tabelka z tymi osobami
3. Sortuj dane.
 a)n i w z
 b)i n w z
 c)w n i z
 d)z n i w
4. Dodaj osobę do tablicy - poprosić o imię nazwisko wiek i zarobki
5. Usuń osobę z tablicy - podać id osoby w tabelce i

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wczytaj_z_pliku();
int wypisz_tabelke();
int wypisz_sortowanie_menu();
void dodaj_osobe();
void usun_osobe_menu();

int menu() {
int wybor;

printf("\n \n 1. Wczytaj osoby z pliku \n");
printf("2. Wypisz dane w postaci tabelki \n");
printf("3. Sortuj dane \n");
printf("4. Dodaj osobę do tablicy \n");
printf("5. Usuń osobę z tablicy \n");
printf("6. Zakończ \n");

scanf("%d", &wybor);

return wybor;

}

int main()
 {
    while(1) {
     switch (menu()) {
        case 1:
            wczytaj_z_pliku();
            break;
        case 2:
            wypisz_tabelke();
            break;
        case 3:
            wypisz_sortowanie_menu();
            break;
        case 4:
            dodaj_osobe();
            break;
        case 5:
            usun_osobe_menu();
            break;
        case 6:
            exit(0);
        default:
            printf("\n \n \n Wybierz jedna z 5 mozliwych opcji: \n \n \n");
            main();
            break;
     }
    }
 }

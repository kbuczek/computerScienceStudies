# Gra Statki w konsoli
Gra rozpoczyna się od ustawienia statków na planszy (każdy z 2 graczy ma swoją planszę). Następnie na zmianę gracze strzelają w planszę przeciwnika. W momencie trafinia w statek, gracz ponawia ruch. Wygrywa gracz, który pierwszy zniszczy wszystkie statki przeciwnika. 

## Znaczenie znaków
'_' - puste miejsce  
'X' - trafiony statek  
'O' - pudło  
'#', '<', '>', '^', 'v' - elementy statku  

## Opis Funkcji

<b>getInputFromPlayer()</b> - pobiera input od gracza. Wyrzuca wyjątek, jeżeli input nie jest typu int.  

klasa <b>Battleship(startingPoint, length, direction)</b> - klasa statku, tworzy koordynaty statku (funkcja createBattleship()) na podstawie startingPoint, length i direction. Przechowuje 2 elementowe krotki koordynaty statku w liście coordinatesList.  Zawiera listę hitDetection, która ma pola true or false, gdzie true oznacza trafione miejsce. Funkcja isDestroyed() zwraca true jeżeli wszystkie pola w hitDetection są true.

klasa <b>Game()</b> - odpowiada za planszę gry. Przechowuje w słowniku allShots wszystkie strzały (kluczem są krotki 2 elementowe z typem int, a wartością prawda lub fałsz, gdzie prawda to celne trafienie). Analizę poprawności strzału przeprowadza funkcja shotIsCorrect(), która sprawdza, czy dany strzał jest w odpowiednim przedziale oraz sprawdza, czy dany strzał już się znajduje w słowniku allShots. Strzały do planszy dodaje funkcja shoot() - zwraca prawdę jeżeli strzał był trafiony. Usuwa statek z listy battleships jeżeli jest on całkowicie zniszczony. Funkcja addBattleship() dodaje statki do listy battleships i sprawdza poprawność ich lokalizacji oraz kolizję z innymi statkami. placeRandomBattleships(numOf5, numOf4, numOf3, numOf2) tworzy losowe położenie statków przy pomocy funkcji placeRandomBattleshipOfType(numberOfShips, battleshipLength). numOf5 oznacza ilość statków o długości 5. Funkcja isOver() zwraca true, jeżeli lista statków battleships jest pusta.

<b>renderBoardRowByRow(game, showBattleships)</b> - renderuje planszę wiersz po wierszu. Jako pierwszy argument przyjmuje instancję klasy Game(). Drugi argmuent odpowiada za to, czy pokazać położenie statków.  

<b>getInputFromComputer(battleshipWasHit, lastShot, game)</b> - generuje losowe strzały na planszy. Sprawdza czy danego strzału nie ma już w game.allShots. Jeżeli strzał w poprzedniej rundzie był trafiony (battleshipWasHit), to generuje losowy strzał obok ostatniego strzału (lastShot)

<b>playerVsPlayer()</b> - odpowiada za logikę gry pomiędzy dwoma graczami 

<b>playerVsComputer()</b> - odpowiada za logikę gry pomiędzy graczem i komputerem

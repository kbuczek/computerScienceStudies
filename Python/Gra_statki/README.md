# Gra Statki w konsoli

## Znaczenie znaków
'_' - puste miejsce  
'X' - trafiony statek  
'O' - pudło  
'#', '<', '>', '^', 'v' - elementy statku  

## Opis Funkcji

getInputFromPlayer() - pobiera input od gracza  
klasa Battleship() - klasa statku, tworzy koordynaty statku i je przechowuje w liście coordinatesList  
klasa Game() - odpowiada za logikę gry. Dodaje i sprawdza poprawność lokalizacji i kolizji statków. Dodaje i sprawdza poprawność strzałów. Tworzy losowe położenie statków. Zawiera słownik allShots, który zawiera wszystkie strzały na planszy (kluczem są krotki 2 elementowe, a wartością prawda lub fałsz)  
renderBoardRowByRow(game, showBattleships) - renderuje planszę wiersz po wierszu. Jako pierwszy argument przyjmuje instancję klasy Game(). Drugi argmuent odpowiada za to, czy pokazać położenie statków  
getInputFromComputer() - losowe strzały na planszy. Jeże  
playerVsPlayer()  
playerVsComputer()  

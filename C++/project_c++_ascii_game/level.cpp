#include "level.h"
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>

Level::Level() {

}

Level::~Level() {

}

void Level::load(std::string levelFile, Player &player) {
    //Otwieranie pliku txt z poziomem
    std::ifstream file; //ifstream tylko otwiera pliki
    file.open(levelFile);

    if(file.fail()) {
        std::cout << "Problem with opening the file!" << std::endl;
        perror(levelFile.c_str());
        exit(1);
    }

    std::string line;

    //czytanie linii z otwartego pliku
    while(getline(file, line)) {
        levelData.push_back(line); //dodaj linie do vectoru levelData
    }

    file.close();

    //Przetwarzanie (skanowanie) poziomu
    char pointer;

    for(int y = 0; y< levelData.size(); y++) { //vertical
        for(int x = 0; x < levelData[x].size(); x++) { //horizontal
            pointer = levelData[y][x];
            switch(pointer) {
                case '@': //Player
                    player.setPosition(x, y);
                    break;
                case 'E': //Elf
                    enemies.push_back(Enemy("Elf", pointer, 1, 3, 1, 10, 50)); //tworzymy obiekt klasy Enemy i dodajemy go do vectora enemies
                    //do ostatnio dodanego enemy dodajemy wspolrzedne jego pozycji
                    enemies.back().setPosition(x, y);
                    break;
                case 'g':
                    enemies.push_back(Enemy("Goblin", pointer, 2, 10, 5, 35, 150));
                    enemies.back().setPosition(x, y);
                    break;
                case 'd':
                    enemies.push_back(Enemy("Dwarf", pointer, 3, 30, 15, 100, 300));
                    enemies.back().setPosition(x, y);
                    break;
                case 'O':
                    enemies.push_back(Enemy("Ork", pointer, 4, 20, 20, 200, 500));
                    enemies.back().setPosition(x, y);
                    break;
                case 'D':
                    enemies.push_back(Enemy("Dragon", pointer, 100, 2000, 2000, 2000, 5000000));
                    enemies.back().setPosition(x, y);
                    break;
//                default:
//                    printw("Symbol nie rozpoznany");
            }
        }
    }
}

void Level::print() {
//    init_color(COLOR_RED, 226, 2, 62);
//    init_color(COLOR_BLUE, 211, 255, 252);
//    init_color(COLOR_CYAN, );
//    init_color(COLOR_GREEN, 165, 219, 98);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // player
    init_pair(2, COLOR_BLACK, COLOR_BLACK); // kropka
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // sciana
    init_pair(4, COLOR_BLUE, COLOR_BLACK); // elf
    init_pair(5, COLOR_GREEN, COLOR_BLACK); // ork
    init_pair(6, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(7, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(8, COLOR_RED, COLOR_BLACK); // default
    init_pair(9, COLOR_MAGENTA, COLOR_BLACK); // default
    for (int i = 0; i < levelData.size(); i++) {
        // zmiana wypisywania po jednym znaku zamiast calej linii
        for(int j = 0; j < levelData[i].size(); j++) {
            int char_color = 6;
            switch(levelData[i][j]) {
                case '#':
                    char_color = 3;
                    break;
                case '@':
                    char_color = 1;
                    break;
                case '.':
                    char_color = 2;
                    break;
                case 'E':
                    char_color = 4;
                    break;
                case 'O':
                    char_color = 5;
                    break;
                case 'g':
                    char_color = 7;
                    break;
                case 'D':
                    char_color = 8;
                    break;
                case 'd':
                    char_color = 9;
                    break;
                default:
                    char_color = 6;
                    break;
            }
            wattron(window, COLOR_PAIR(char_color));
            wprintw(window, "%c", levelData[i][j]);
            wattroff(window, COLOR_PAIR(char_color));
        }
        wprintw(window, "\n", "");
    }
}

void Level::movePlayerL(char input, Player &player) {

    int playerX, playerY;
    //obecna pozycja gracza
    player.getPosition(playerX, playerY);

    //os y idzie od gory do dolu (ujemne liczby w pierwszej i drugiej cwiartce)
    switch(input){
        case 'w':
            processPlayerMove(player, playerX, playerY - 1);
            break;
        case 'a':
            processPlayerMove(player, playerX - 1, playerY);
            break;
        case 's':
            processPlayerMove(player, playerX, playerY + 1);
            break;
        case 'd':
            processPlayerMove(player, playerX + 1, playerY);
            break;
    }

}

void Level::updateEnemies(Player &player) {
    char aiMove;
    int playerX, playerY;
    //obecna pozycja gracza
    player.getPosition(playerX, playerY);

    int enemyX, enemyY;


    //przechodzi caly vector z wrogami
    for(int i = 0; i < enemies.size(); i++) {
        aiMove = enemies[i].getMove(playerX, playerY); //zwraca wasd

                // pozycja wroga
                        enemies[i].getPosition(enemyX, enemyY);

        switch(aiMove){
            case 'w':
                processEnemyMove(player, i, enemyX, enemyY - 1);
                break;
            case 'a':
                processEnemyMove(player, i, enemyX - 1, enemyY);
                break;
            case 's':
                processEnemyMove(player, i, enemyX, enemyY + 1);
                break;
            case 'd':
                processEnemyMove(player, i, enemyX + 1, enemyY);
                break;
        }
    }
}

//wyciagam znak z miejsca x, y
char Level::getPointer(int x, int y) {
    char pointer = levelData[y][x];
    return pointer;
}

void Level::setPointer(int x, int y, char pointer) {
    levelData[y][x] = pointer;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
    int playerX, playerY;
    //obecna pozycja gracza
    player.getPosition(playerX, playerY);
    //miejsce na ktorej chcemy przejsc
    char movePointer = getPointer(targetX, targetY);

    switch(movePointer) {
        case '.':
            //zmienia pozycje gracza
            player.setPosition(targetX, targetY);
            //obecne miejsce staje sie '.'
            setPointer(playerX, playerY, '.');
            //na przyszle miejsce wstawiam gracza graficznie
            setPointer(targetX, targetY, '@');
            break;
        case '#':
            break;
        default: //enemy
            battleEnemy(player, targetX, targetY);
            break;
    }
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
    int playerX, playerY, enemyX, enemyY;

    enemies[enemyIndex].getPosition(enemyX, enemyY);

    //obecna pozycja gracza
    player.getPosition(playerX, playerY);
    //miejsce na ktorej chcemy przejsc
    char movePointer = getPointer(targetX, targetY);

    switch(movePointer) {
        case '.':
            //zmienia pozycje gracza
            enemies[enemyIndex].setPosition(targetX, targetY);
            //obecne miejsce staje sie '.'
            setPointer(enemyX, enemyY, '.');
            //na przyszle miejsce wstawiam wroga graficznie
            setPointer(targetX, targetY, enemies[enemyIndex].getPointer());
            break;
        case '#':
            break;
        default:
            break;
    }
}

void Level::battleEnemy(Player &player, int targetX, int targetY) {

    int enemyX, enemyY, attackRoll, attackResult, playerX, playerY;
    std::string enemyName;

    player.getPosition(playerX, playerY);

    for(int i = 0; i < enemies.size(); i++) {
        enemies[i].getPosition(enemyX, enemyY);
        enemyName = enemies[i].getName();

        //znajdujemy wroga o zgadzajacych sie wspolrzednych
        if (targetX == enemyX && targetY == enemyY) {

            //zwraca zmienna attack gracza
            attackRoll = player.attackRand();
            //gracz atakuje przeciwnika
            attackResult = enemies[i].takeDamage(attackRoll);
            wprintw(window, "Gracz atakuje %s moca: %d\n", enemyName.c_str(), attackRoll);
            if(attackResult != 0) {
                //zmiana miejsca gdzie stal enemy na '.'
                setPointer(targetX, targetY, '.');
//                print();
              wprintw(window, "%s has been slained!\n", enemyName.c_str());

                //usun obecnego wroga w vector enemies
                enemies[i] = enemies.back();
                enemies.pop_back();
                //zmniejszamy ilosc przeciwnikow o 1
                i--;

                player.addExperience(attackResult);
                return;
            }

            //przeciwnik atakuje gracza
            attackRoll = enemies[i].attackRand();
            attackResult = player.takeDamage(attackRoll);
            wprintw(window, "Zostales zaatakowany moca: %d przez %s\n", attackRoll, enemyName.c_str());
            if(attackResult != 0) {
                //zmiana miejsca gdzie stal gracz na 'X'
                setPointer(playerX, playerY, 'X');
              wprintw(window, "Umarles. KONIEC GRY!\n");
                player.addExperience(attackResult);

                //koniec programu
//                delwin(window);
//                endwin();
//                exit(0);
            }
            return;
        }
    }
}
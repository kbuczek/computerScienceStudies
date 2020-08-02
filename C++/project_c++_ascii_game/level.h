#ifndef PROJEKT_C_LEVEL_H
#define PROJEKT_C_LEVEL_H

#include <vector>
#include<string>
#include <ncurses.h>
#include "player.h"
#include "enemy.h"

class Level {
    std::vector <std::string> levelData;
    std::vector <Enemy> enemies;
public:
    Level();
    ~Level();
    WINDOW *window;
    void load(std::string levelFile, Player &player);
    void print();
    void movePlayerL(char input, Player &player);
    char getPointer(int x, int y);
    void setPointer(int x, int y, char pointer);
    void processPlayerMove(Player &player, int targetX, int targetY);
    void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
    void battleEnemy(Player &player, int targetX, int targetY);
    void updateEnemies(Player &player);

//    friend void wypiszStaty(const Level &c);

};

#endif //PROJEKT_C_LEVEL_H

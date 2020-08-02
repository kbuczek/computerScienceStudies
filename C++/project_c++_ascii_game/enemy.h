#ifndef PROJEKT_C_ENEMY_H
#define PROJEKT_C_ENEMY_H
#include <string>
#include <vector>
#include "player.h"
#include "postac.h"


//dziedziczenie z Postac
class Enemy : public Postac{
    std::string name;
    char pointer;
public:
    Enemy(std::string name, char pointer, int level, int attack, int defense, int health, int xp);
    //setter
//    void setPosition(int x, int y);
    //getter
//    void getPosition(int &x, int &y);
    std::string getName() { return name; };
    char getPointer() { return pointer; };

    int attackRand();
    int takeDamage(int attack);
    char getMove(int playerX, int playerY);

    //deklaracja przyjaciela
//    friend void Level::ktoSilniejszy(Player &player);
};


#endif //PROJEKT_C_ENEMY_H

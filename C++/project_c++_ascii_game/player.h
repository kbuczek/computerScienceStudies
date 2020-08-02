#ifndef PROJEKT_C_POSTAC_H
#define PROJEKT_C_POSTAC_H
#include <iostream>
#include "enemy.h"
#include "postac.h"

class Player : public Postac {
public:
    Player(); //konstruktor
//    ~Player(); //dekonstrukotr
    //inicjalizacja
    Player(int level, int health, int attack, int defense, int experience);
    //setter
//    void setPosition(int x, int y);
    //getter
//    void getPosition(int &x, int &y);
    int attackRand();
    void addExperience(int experience);
    int takeDamage(int attack);
    //Konstruktor kopiujacy
    Player(Player &player);

    //deklaracja przyjaciela
//    friend void wypiszStaty();
};

#endif //PROJEKT_C_POSTAC_H

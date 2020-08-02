#include <iostream>
#include <random>
#include <ctime>
#include "player.h"

//zamienia wartosci w klasie Player z podanymi przez main.cpp
Player::Player() {

}

Player::Player(int level1, int health1, int attack1, int defense1, int experience1) : Postac(level1, health1, attack1, defense1, experience1) {

}

//setter pozycji gracza
//void Player::setPosition(int x1, int y1) {
//    x = x1;
//    y = y1;
//}

//getter pozycji gracza
//void Player::getPosition(int &x1, int &y1) { //dlaczego tu jest referencja
//    x1 = x;
//    y1 = y;
//}

int Player::attackRand() {
//    static default_random_engine randomEngine(time(NULL);
//    uniform_int_distribution<int> attackRoll(0, attack);
//    return attackRoll(randomEngine);
    return attack;
}

//dodawanie exp po ataku na przeciwnika
void Player::addExperience(int experience1) {
    experience += experience1;

    //zwiekszanie statow gracza ???
    while(experience > 50) {
//        wprintw(win, "Level Up!\n");
        experience -= 50;
        level++;
        attack += 10;
        defense += 5;
        health += 50;
    }
}

int Player::takeDamage(int attack) {
    attack -= defense;
    //sprawdzam czy mozna zadac obrazenie
    if(attack > 0) {
        health -= attack;
        //sprawdzam, czy gracz umarl
        if(health <= 0) {
            return 1;
        }
    }
    return 0;
}

///////////////////////////////////////////////////

//Konstruktor kopiujacy
Player::Player(Player &player1) {
    level = player1.level;
    health = player1.health;
    attack = player1.attack;
    defense = player1.defense;
    experience = player1.experience;
}
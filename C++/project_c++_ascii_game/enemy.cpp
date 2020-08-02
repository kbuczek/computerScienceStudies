#include "enemy.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "postac.h"

Enemy::Enemy(std::string name1, char pointer1, int level1, int attack1, int defense1, int health1, int xp1) : Postac(level1, attack1, defense1, health1, xp1) {
    name = name1;
    pointer = pointer1;
}

//setter pozycji wroga
//void Enemy::setPosition(int x1, int y1) {
//    x = x1;
//    y = y1;
//}

//getter pozycji wroga
//void Enemy::getPosition(int &x1, int &y1) { //dlaczego tu jest referencja
//    x1 = x;
//    y1 = y;
//}

int Enemy::attackRand() { //getAttack
    return attack;
}

int Enemy::takeDamage(int attack) {
    attack -= defense;
    //sprawdzam czy mozna zadac obrazenia
    if(attack > 0) {
        health -= attack;
        //sprawdzam, czy wrog umarl
        if(health <= 0) {
            return experience;
        }
    }
    return 0;
}

//Poruszaj przeciwnikow w kierunku gracza
char Enemy::getMove(int playerX, int playerY) {
    //random number+_
    srand(time(NULL));
    //0 - 6
    int randomMove = rand() % 6;

    int distance;
    int dx = x - playerX;
    int dy = y - playerY;
    int adx = abs(dx); //abs - wartosc bezwzgledna
    int ady = abs(dy);
    distance = adx + ady;
    if (distance <= 5) {
        //poruszanie sie po dluzszej osi do gracza
        if (adx > ady) {
            //jesli gracz jest na prawo od przciwnika
            if( dx > 0) {
                return 'a';
            } else {
                return 's';
            }
        } else {
            //jesli gracz jest powyzej przeciwnika
            if( dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }

    switch (randomMove) {
        case 0:
        return 'a';
        case 1:
            return 'w';
        case 2:
            return 's';
        case 3:
            return 'd';
        default:
            return '.';
    }
}
#include "postac.h"

Postac::Postac() {

}


Postac::Postac(int level1, int health1, int attack1, int defense1, int experience1) {
    level = level1;
    health = health1;
    attack = attack1;
    defense = defense1;
    experience = experience1;
}

//setter pozycji postaci
void Postac::setPosition(int x1, int y1) {
    x = x1;
    y = y1;
}

//getter pozycji postaci
void Postac::getPosition(int &x1, int &y1) {
    x1 = x;
    y1 = y;
}
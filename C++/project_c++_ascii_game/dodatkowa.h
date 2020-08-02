#ifndef PROJEKT_C_DODATKOWA_H
#define PROJEKT_C_DODATKOWA_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include "player.h"


class Dodatkowa {
    WINDOW *window;
public:
    void init(WINDOW *win);
//friend, przeciazanie operatorow
    void przyjaciel(Player &player);
};


#endif //PROJEKT_C_DODATKOWA_H

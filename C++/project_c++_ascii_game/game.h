#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <ncurses.h>
#include "player.h"
#include "level.h"
#include "dodatkowa.h"

class Game
{
    Player *player; //tworyzmy obiekt player
    Level level; //tworzymy obiekt level
    WINDOW *window; //wskaznik do okna (potrzebny przy wprintw)

    //-----dodatkowa-----
    Dodatkowa d1;
    int a = 1;
    //----------------

    public:
    Game(std::string levelFile, WINDOW *win);//constructor
    ~Game(); // deconstructor
    void loopGame();
    void movePlayerG();

//    friend void Dodatkowa::przyjaciel();

};

#endif CLASS_H
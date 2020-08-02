#include <iostream>
#include <cstdlib>
#include <string>
#include <ncurses.h> //obsluga klawiatury
#include <unistd.h>

#include "game.h"
#include "player.h"
#include "level.h"
#include "dodatkowa.h"

int main() {
    initscr();
//    refresh();
    start_color();
    WINDOW *win = newwin(480, 640, 0, 0); //creates window
    noecho(); // getch nie wypisuje znakow
    Game game("level1.txt", win); //tworzymy  obiekt game klasy Game
    game.loopGame();
    delwin(win);
    endwin();
    return 0;
}

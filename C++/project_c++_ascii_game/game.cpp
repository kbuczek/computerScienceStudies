#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "game.h"
#include "player.h"

Game::Game(std::string levelFile, WINDOW *win) {
    window = win;

    player = new Player(1, 100, 20, 10, 0);
    //--------klasa dodatkowa---------
    d1.init(window);
    d1.przyjaciel(*player);
    //--------
    level.window = win;
    level.load(levelFile, *player);
}

Game::~Game() {
	std::cout << "Dekonstruktor Gry" << std::endl;
}

void Game::loopGame() {
    bool loop = true;
    int i = 0; //frame counter
      do {
        level.print();
        movePlayerG();
        level.updateEnemies(*player);
        wprintw(window, "%d\n", i++);
        refresh();
        wrefresh(window);
        wclear(window);
//      wprintw(window, "Poruszaj sie literami wasd:\n");
//        usleep(100000);
    } while(loop == true);
}

void Game::movePlayerG() {
    char input;
    input = getch();
    level.movePlayerL(input, *player);
}
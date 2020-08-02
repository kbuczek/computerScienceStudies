

#include "dodatkowa.h"
#include "player.h"

void Dodatkowa::init(WINDOW *win) {
    window = win;
    wprintw(window, "Poruszaj sie klawiszami w, a, s, d\n");
}

void Dodatkowa::przyjaciel(Player &player) {
// wprintw(window, "a: %d", player.health);
}
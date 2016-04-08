#include <curses.h>
#include "game.h"
#include <stdlib.h>

int main() {
	Game * gm = new Game;
	gm->init();
	timeout(100);
	while (!gm->getend()) {
		gm->input();
		gm->draw();
	}
	gm->endgame();
	delete gm;
	return 0;
}
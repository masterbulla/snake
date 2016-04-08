#include "game.h"
#include <curses.h>
#include <time.h>

Game::Game()
{
	direction = 0;
	end = false;
	points = 0;
}

Game::~Game()
{
}
void placefood();

int Game::getheadX() {
	return snake.front().getX();
}

int Game::getheadY() {
	return snake.front().getY();
}

void Game::init() {
	
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, maxY, maxX);
	snake.push_back(snakepoint(maxX / 2, maxY / 2));
	this->placefood();
}

void Game::placefood() {
	srand(time(NULL));
	bool t = true;
	while (t) {
		t = false;
		food_x = rand() % (maxX - 1) + 1;
		food_y = rand() % (maxY - 1) + 1;
		for (auto x : snake) {
			if (food_x == x.getX() && food_y == x.getY()) {
				t = true; 
				break;
			}
		}
	}
}

void Game::input() {
	ch = getch();
	switch (ch) {
		case KEY_UP:    direction=3; break;
		case KEY_DOWN:  direction=1; break;
		case KEY_RIGHT: direction=0; break;
		case KEY_LEFT:  direction=2; break;
	}
}

void Game::collision() {
	it = snake.begin();
	std::advance(it, 1);
	for (; it != snake.end(); it++) {
		if (this->getheadX() == it->getX() && this->getheadY() == it->getY()) {
			end = true;
		}
	}
	if (this->getheadX() == 0 || this->getheadX() == maxX) end = true;
	if (this->getheadY() == 0 || this->getheadY() == maxY) end = true;
	if (this->getheadX() == food_x && this->getheadY() == food_y) {
		this->placefood();
		points++;
	}
	else {
		snake.pop_back();
	}
	
	
}

void Game::draw(){
	int tempx = this->getheadX();
	int tempy = this->getheadY();
	if (direction == 0) tempx++;
	if (direction == 1) tempy++;
	if (direction == 2) tempx--;
	if (direction == 3) tempy--;
	this->collision();
	snake.push_front(snakepoint(tempx, tempy));	
	erase();
	mvaddch(food_y, food_x, '*');
	for (auto point : snake) {
		mvaddch(point.getY(), point.getX(), '@');
	}
		refresh();
}

bool Game::getend(){
	return end;
}

void Game::endgame() {
	timeout(-1);
	erase();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(maxY/2, maxX/2, "Game over");
	mvprintw((maxY / 2) + 1, maxX / 2, "You gained %i points", points);
	refresh();
	getch();
	endwin();
}
#pragma once
#include <list>

class snakepoint {
private:
	int snx, sny;
public:
	snakepoint(int x, int y) : snx(x), sny(y) {};
	~snakepoint() {};
	int getX() { return snx; };
	int getY() { return sny; };
};

class Game {
public:
	Game();
	~Game();
	void init();
	void draw();
	void input();
	void placefood();
	void collision();
	bool getend();
	void endgame();
	int getheadX();
	int getheadY();

private:
	std::list<snakepoint> snake;
	int maxX, maxY, points, direction, ch, food_x, food_y;
	std::list<snakepoint>::iterator it;
	bool end;
};


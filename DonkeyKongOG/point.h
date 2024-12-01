#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"
#include "utils.h"
#include "board.h"  

class point
{
	int x;
	int y;
	int diff_x;
	int diff_y;
	Board* pBoard = nullptr;  
public:
	point(int _x, int _y) :x(_x), y(_y) { diff_x = 0; diff_y = 0; }
	void draw(char c) const 
	{
		gotoxy(x, y);
		std::cout << c; 
	}	
	void erase() 
	{
		draw(' ');
	}
	void erase(char c)
	{
		draw(c);
	}	
	//void keyPressed(char key);
	void move(gameConfig::eKeys key);
	void setBoard(Board& board) {
		pBoard = &board;
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};
#endif

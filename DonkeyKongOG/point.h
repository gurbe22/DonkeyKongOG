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
	point() :x(1), y(22) { diff_x = 0; diff_y = 0; }
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
	void setBoard(Board& board) {
		pBoard = &board;
	}

	int& getX() {
		return x;
	}
	int& getY() {
		return y;
	}
	void setY(int newY)
	{
		y = newY; 
	}
	void setX(int newX)
	{
		x = newX; 
	}
	int& getDiffX() {
		return diff_x; 
	}
	int& getDiffY() { 
		return diff_y; 
	}
	void setDiffY(int newDiff_y)
	{
		diff_y = newDiff_y;
	}
	void setDiffX(int newDiff_x)
	{
		diff_x = newDiff_x; 
	}
	Board* getBoard()
	{
		return pBoard;  
	}
};
#endif

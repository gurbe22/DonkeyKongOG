#ifndef POINT_H
#define POINT_H

#include "utils.h"
#include "board.h"  

#include <iostream>

class point
{
	int x;
	int y;
	int diff_x;
	int diff_y;
	Board* pBoard = nullptr;  

public:
	enum class States { FALLING, JUMPING, CLIMBING, WALKING_OR_STAYING };

	static constexpr char FLOOR = '=';
	static constexpr char LFLOOR = '<';
	static constexpr char RFLOOR = '>';
	static constexpr char LADDER = 'H';
	static constexpr char OPEN_SPACE = ' ';


	point(const int xStart, const int yStart) :x(xStart), y(yStart) { diff_x = 0; diff_y = 0;}  //Ctor    

	bool isOutOfLimit(int newPos_x, int newPos_y);

	void move(int newDiff_X, int newDiff_Y);

	void draw(char ch) const 
	{
		gotoxy(x, y);
		std::cout << ch; 
	}	
	
	void erase() const
	{
		char ch;
		
		ch = pBoard->getChar(x, y); 
		draw(ch);
	}

	void setBoard(Board& board) {
		pBoard = &board;
	}

	int getX() const { return x; }

	int getY() const { return y; }

	void setX(int newX) { x = newX; }

	void setY(int newY) { y = newY; }

	int getDiffX() const { return diff_x; }

	int getDiffY() const { return diff_y; }

	void setDiffY(int newDiff_y){ diff_y = newDiff_y; }

	void setDiffX(int newDiff_x) { diff_x = newDiff_x; }

	Board* getBoard() const { return pBoard; } 

	bool isFloor(char nextChar)
	{ return nextChar == FLOOR || nextChar == LFLOOR || nextChar == RFLOOR;	}
};
#endif

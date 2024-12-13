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
	enum class States { FALLING, JUMPING, CLIMBING, WALKING_OR_STAYING };

	point() :x(1), y(22) { diff_x = 0; diff_y = 0; }

	bool isOutOfLimit(int newPos_x, int newPos_y)
	{
		return (newPos_x >= gameConfig::GAME_WIDTH - 1 ||
			    newPos_y >= gameConfig::GAME_HEIGHT - 1 ||
			    newPos_x <= 0 ||
			    newPos_y <= 0);
	}

	bool isFloor(char nextChar)
	{
		return nextChar == '=' || nextChar == '<' || nextChar == '>';
	}

	void move(int newDiff_X, int newDiff_Y)
	{
		int newPos_x = x + newDiff_X;
		int newPos_y = y + newDiff_Y;
		char nextChar = pBoard->getChar(newPos_x, newPos_y);

		if (isOutOfLimit(newPos_x, newPos_y) || isFloor(nextChar))
		{
			newDiff_X = 0;
			newDiff_Y = 0;
		}

		diff_x = newDiff_X;
		diff_y = newDiff_Y;

		x += diff_x;
		y += diff_y;
	}

	void draw(char c) const 
	{
		gotoxy(x, y);
		std::cout << c; 
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

	void setX(int newX) {
		x = newX;
	}

	void setY(int newY) {
		y = newY;
	}

	int getDiffX() const { return diff_x; }

	int getDiffY() const { return diff_y; }

	void setDiffY(int newDiff_y)
	{
		diff_y = newDiff_y;
	}

	void setDiffX(int newDiff_x)
	{
		diff_x = newDiff_x; 
	}

	Board* getBoard() const {
		return pBoard;
	}
};
#endif

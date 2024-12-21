#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include <windows.h>
#include "gameConfig.h"
using namespace std;

class Barrel
{
	point barrel;
	static constexpr int  HEIGHT_TO_EXPLODE = 8;
	static constexpr int  BARREL_STARTING_X = 10;
	static constexpr int  BARREL_STARTING_Y = 4;
	int startDelay;  // זמן העיכוב לפני תחילת התנועה
	int currentFrame; // מספר הפריימים שעברו מאז תחילת המשחק
	bool explode = false;


	char findBarrelNextChar(char currChar, char charBelow);

	point::States findBarrelState(char currChar, char nextChar, char charBelow);

	bool isExploding() { return (barrel.getHeightFalling() >= HEIGHT_TO_EXPLODE); } 

	void barrelWalking(char charBelow);

public:


	//Barrel() : barrel(BARREL_STARTING_X, BARREL_STARTING_Y) {};
	// עדכון הבנאי
	Barrel(int delay = 0)
		: barrel(BARREL_STARTING_X, BARREL_STARTING_Y), startDelay(delay), currentFrame(0) {}

	void moveBarrel();

	void setBoard(Board& board)
	{
		barrel.setBoard(board);
	}

	Board* getBoard() const
	{
		return barrel.getBoard();
	}

	int getX() const
	{
		return barrel.getX();
	}

	int getY() const
	{
		return barrel.getY();
	}

	void drawBarrel() const
	{
		barrel.draw(gameConfig::BARREL);
	}

	void eraseBarrel() const
	{
		barrel.erase();
	}

	void setExplode(bool newExplode) { explode = newExplode; }

	bool getIsExplode() const { return explode; }
};
#endif
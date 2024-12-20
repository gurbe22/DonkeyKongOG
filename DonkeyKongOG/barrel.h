#ifndef BARREL_H
#define BARREL_H

#include "point.h"
#include <windows.h>
#include "mario.h"
using namespace std;

class Barrel
{
	point barrel;
	static constexpr int  HEIGHT_TO_EXPLODE = 8;
	static constexpr int  BARREL_STARTING_X = 37;
	static constexpr int  BARREL_STARTING_Y = 4;
	

	char findBarrelNextChar(char currChar, char charBelow);

	point::States findBarrelState(char currChar, char nextChar, char charBelow);

	bool isExploding() { return (barrel.getHeightFalling() >= HEIGHT_TO_EXPLODE); } 

	void barrelWalking(char charBelow);

public:

    static constexpr char  BARREL = 'O'; 

	Barrel() : barrel(BARREL_STARTING_X, BARREL_STARTING_Y) {};

	void moveBarrel();

	void setBoard(Board& board)
	{
		barrel.setBoard(board);
	}

	void drawBarrel() const
	{
		barrel.draw(BARREL);
	}

	void eraseBarrel() const
	{
		barrel.erase();
	}

};
#endif
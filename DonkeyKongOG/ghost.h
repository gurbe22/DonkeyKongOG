#pragma once
#include "point.h"
#include "gameConfig.h"
#include "Board.h"
#include <cstdlib> // For rand()

class ghost
{
	enum class directions {
		LEFT = -1,   // Move left
		RIGHT = 1,  // Move right
	};
	point myGhost;
	directions direction = directions::RIGHT;
	
	void changeDirection()
	{
		direction == directions::RIGHT ? direction = directions::LEFT : direction = directions::RIGHT;
	}
	bool isWithinBounds(int x, int y) const;
	bool isMovableTile(char tile) const;

public:
	ghost() : myGhost() {};
	ghost( Board board,int ghostStartingX, int ghostStartingY)
		: myGhost(ghostStartingX, ghostStartingY)
	{
		this->setBoard(board);
	}

	void moveGhost();
	void setBoard(Board& board)
	{
		myGhost.setBoard(board);
	}
	Board* getBoard() const
	{
		return myGhost.getBoard();
	}
	int getX() const
	{
		return myGhost.getX();
	}
	int getY() const
	{
		return myGhost.getY();
	}
	void drawGhost() const
	{
		myGhost.draw(gameConfig::GHOST);
	}
	void eraseGhost() const
	{
		myGhost.erase();
	}
};


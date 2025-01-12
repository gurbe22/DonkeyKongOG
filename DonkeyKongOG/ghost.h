#pragma once
#include "point.h"
#include "gameConfig.h"
#include "Board.h"
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
public:
	ghost() : myGhost() {};
	ghost(int ghostStartingX, int ghostStartingY, Board board, directions direction)
		: myGhost(ghostStartingX, ghostStartingY)
	{
		this->setBoard(board);
		this->direction = direction;
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
};


#pragma once
#include "Point.h"
class enemy
{
protected:
	point myEnemy;

	// Helper function to check if coordinates are within bounds
	bool isWithinBounds(int x, int y) const;
public:
	enemy(Board& board, int enemyStartingX, int enemyStartingY)
		: myEnemy(enemyStartingX, enemyStartingY)
	{
		this->setBoard(board);
	}
	void setBoard(Board& board)
	{
		myEnemy.setBoard(board);
	}
	Board* getBoard() const
	{
		return myEnemy.getBoard();
	}
	int getX() const
	{
		return myEnemy.getX();
	}
	int getY() const
	{
		return myEnemy.getY();
	}
	virtual void draw() const = 0; // Pure virtual function for drawing the enemy
	
	void erase() const
	{
		myEnemy.erase();
	}
	int getDiffX() const
	{
		return myEnemy.getDiffX();
	}
	int getDiffY() const
	{
		return myEnemy.getDiffY();
	}
};


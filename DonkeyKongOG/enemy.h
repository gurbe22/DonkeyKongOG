#ifndef ENEMY_H
#define ENEMY_H

#include "Point.h"
class Enemy
{
protected:
	Point myEnemy;

	// Helper function to check if coordinates are within bounds
	bool isWithinBounds(int x, int y) const;
public:

	Enemy(Board& board, int enemyStartingX, int enemyStartingY) 
		: myEnemy(enemyStartingX, enemyStartingY)
	{
		this->setBoard(board);
	}

	virtual ~Enemy() = default;

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

	virtual void move(std::vector<Enemy*>& enemies) = 0;

	virtual void move() = 0;

	virtual bool getIsExplode() const = 0;

	int getDiffX() const
	{
		return myEnemy.getDiffX();
	}

	int getDiffY() const
	{
		return myEnemy.getDiffY();
	}

	virtual void changeDirectionX() = 0;

	virtual void changeDirectionY() = 0;
};

#endif
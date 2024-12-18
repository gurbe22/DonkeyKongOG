#ifndef MARIO_H
#define MARIO_H

#include "point.h"
#include <windows.h>

using namespace std;

class mario
{

	static constexpr int MARIO_STARTING_X = 1; 
	static constexpr int MARIO_STARTING_Y = 22; 
	static constexpr int LIVES = 3;
	static constexpr int CHARS_TO_DEATH = 5;
	static constexpr char MARIO = '@'; 
	
	point myMario;
	
	int heightJumping = 0;
	bool jumping = false;
    bool isUp = true;
	int lives = LIVES; //ask keren
	
	// Function to make Mario jump
	void jump(gameConfig::eKeys& key ,char nextChar);

	// Function to make Mario climb
	void climbing(char nextChar, gameConfig::eKeys& key);
	 
	bool isOnFloor()
	{
		char ch1Below = myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 1);
		return (ch1Below == point::FLOOR || ch1Below == point::LFLOOR || ch1Below == point::RFLOOR);

	}

	void draw(char c)
	{
		myMario.draw(c);
	}

	void erase()
	{
		myMario.erase();
	}

	char findNextChar(char currChar, gameConfig::eKeys key)
	{
		int x = myMario.getX();
		int y = myMario.getY();
		switch (key)
		{
		case gameConfig::eKeys::UP:
			if (currChar == point::LADDER)
			{
				myMario.setDiffX(0);
			}
			return myMario.getBoard()->getChar(x + myMario.getDiffX(), y - 1);
		case gameConfig::eKeys::DOWN:
			if (currChar == point::LADDER)
			{
				myMario.setDiffX(0);
			}
			return myMario.getBoard()->getChar(x + myMario.getDiffX(), y + 1);
		case gameConfig::eKeys::LEFT:
			return myMario.getBoard()->getChar(x - 1, y);
		case gameConfig::eKeys::RIGHT:
			return myMario.getBoard()->getChar(x + 1, y);
		default:
			return currChar;
		}
	}

	bool isClimbing(char currChar, char nextChar, gameConfig::eKeys key);

	bool isFalling(char currChar, char nextChar, gameConfig::eKeys key);

	bool isJumping(char currChar, char nextChar, gameConfig::eKeys key);

	void WalkingOrStaying(gameConfig::eKeys key)
	{
		if (key == gameConfig::eKeys::LEFT)
			myMario.move(-1, 0);
		else if (key == gameConfig::eKeys::RIGHT)
			myMario.move(1, 0);
		else if (key == gameConfig::eKeys::STAY)
			myMario.move(0, 0);
	}

	point::States findState(char currChar, char nextChar, gameConfig::eKeys key);

	bool isAlive();

	void setLives()
	{
		lives--;
	}
	

public:
	mario() : myMario(MARIO_STARTING_X, MARIO_STARTING_Y) {};

	void moveMario(gameConfig::eKeys &key);
	
	void setBoard(Board& board)
	{
		myMario.setBoard(board);
	}

	int getLives() const { return lives; }
};

#endif

#ifndef MARIO_H
#define MARIO_H

#include "point.h"

using namespace std;

class mario
{
	point myMario;
	int heightJumping = 0;
	bool jumping = false;
    bool isUp = true;
	
	void jump(gameConfig::eKeys& key ,char nextChar);

	void climbing(char nextChar, gameConfig::eKeys& key);
	 
	bool isOnFloor()
	{
		char ch1Below = myMario.getBoard()->getChar(myMario.getX(), myMario.getY() + 1);
		return (ch1Below == FLOOR || ch1Below == LFLOOR || ch1Below == RFLOOR);

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
			return myMario.getBoard()->getChar(x, y - 1);
		case gameConfig::eKeys::DOWN:
			return myMario.getBoard()->getChar(x, y + 1);
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

public:
	
	void moveMario(gameConfig::eKeys &key);
	
	void setBoard(Board& board)
	{
		myMario.setBoard(board);
	}
};

#endif

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
	
	point myMario;
	
	int heightJumping = 0;
	bool jumping = false;
    bool isUp = true;
	int lives = LIVES; //ask keren
	
	// Function to make Mario jump
	void jump(gameConfig::eKeys& key ,char nextChar);

	// Function to make Mario climb
	void climbing(char nextChar, gameConfig::eKeys& key);

	char findNextChar(char currChar, gameConfig::eKeys key);

	bool isClimbing(char currChar, char nextChar, gameConfig::eKeys key);

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

	point::States findMarioState(char currChar, char nextChar, gameConfig::eKeys key);

	bool isAlive();

	void setLives()
	{
		lives--;
	}

public:

    static constexpr char MARIO = '@'; 

	mario() : myMario(MARIO_STARTING_X, MARIO_STARTING_Y) {}; 

	void moveMario(gameConfig::eKeys &key);
	
	void setBoard(Board& board)
	{
		myMario.setBoard(board);
	}

	int getLives() const { return lives; }

	void setMarioToStart()
	{
		myMario.setX(MARIO_STARTING_X);
		myMario.setY(MARIO_STARTING_Y);
	}

	void makeDeath()
	{
		lives = 0;
	}
};

#endif

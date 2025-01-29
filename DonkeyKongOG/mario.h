
#ifndef MARIO_H
#define MARIO_H

#include "point.h"
#include "gameConfig.h"
#include "barrel.h"
#include "ghost.h"
#include "specialGhost.h"
#include "enemy.h"
// The 'mario' class manages the behavior and state of Mario in the game.
class Mario
{
	// Constants for Mario's starting position, lives, and death criteria

	static constexpr int INITIAL_LIVES = 3;
	static constexpr int CHARS_TO_DEATH = 5;
	static constexpr int BARREL_SCORE = 50;
	static constexpr int GHOST_SCORE = 100;
	static constexpr int SPECIAL_GHOST_SCORE = 200;

	// Member variables
	Point myMario; // Represents Mario as a point on the board 
	int marioStartingX = 0; // Starting X position
	int marioStartingY = 0; // Starting Y position
	int heightJumping = 0; // Tracks how high Mario is jumping
	bool jumping = false; // Indicates if Mario is currently jumping
	bool isUp = true; // Tracks the direction of Mario's jump
	int lives = INITIAL_LIVES; // Current number of lives Mario has
	bool isHammer = false; // Indicates if Mario has a hammer
	int score = 0; // Current score
	int hammerDirection = 0; // Hammer direction
	GameConfig::eKeys prevKey = GameConfig::eKeys::STAY; // Previous key

	// Helper methods
	void jump(GameConfig::eKeys& key, char nextChar);
	void climb(char nextChar, GameConfig::eKeys& key);
	void walkingOrStaying(GameConfig::eKeys key);
	void hammering(std::vector<Enemy*>& enemies);

	bool isClimbing(char currChar, char nextChar, GameConfig::eKeys key) const;
	bool isJumping(char currChar, char nextChar, GameConfig::eKeys key);
	bool isAlive() const;
	bool isMarioDisqualified(std::vector<Enemy*>& enemies, int nextChar) const;
	bool isCollision(int marioX, int marioY, int marioNextX, int marioNextY, int enemyX, int enemyY, int enemyNextX, int enemyNextY) const;
	bool isInExplosionRadius(int marioX, int marioY, int barrelX, int barrelY) const;

	char findNextChar(char currChar, GameConfig::eKeys key);
	Point::States findMarioState(char currChar, char nextChar, GameConfig::eKeys key);


public:

	// Constructors
	Mario() = default;

	// Gameplay-related methods
	void drawMario() const {
		myMario.draw(GameConfig::MARIO);
	}
	void eraseMario() const
	{
		int x = myMario.getX();
		int y = myMario.getY();
		char currChar = myMario.getBoard()->getChar(x, y); // Retrieves the character at the point's position on the board
		if (currChar == GameConfig::HAMMER)
		{
			myMario.eraseCompletely();   
		}
		else
		{
			myMario.erase();
		}
	}
	void moveMario(GameConfig::eKeys& key, std::vector<Enemy*>& enemies);
	void makeDeath() { lives = 0; }

	// State-related methods
	int getLives() const { return lives; }
	int getScore() const { return score; }
	int getIsHammer() const { return isHammer; }
	void addScore(int newPoints);
	bool isWon() const;

	// Board interaction
	void setBoard(Board& board) { myMario.setBoard(board); }
	void setMarioToStart()
	{
		isHammer = false;
		jumping = false;

		myMario.setDiffX(0);
		myMario.setDiffY(0);
		myMario.setX(marioStartingX);
		myMario.setY(marioStartingY);
	}

	void setStartingX(int startingX) { marioStartingX = startingX; }
	void setStartingY(int startingY) { marioStartingY = startingY; }

	void setHammerDirection();
	void setHammerDirection(int dir);

	// Decrements Mario's life count
	void setLives() { lives--; }
};

#endif
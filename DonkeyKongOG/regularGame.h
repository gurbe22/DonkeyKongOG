#ifndef REGULARGAME_H
#define REGULARGAME_H
#include "game.h"

class RegularGame: public Game
{
	// Function to initialize game data
	void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results);

	// Function to process the Game Input
	bool processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed);

	// Function to go to sleep
	void goToSleep() const override { Sleep(GAME_SPEED); }

public:
	RegularGame() : Game() {}   
	~RegularGame() {}
};

#endif
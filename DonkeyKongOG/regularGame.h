#ifndef REGULARGAME_H
#define REGULARGAME_H
#include "game.h"

class RegularGame: public Game
{
	void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results);
	bool processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed);
	void goToSleep() const override { Sleep(GAME_SPEED); }
public:
	RegularGame() : Game() {}   
};

#endif
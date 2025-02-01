#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "game.h"

class SaveGame : public Game
{
	void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results) ;
	bool processGameInput(Steps& steps, Results& results, int iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed)override;
	void goToSleep() const override { Sleep(GAME_SPEED); }
	void handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, int iteration, Results& results, std::string filename) override;
	void handleGameResult(bool victory,bool winLevel, int iteration, Steps& steps, Results& results, std::string stepsFileName, std::string resultsFileName, bool& unmatching_result_found, std::string filename) override ;
public:
	SaveGame() : Game() {}
	
};
#endif
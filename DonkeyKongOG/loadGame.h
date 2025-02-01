#ifndef LOADGAME_H
#define LOADGAME_H

#include "steps.h"
#include "results.h"
#include "game.h"

class LoadGame : public Game
{
	void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results) override;

	void validateResultsAndUpdateDisqualificationIteration(Results& results, size_t& iteration, size_t& nextDisqualificationIteration, bool& unmatching_result_found, std::string filename) override;

	bool processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed) override;

	virtual void goToSleep() const override;

	void handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, size_t iteration, Results& results, std::string filename) override;

	bool checkIfDisqualificationMatch(size_t iteration, size_t nextDisqualificationIteration, bool& unmatching_result_found, std::string filename) override;

	void handleGameResult(bool victory, bool winLevel, size_t iteration, Steps& steps, Results& results, std::string stepsFileName, std::string resultsFileName, bool& unmatching_result_found, std::string filename) override;
public:
	LoadGame() : Game() {}
	~LoadGame() {}
	virtual void mainMenu() override; 
};

#endif
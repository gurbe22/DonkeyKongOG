#include "loadGame.h"

// Loads game data, including steps and results, and extracts the random seed
void LoadGame::initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results)
{
	steps = Steps::loadSteps(stepsFilename);
	randomSeed = steps.getRandomSeed();
	results = Results::loadResults(resultsFilename);
}
// Validates results file and updates the next disqualification iteration
void LoadGame::validateResultsAndUpdateDisqualificationIteration(Results& results, size_t& iteration, size_t& nextDisqualificationIteration, bool& unmatching_result_found, std::string filename)
{
	if (results.isFinishedBy(iteration)) {
		reportResultError("Results file reached finish while game hadn't!", filename, iteration);
		unmatching_result_found = true;
	}
	else {
		nextDisqualificationIteration = results.getNextDisqualificationIteration();
	}
}
// Processes game input from the recorded steps
bool LoadGame::processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed)
{
	if (steps.isNextStepOnIteration(iteration)) {
		int key = steps.popStep();
		key = std::tolower(key);

		if(key == int(GameConfig::eKeys::ESC)) 
		{
			key = steps.popStep();
			key = std::tolower(key);

			if (key == (int)GameConfig::eKeys::EXIT)
			{
				mario.makeDeath();
				return true;
			}
			else if (key == (int)GameConfig::eKeys::ESC)
			{
				return false;
			}
			else if (key == (int)GameConfig::eKeys::SUICIDE)
			{
				mario.setLives();	
				if (mario.getLives() > 0)
				{
					board.displayDisqualified();
					Sleep(1000);
				}
				return true;
			}
		}
		keyPressed = (GameConfig::eKeys)key; 
	}
	return false;
}	

// Adds a delay to control game speed
void LoadGame::goToSleep() const
{
	Sleep(LOAD_GAME_SPEED);
}
//Handles disqualification events and verifies correctness in results file
void LoadGame::handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, size_t iteration, Results& results, std::string filename)
{
	// check if the result is correct
	if (results.popResult() != std::pair { iteration, Results::ResultValue::disqualified }) {
		reportResultError("Results file doesn't match disqualification event!", filename, iteration);
		unmatching_result_found = true;
	}
	nextDisqualificationIteration = results.getNextDisqualificationIteration();
}

// Checks if a disqualification event occurred as expected
bool LoadGame::checkIfDisqualificationMatch(size_t iteration, size_t nextDisqualificationIteration,bool& unmatching_result_found, std::string filename)
{
	// we didn't disqualified, so we check if the result is correct
	if (iteration == nextDisqualificationIteration) {
		reportResultError("Results file has a disqualification event that didn't happen!", filename, iteration);
		unmatching_result_found = true;
		return true;
	}
	return false;
}

// Verifies if the game result matches the expected outcome in the results file
void LoadGame::handleGameResult(bool victory, bool winLevel, size_t iteration, Steps& steps, Results& results, std::string stepsFileName, std::string resultsFileName, bool& unmatching_result_found, std::string filename)
{
	if (!unmatching_result_found) 
	{
		auto result = results.popResult();
		if (victory)
		{
			if(result.second != Results::victory )
			{
				reportResultError("Results file doesn't match finished in victory event!", filename, iteration);
				unmatching_result_found = true;
			}
		}
		else if (winLevel)
		{
			if (result.second !=  Results::wonLevel )
			{
				reportResultError("Results file doesn't match finished in winning the level event!", filename, iteration);
				unmatching_result_found = true;
			}
		}
		else 
		{
			if (result.second != Results::lose)
			{
				reportResultError("Results file doesn't match finished in losing event!", filename, iteration);
				unmatching_result_found = true;
			}
		}

		if (results.popResult().second != Results::noResult) {
			reportResultError("Results file has additional events after finish event!", filename, iteration);
			unmatching_result_found = true;
		}
	}
}
// Loads level files and starts the game 
void LoadGame::mainMenu() 
{
	std::vector<std::string> fileNames;
	ShowConsoleCursor(false); // Hide the cursor
	getAllBoardFileNames(fileNames);
	sort(fileNames.begin(), fileNames.end());

	runGame(fileNames);
}
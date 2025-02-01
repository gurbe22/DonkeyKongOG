#include "saveGame.h"
using namespace std;

void SaveGame::initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results)
{
	randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	steps.setRandomSeed(randomSeed);
}

bool SaveGame::processGameInput(Steps& steps, Results& results, int iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed)
{
	if (_kbhit())
	{
		int key = _getch();

		key = std::tolower(key);

		// Handle pause functionality
		if (isPause(board, key))
		{
			steps.addStep(iteration, (char)GameConfig::eKeys::ESC);
			if (key == (int)GameConfig::eKeys::EXIT)
			{
				// End game if exit is chosen
				steps.addStep(iteration, key);
				mario.makeDeath();
				return true;
			}
			else if (key == (int)GameConfig::eKeys::ESC)
			{
				// Reset and redisplay the board on resume
				board.reset();
				displayBoard(board, mario, false);
			}
			else if (key == (int)GameConfig::eKeys::SUICIDE)
			{
				steps.addStep(iteration, key);
				mario.setLives();
				if (mario.getLives() > 0)
				{
					board.displayDisqualified();
					Sleep(2000);
					results.addResult(iteration, Results::disqualified);
				}
				return true;
			}
		}

		//Update the key pressed
		keyPressed = (GameConfig::eKeys)key;
		steps.addStep(iteration, key); 
	}

	return false;
}

void SaveGame::handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, int iteration, Results& results, string filename)
{
	results.addResult(iteration, Results::disqualified);
}

void SaveGame::handleGameResult(bool victory,bool winLevel, int iteration, Steps& steps, Results& results, string stepsFileName, string resultsFileName, bool& unmatching_result_found, std::string filename)
{
	if(victory)
		results.addResult(iteration, Results::victory);
	else if(winLevel)
		results.addResult(iteration, Results::wonLevel);
	else
	{
		results.addResult(iteration, Results::lose);
	}

	steps.saveSteps(stepsFileName);
	results.saveResults(resultsFileName); 
}


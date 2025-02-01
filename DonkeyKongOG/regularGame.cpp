#include "regularGame.h"

void RegularGame::initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results)
{
	randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
}

bool RegularGame::processGameInput(Steps& steps, Results& results, int iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed)
{
	if (_kbhit())
	{
		int key = _getch();

		key = std::tolower(key);

		// Handle pause functionality
		if (isPause(board, key))
		{
			if (key == (int)GameConfig::eKeys::EXIT)
			{
				// End game if exit is chosen
				mario.makeDeath();
				return true;
			}
			else if (key == (int)GameConfig::eKeys::ESC)
			{
				// Reset and redisplay the board on resume
				board.reset();
				displayBoard(board, mario , false); 
			}
			else if (key == (int)GameConfig::eKeys::SUICIDE)
			{
				mario.setLives();
				if (mario.getLives() > 0)
				{
					board.displayDisqualified();
					Sleep(GameConfig::DISPLAY_SPEED);
				}
				return true;;
			}
		}

		//Update the key pressed
		keyPressed = (GameConfig::eKeys)key;
	}

	return false;
}

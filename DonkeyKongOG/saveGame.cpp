#include "saveGame.h"
using namespace std;

void SaveGame::initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results)
{
    // Set the random seed based on the current system time
    randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
    steps.setRandomSeed(randomSeed); // Pass the seed to the steps object
}

bool SaveGame::processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed)
{
    if (_kbhit()) // Check if a key has been pressed
    {
        int key = _getch(); // Get the key pressed
        key = std::tolower(key); // Convert the key to lowercase

        // Handle pause functionality
        if (isPause(board, key))
        {
            steps.addStep(iteration, (char)GameConfig::eKeys::ESC); // Add step for pause
            if (key == (int)GameConfig::eKeys::EXIT)
            {
                // End the game if exit is chosen
                steps.addStep(iteration, key);
                mario.makeDeath(); // Mark Mario as dead
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
                mario.setLives(); // Reset Mario's lives
                if (mario.getLives() > 0)
                {
                    board.displayDisqualified(); // Display disqualification message
                    Sleep(GameConfig::DISPLAY_SPEED); // Wait for the message to be seen
                    results.addResult(iteration, Results::disqualified); // Record disqualification
                }
                return true;
            }
        }

        // Update the key pressed
        keyPressed = (GameConfig::eKeys)key;
        steps.addStep(iteration, key); // Add the step for the key pressed
    }

    return false; // No need to process further
}

void SaveGame::handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, size_t iteration, Results& results, string filename)
{
    results.addResult(iteration, Results::disqualified); // Record disqualification in results
}

void SaveGame::handleGameResult(bool victory, bool winLevel, size_t iteration, Steps& steps, Results& results, string stepsFileName, string resultsFileName, bool& unmatching_result_found, std::string filename)
{
    // Update the results based on the game outcome
    if (victory)
        results.addResult(iteration, Results::victory); // Record victory
    else if (winLevel)
        results.addResult(iteration, Results::wonLevel); // Record level win
    else
    {
        results.addResult(iteration, Results::lose); // Record loss
    }

    // Save the steps and results to their respective files
    steps.saveSteps(stepsFileName);
    results.saveResults(resultsFileName);
}

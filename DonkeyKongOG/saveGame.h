#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "game.h"

class SaveGame : public Game
{
    // Initializes game data from files and sets random seed
    void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results);

    // Processes game input and updates game state
    bool processGameInput(Steps& steps, Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed) override;

    // Pauses the game for a predefined duration
    void goToSleep() const override { Sleep(GAME_SPEED); }

    // Handles disqualification during the game
    void handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found, size_t iteration, Results& results, std::string filename) override;

    // Stores the game result to files
    void handleGameResult(bool victory, bool winLevel, size_t iteration, Steps& steps, Results& results, std::string stepsFileName, std::string resultsFileName, bool& unmatching_result_found, std::string filename) override;

public:
    SaveGame() : Game() {}
    ~SaveGame() {}
};

#endif

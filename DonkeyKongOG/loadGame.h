#ifndef LOADGAME_H
#define LOADGAME_H

#include "steps.h"
#include "results.h"
#include "game.h"

// 'LoadGame' class handles game execution using pre-recorded steps and results.
class LoadGame : public Game
{
    // Initializes game data from recorded step and result files.
    void initializeGameData(std::string stepsFilename, std::string resultsFilename,
        long& randomSeed, Steps& steps, Results& results) override;

    // Validates the results and checks for disqualification cases.
    void validateResultsAndUpdateDisqualificationIteration(Results& results, size_t& iteration,
        size_t& nextDisqualificationIteration,
        bool& unmatching_result_found,
        std::string filename) override;

    // Processes user input during the game (specific to loaded games).
    bool processGameInput(Steps& steps, Results& results, size_t iteration,
        Board& board, Mario& mario, GameConfig::eKeys& keyPressed) override;

    // Controls game speed (likely used to match recorded game timing).
    virtual void goToSleep() const override;

    // Handles player disqualification if a mismatch is found in results.
    void handleDisqualification(size_t& nextDisqualificationIteration, bool unmatching_result_found,
        size_t iteration, Results& results, std::string filename) override;

    // Checks if the current iteration matches the disqualification condition.
    bool checkIfDisqualificationMatch(size_t iteration, size_t nextDisqualificationIteration,
        bool& unmatching_result_found, std::string filename) override;

    // Processes the game result (win, loss, or disqualification).
    void handleGameResult(bool victory, bool winLevel, size_t iteration, Steps& steps,
        Results& results, std::string stepsFileName,
        std::string resultsFileName, bool& unmatching_result_found,
        std::string filename) override;

public:
    LoadGame() : Game() {}  // Default constructor
    ~LoadGame() {}          // Destructor

    // Displays the main menu for the loaded game mode.
    virtual void mainMenu() override;
};

#endif

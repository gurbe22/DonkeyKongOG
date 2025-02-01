#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h> // For _kbhit and _getch
#include <algorithm>
#include "gameConfig.h"
#include "board.h"
#include "mario.h"
#include "barrel.h" 
#include "ghost.h" 
#include "specialGhost.h"
#include "enemy.h"
#include <vector>
#include "steps.h"
#include "results.h"
// The 'Game' class orchestrates the gameplay, including player interactions,
// barrel movements, and game state management.
class Game
{
	int level = 0; // The current level of the game
    // Constants for menu options and game states

    static constexpr char START_NEW_GAME = '1';        // Option to start the game
    static constexpr char START_NEW_SPECIFC_LEVEL = '2';        // Option to start the game
    static constexpr char SHOW_INSTRUCTIONS = '8';     // Option to view instructions
    static constexpr char EXIT_GAME = '9';        // Option to exit the game
    static constexpr bool RUNNING = true;         // Game is running
    static constexpr bool STOP_RUNNING = false;   // Game is stopped
	static constexpr int DELAY = 30;	  // Delay for the barrels
	static constexpr int LEVELS_PER_PAGE = 2;	  // 
	static constexpr int ANIMATION_SPEED = 30;	  //
	  //

    // Internal helper methods
    void createAllGhosts(std::vector<Enemy*>& enemies, Board board);
    void eraseEnemies(std::vector<Enemy*>& enemies);
    void eraseAllCharacters(std::vector<Enemy*>& enemies, Mario& mario);
    void moveEnemies(std::vector<Enemy*>& enemies, bool isSilent = false);

    // Display-related methods
    void displayInstructions() const;
    int displayLevelsChoices(std::vector<std::string>& fileNames) const;
    void displayMenuWithAnimation() const;
    void displayTitleWithAnimation() const;
    void displayDonkyKongArtWithAnimation() const;
	void displayOptionsWithAnimation() const;
    void printWithAnimation(const std::vector<std::string>& lines, unsigned int delayMs = 100) const;

    // Game state management
    void setMarioPos(Board& board, Mario& mario);
    void setScoreLine(Board& board, Mario& mario);
    void setLevelLine(Board& board);
    void setLivesChar(Board& board, Mario& mario);
    void setHammer(Board& board, Mario& mario);

protected:
	static constexpr int GAME_SPEED = 100;
    static constexpr int LOAD_GAME_SPEED = 50;
    static constexpr int LOAD_SILENT_GAME_SPEED = 0;

    virtual void initializeGameData(std::string stepsFilename, std::string resultsFilename, long& randomSeed, Steps& steps, Results& results) = 0; 
    virtual void validateResultsAndUpdateDisqualificationIteration(Results& results, size_t& iteration, size_t& nextDisqualificationIteration, bool& unmatching_result_found, std::string filename) {}
    virtual bool processGameInput(Steps& steps,Results& results, size_t iteration, Board& board, Mario& mario, GameConfig::eKeys& keyPressed) = 0;
    virtual void goToSleep() const = 0;
    virtual void handleDisqualification(size_t& nextDisqualificationIteration,bool unmatching_result_found , size_t iteration, Results& results, std::string filename) {}
    virtual bool checkIfDisqualificationMatch(size_t iteration, size_t nextDisqualificationIteration, bool& unmatching_result_found, std::string filename) { return false; }
    virtual void handleGameResult(bool victory,bool winLevel, size_t iteration, Steps& steps, Results& results, std::string stepsFileName, std::string resultsFileName, bool& unmatching_result_found, std::string filename) {};
    
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	bool isPause(Board& board, int& key) const;
	void displayBoard(Board& board, Mario& mario, bool isSilent);

    void reportResultError(const std::string& message, const std::string& filename, size_t iteration);

	void runGame(std::vector<std::string> fileNames, int levelChoice = 0, bool isSilent = false);
public:
    Game() {}
	virtual ~Game() {}
    // Displays the main menu and manages user input
    virtual void mainMenu();
	
};

#endif

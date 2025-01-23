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
#include <vector>

// The 'Game' class orchestrates the gameplay, including player interactions,
// barrel movements, and game state management.
class Game
{
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

	int level = 0; // The current level of the game


    // Internal helper methods
    void moveBarrels(std::vector<Barrel>& barrels);
    void eraseBarrels(std::vector <Barrel>& barrels);
    void createAllGhosts(std::vector<Ghost>& ghosts, Board board);
    void moveGhosts(std::vector<Ghost>& ghosts);
    void eraseGhosts(std::vector<Ghost>& ghosts);


    // Display-related methods
    void displayInstructions() const;
    void displayBoard(Board& board, Mario& mario);
    int displayLevelsChoices(std::vector<std::string>& fileNames) const;
    void displayMenuWithAnimation() const;
    void displayTitleWithAnimation() const;
    void displayDonkyKongArtWithAnimation() const;
	void displayOptionsWithAnimation() const;
    void printWithAnimation(const std::vector<std::string>& lines, int delayMs = 100) const;


    // Game state management
    bool isPause(Board& board, int& key) const;
    void setMarioPos(Board& board, Mario& mario);
    void setScoreLine(Board& board, Mario& mario);
    void setLevelLine(Board& board, Mario& mario);
    void setLivesChar(Board& board, Mario& mario);

 
    void runGame(std::vector<std::string> fileNames, int levelChoice = 0);
    void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);

    void eraseAllCharacters(std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts, Mario& mario);
    void moveEnemies(std::vector<Barrel>& barrels, std::vector<Ghost>& ghosts);
public:
    // Displays the main menu and manages user input
    void mainMenu();
};

#endif

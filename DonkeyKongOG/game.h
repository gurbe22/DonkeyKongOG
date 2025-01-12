#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h> // For _kbhit and _getch
#include <algorithm>
#include "gameConfig.h"
#include "Board.h"
#include "mario.h"
#include "barrel.h" 

using namespace std;

// The 'game' class orchestrates the gameplay, including player interactions,
// barrel movements, and game state management.
class game
{
    // Constants for menu options and game states
    static constexpr char START_NEW_GAME = '1';        // Option to start the game
    static constexpr char SHOW_INSTRUCTIONS = '8';     // Option to view instructions
    static constexpr char EXIT_GAME = '9';        // Option to exit the game
    static constexpr bool RUNNING = true;         // Game is running
    static constexpr bool STOP_RUNNING = false;   // Game is stopped

	int level = 0; // The current level of the game

    // Moves the barrels across the board with a specified delay
    void moveBarrels( vector<Barrel> &barrels, Board board);

    // Erases the barrels from their current positions
    void eraseBarrels(vector <Barrel> &barrels);

    // Runs the main game loop
    void runGame();

    //
    void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);

    // Displays the instructions for the game
    void displayInstructions();

    // Displays the game board and updates it with Mario's position
    void displayBoard(Board& board, mario& mario);

    // Checks if the game is paused and handles pause state
    bool isPause(Board& board, int& key);

    void setCharactersPos(Board& board, mario& mario /*, vector<Ghost> ghosts */);

public:
    // Displays the main menu and manages user input
    void mainMenu();
};

#endif

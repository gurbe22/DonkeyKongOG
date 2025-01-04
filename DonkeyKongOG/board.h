#ifndef BOARD_H
#define BOARD_H
 
#include "gameConfig.h"
//#include <cstring>
#include "utils.h"
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

// The 'Board' class manages the game board, including its initial state and updates during gameplay.
class Board
{
    // The initial state of the board (original layout)
    char* originalBoard[gameConfig::GAME_HEIGHT];

    // Current state of the board (modifiable during gameplay)
    char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1]; // +1 for null terminator

public:
    // Resets the board to its original state
    void reset();

    // Prints the current state of the board to the console
    void print() const;

    // Retrieves the character at a specific position on the board
    char getChar(int x, int y) const {
        return currentBoard[y][x];
    }

    // Sets a character at a specific position on the board
    void setChar(int x, int y, char c) {
        currentBoard[y][x] = c;
    }

    

    //
    void load(const std::string& filename, int& marioStartingX, int& marioStartingY);

    //void setStartingX(int startingX) { marioStartingX = startingX; } 

    //void setStartingY(int startingY) { marioStartingY = startingY; } 

    //int getStartingX() const { return marioStartingX; }

    //int getStartingY() const { return marioStartingY; }

    // Displays a pause screen to the player
    void displayPauseScreen();

    // Displays a victory screen to the player
    void displayVictory();

    // Displays a disqualified screen to the player
    void displayDisqualified();

    // Displays a loss screen to the player
    void displayLoss();
};

#endif
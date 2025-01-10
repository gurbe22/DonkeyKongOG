#ifndef BOARD_H
#define BOARD_H
 
#include "gameConfig.h"
//#include <cstring>
#include "utils.h"
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <utility> // For std::pair

// The 'Board' class manages the game board, including its initial state and updates during gameplay.
class Board
{
    static constexpr int LIVES_INDENTATION_X = 12;
    static constexpr int LIVES_INDENTATION_Y = 1;
    static constexpr int INFO_WIDTH = 20;
    static constexpr int INFO_HEIGHT = 3;

    // The initial state of the board (original layout)
    char originalBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1];

    // Current state of the board (modifiable during gameplay)
    char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1]; // +1 for null terminator

    int marioStartingX;
    int marioStartingY;

    int donkeyPosX;
    int donkeyPosY;

	std::vector<std::pair<int, int>> ghostPos;//ask Amir

    int infoPosX;
    int infoPosY;

    void addInfo(int infoPosX, int infoPosY);

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

    int getLivesPositionX() const
    {
        return infoPosX + LIVES_INDENTATION_X;
    }

	int getLivesPositionY() const
	{
        return infoPosY + LIVES_INDENTATION_Y;
	}

	void setLivesPosition(int x, int y)
	{
		infoPosX = x;
		infoPosY = y;
	}
    //
    void load(const std::string& filename);

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

    int getDonkeyPosX() const
    {
        return donkeyPosX;
    }

    int getDonkeyPosY() const
    {
		return donkeyPosY;
    }

	int getMarioStartingX() const
	{
		return marioStartingX;
	}

    int getMarioStartingY() const
    {
		return marioStartingY;
    }

	// vector<int[2]> getGhostPos() const
	// {
		
	// }
};

#endif
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
#include <algorithm>

// The 'Board' class manages the game board, including its initial state and updates during gameplay.
class Board
{
    static constexpr int LIVES_INDENTATION_X = 9;
    static constexpr int LIVES_INDENTATION_Y = 2;

    static constexpr int LEVEL_INDENTATION_X = 12;
    static constexpr int LEVEL_INDENTATION_Y = 0;
    
	static constexpr int HAMMER_INDENTATION_X = 19;
	static constexpr int HAMMER_INDENTATION_Y = 2;

	static constexpr int SCORE_INDENTATION_X = 12;
	static constexpr int SCORE_INDENTATION_Y = 1;

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

	std::vector<std::pair<int, int>> ghostPos;

    int infoPosX;
    int infoPosY;

    void addInfo(int infoPosX, int infoPosY);
    bool handleSpecialChar(char c, int& curr_row, int &curr_col, bool& isPaulineFound, bool& isDonkeyKongFound, bool& isHammerFound, bool& isMarioFound, bool& isInfoFound);
    void addFloor(char* row, int width);
    bool isDonkeyKongInLegalPlace();
    
    int getMaxNewPointIndentation() const;
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
	/*void setLivesPosition(int x, int y)
	{
		infoPosX = x;
		infoPosY = y;
	}*/



	int getHammerPositionX() const
	{
		return infoPosX + HAMMER_INDENTATION_X;
	}
	int getHammerPositionY() const
	{
		return infoPosY + HAMMER_INDENTATION_Y;
	}

    


	int getLevelPositionX() const
	{
		return infoPosX + LEVEL_INDENTATION_X;
	}
	int getLevelPositionY() const
	{
		return infoPosY + LEVEL_INDENTATION_Y;
	}

    int getScorePositionX() const
    {
        return infoPosX + SCORE_INDENTATION_X;
    }
    int getScorePositionY() const
    {
        return infoPosY + SCORE_INDENTATION_Y;
    }


    //
    bool load(const std::string& filename);

    // Displays a pause screen to the player
    void displayPauseScreen();

    // Displays a victory screen to the player
    void displayVictory();

    void displayErrorNoFiles();

    void displayErrorUnacceptableCharacter();

    void displaySignificantCharacterMissing();

    void displayLoadingFileFailed();

    void displayDonkeyKongInIllegalPlace();

    void displayErrorNotExistFile();

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

	std::vector<std::pair<int, int>>& getGhostPos()
    {
        return ghostPos;
    }

	void resetGhostPos()
	{
		ghostPos.clear();
	}

    void addScore(int score, int returningX, int returningY);

    void printScore(int score, int returningX, int returingY, int indentation) const;

    void setLine(std::string line ,int posX, int posY);

    int getNewScoreIndetation(int score) const;
};

#endif
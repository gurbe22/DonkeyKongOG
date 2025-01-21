#ifndef BOARD_H
#define BOARD_H
 
#include "gameConfig.h"
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

    

    // Board representation
    char originalBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1];
    char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1];

    //// Positions
    int marioStartingX;
    int marioStartingY;

    int donkeyPosX;
    int donkeyPosY;

	std::vector<std::pair<int, int>> ghostPos;

    int infoPosX;
    int infoPosY;

    // Helper methods
    void addInfo(int infoPosX, int infoPosY);
    bool handleSpecialChar(char c, int& curr_row, int &curr_col, bool& isPaulineFound, bool& isDonkeyKongFound, bool& isHammerFound, bool& isMarioFound, bool& isInfoFound);
    void addFloor(char* row, int width);
    bool isDonkeyKongInLegalPlace() const;
    
    int getMaxNewPointIndentation() const;
public:
    
    // Board management
    void reset();
    void print() const;
    bool load(const std::string& filename);


    // Board character manipulation
    char getChar(int x, int y) const { return currentBoard[y][x]; }
    void setChar(int x, int y, char c) { currentBoard[y][x] = c; }
    void setLine(std::string line, int posX, int posY);

    // Info section getters
    int getLivesPositionX() const
    {
        return infoPosX + LIVES_INDENTATION_X;
    }
	int getLivesPositionY() const
	{
        return infoPosY + LIVES_INDENTATION_Y;
	}

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

    // Error displays
    void displayErrorNoFiles();
    void displayErrorUnacceptableCharacter();
    void displaySignificantCharacterMissing();
    void displayLoadingFileFailed();
    void displayDonkeyKongInIllegalPlace();
    void displayErrorNotExistFile();

    // Game state displays
    void displayPauseScreen();
    void displayVictory();
    void displayDisqualified();
    void displayLoss();

    //Key positions getters
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

    // Ghost management
	std::vector<std::pair<int, int>>& getGhostPos()
    {
        return ghostPos;
    }
	void resetGhostPos()
	{
		ghostPos.clear();
	}

    // Score handling
    void addScore(int score, int returningX, int returningY);
    void printScore(int score, int returningX, int returningY, int indentation) const;


    int getNewScoreIndetation(int score) const;
};

#endif
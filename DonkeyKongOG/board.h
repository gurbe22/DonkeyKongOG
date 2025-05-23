#ifndef BOARD_H
#define BOARD_H
 
#include "GameConfig.h"
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
    char originalBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]{};
    char currentBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH + 1]{};

    //// Positions
    int marioStartingX;
    int marioStartingY;

    int donkeyPosX;
    int donkeyPosY;

	std::vector<std::pair<int, int>> ghostPos;
	std::vector<std::pair<int, int>> specialGhostPos;

    int infoPosX;
    int infoPosY;

    int hammerPosX;
    int hammerPosY;

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

	int getHammerStatusPositionX() const
	{
		return infoPosX + HAMMER_INDENTATION_X;
	}
	int getHammerStatusPositionY() const
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
    int getHammerPositionX() const
    {
        return hammerPosX;
    }
	int getHammerPositionY() const
	{
		return hammerPosY;
	}

    // Ghost management
	std::vector<std::pair<int, int>>& getGhostPos()
    {
        return ghostPos;
    }

    std::vector<std::pair<int, int>>& getSpecialGhostPos()
    {
        return specialGhostPos;
    }
	void resetGhostPos()
	{
		ghostPos.clear();
		specialGhostPos.clear();
	}

    // Score handling
    void addScore(int score, int returningX, int returningY);
    void printScore(int score, int returningX, int returningY, int indentation) const;
    int getNewScoreIndetation(int score) const;

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
    void displayWonLevel();
};

#endif
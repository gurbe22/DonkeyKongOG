#ifndef GAME_H

#define GAME_H

#include <iostream>
#include <conio.h> // For _kbhit and _getch
#include <windows.h> // For Sleep and gotoxy

#define RUNNING true
#define STOP_RUNNING false

//#include "Board.h"
//#include "gameConfig.h"
#include "mario.h"

using namespace std;

class game
{
	
public:
	// Main menu function
	void mainMenu();

	// Function to run the game
	void runGame();

	// Function to display instructions
	void displayInstructions();

	// Function to display the game board
	void displayBoard(Board& b);
};

#endif

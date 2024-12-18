#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h> // For _kbhit and _getch
#include <windows.h> // For Sleep and gotoxy

//#include "Board.h"
//#include "gameConfig.h"
#include "mario.h"

using namespace std;

class game
{
	static constexpr char START_GAME = '1';
	static constexpr char INSTRUCTIONS = '8';  
	static constexpr char EXIT_GAME = '9';  
	static constexpr bool RUNNING = true;
	static constexpr bool STOP_RUNNING = false; 
	
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

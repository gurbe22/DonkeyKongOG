#pragma once

#include <iostream>
#include <conio.h> // For _kbhit and _getch
#include <windows.h> // For Sleep and gotoxy
#include "Board.h"
#include "TheDonkyKongGame.h"
#include "gameConfig.h"
using namespace std;

class menu
{
public:
	// Main menu function
	void mainMenu();

	// Function to run the game
	void runGame();

	// Function to display instructions
	void displayInstructions();

	// Function to display the game board
	void displayBoard(Board b);
};


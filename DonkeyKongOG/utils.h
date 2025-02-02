#ifndef UTILS_H
#define UTILS_H

#include <windows.h>  // For gotoxy function (move cursor)
#include <process.h>  // For system function (console commands)
#include <iostream>   // For cout (output to console)

// Show or hide the console cursor based on the flag
void ShowConsoleCursor(bool showFlag);

// Move the console cursor to the specified (x, y) position
void gotoxy(int x, int y);

// Clear the console screen
void clear_screen();

// Calculate and return the bending direction for X
int bendingDirX(const int posX);

// Calculate and return the bending direction for Y
int bendingDirY(const int posY);

#endif

#ifndef UTILS_H
#define UTILS_H

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream> // for cout

void ShowConsoleCursor(bool showFlag);
void gotoxy(int, int);
void clear_screen();
int bendingDirX(const int posX);
int bendingDirY(const int posY);
#endif
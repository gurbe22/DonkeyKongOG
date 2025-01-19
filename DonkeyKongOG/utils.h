#ifndef UTILS_H
#define UTILS_H

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream> // for cout

using namespace std;

void ShowConsoleCursor(bool showFlag);
void gotoxy(int, int);
void clear_screen();
int bendingDir(const int posX);

#endif
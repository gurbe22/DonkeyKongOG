#ifndef MARIO_H
#define MARIO_H
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <process.h>

#include "point.h"
using namespace std;
class mario
{
	point myMario;
public:
	void move(gameConfig::eKeys key);  
	void draw(char c);
	void erase(); 
};

#endif

#ifndef THEDONKYKONGGAME_H
#define THEDONKYKONGGAME_H

#include <conio.h>
#include <windows.h>
#include <iostream>
#include <process.h>

#include "Board.h"
#include "utils.h"
#include "point.h"
#include "gameConfig.h"
#include "mario.h" 

class TheDonkyKongGame 
{
	
public:
	void init();
	void run();
};

#endif
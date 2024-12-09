#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <process.h>

#include "Board.h"
#include "utils.h"
#include "point.h"
#include "gameConfig.h"
#include "mario.h" 

using namespace std;

void main()
{
	ShowConsoleCursor(false);

    Board b;
    b.reset();
    b.print();

    mario p; 
	p.setBoard(b);
    int keyPressed = 0;

    while (true)
    {
        
        if (_kbhit()) 
        {
            keyPressed = _getch(); 
			keyPressed = std::tolower(keyPressed);

            if (keyPressed == (int)gameConfig::eKeys::ESC) 
                break;
        }

        if (b.getChar(p.getX(), p.getY()) == 'H') {
            p.draw('@');
            Sleep(500);
            p.erase('H');
        }
        else
        {
            p.draw('@');
            Sleep(500);
            p.erase();
        }

        p.move((gameConfig::eKeys)keyPressed); 
    }
}
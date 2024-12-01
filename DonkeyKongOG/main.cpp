#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <process.h>

#include "Board.h"
#include "utils.h"
#include "point.h"
#include "gameConfig.h"

using namespace std;




//void movingMarioInBoard();

void main()
{
    //movingMarioInBoard();
	ShowConsoleCursor(false);

    Board b;
    b.reset();
    b.print();

    point p(1,22);
	p.setBoard(b);

	/*while (true) {
		p.draw('@');
		if (_kbhit()) {
			char key = _getch();
			if (key == (char)gameConfig::eKeys::ESC) break;  
			p.keyPressed(key);
		}
		Sleep(100);
		p.erase();
		p.move(key);
	}*/

    while (true)
    {
        int keyPressed = 0; 
        if (_kbhit()) 
        {
            keyPressed = _getch(); 
            if (keyPressed == (int)gameConfig::eKeys::ESC) 
                break;
        }
        p.draw('@');
        Sleep(500); 
        p.erase();

        p.move((gameConfig::eKeys)keyPressed); 
    }
}



/*void movingMarioInBoard()
{
    int x = 1, y = 25;
    char key;

    while (/*!_kbhit() || _getch() != 27)
    {
        gotoxy(x, y);
        cout << "@";
        Sleep(500);
        gotoxy(x, y);
        cout << " ";

        key = _getch(); 
        if (key == 'w')
            y--;
        else if (key == 'a')
            x--;
        else if (key == 's')
            y++;
        else if (key == 'd')
            x++;

       
    }
}*/
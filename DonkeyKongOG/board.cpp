#include <cstring>
#include <iostream>

#include "Board.h"
#include "utils.h"; 

// Reset the board to its original state
void Board::reset()     
{
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], gameConfig::GAME_WIDTH + 1);
	}
}

// Print the board to the console
void Board::print() const {
	for (int i = 0; i < gameConfig::GAME_HEIGHT - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[gameConfig::GAME_HEIGHT - 1];
}

// Display the pause screen
void Board::displayPauseScreen()
{
	const char* pauseBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                 $                                 |LIVES:3| Q", // 1
		 "Q                      ==========================                             Q", // 2
		 "Q                       H                   H                                 Q", // 3
		 "Q                       H           &       H                                 Q", // 4
		 "Q               >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                  Q", // 5
		 "Q                H                H     H                 H                   Q", // 6
		 "Q                H                H     H                 H                   Q", // 7
		 "Q                H                H     H                 H                   Q", // 8
		 "Q             <<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         Q", // 9
		 "Q                                                                             Q", // 10
		 "Q                      ******* Game is paused ******                          Q", // 11
		 "Q                                                                             Q", // 12
		 "Q         <<<<<<<<<<<<   <<<<<<<<<<<<>>>>>>>>>>>  >>>>>>>>>>>>>>>>>>>         Q", // 13
		 "Q                                                                             Q", // 14
		 "Q               Press ESC to continue or Enter to lose and exit :(            Q", // 15
		 "Q                                                                             Q", // 16
		 "Q    <<<<<<<<<<<  ===================================   >>>>>>>>>>>>>>>>>     Q", // 17
		 "Q    H             H                                H                   H     Q", // 18
		 "Q    H             H                                H                   H     Q", // 19
		 "Q    H             H                                H                   H     Q", // 20
		 "Q  <<<<<<<<<<<<<  <<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>> >>>>>>>>>>>>>>>>>>>   Q", // 21
		 "Q        H        H                                   H                   H   Q", // 22
		 "Q<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24

	};

	
	system("cls");


	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], pauseBoard[i], gameConfig::GAME_WIDTH + 1); 
	} 
	print();
}

void Board::displayVictory()
{
	const char* victoryBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                   |LIVES:3| Q", // 1
		 "Q                                                                             Q", // 2
		 "Q                                                                             Q", // 3
		 "Q                                                                             Q", // 4
		 "Q                                                                             Q", // 5
		 "Q                            _                       _                        Q", // 6
		 "Q                  __      _(_)_ __  _ __   ___ _ __| |                       Q", // 7
		 "Q                  \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| |                       Q", // 8
		 "Q                   \\ V  V /| | | | | | | |  __/ |  |_|                       Q", // 9
		 "Q                    \\_/\\_/ |_|_| |_|_| |_|\\___|_|  (_)                       Q", // 10
		 "Q                                                                             Q", // 11
		 "Q                                                                             Q", // 12
		 "Q                                                                             Q", // 13
		 "Q                              \\'-=======-'/                                  Q", // 14
		 "Q                              _|   .=.   |_                                  Q", // 15
		 "Q                             ((|  {{1}}  |))                                 Q", // 16
		 "Q                              \\|   /|\\   |/                                  Q", // 17
		 "Q                               \\__ '`' __/                                   Q", // 18
		 "Q                                 _`) (`_                                     Q", // 19
		 "Q                               _/_______\\_                                   Q", // 20
		 "Q                              /___________\\                                  Q", // 21
		 "Q                                                                             Q", // 22
		 "Q                                                                             Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	system("cls");


	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], victoryBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displayDisqualified()
{
	const char* disqualifiedBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                             Q", // 1
		 "Q                                                                             Q", // 2
		 "Q                                                                             Q", // 3
		 "Q                                                                             Q", // 4
		 "Q                                                                             Q", // 5
		 "Q                                                                             Q", // 6
		 "Q                                                                             Q", // 7
		 "Q       __                                                                    Q", // 8
		 "Q      /\\ \\__                                                __               Q", // 9
		 "Q      \\ \\ ,_\\  _ __   __  __         __       __      __   /\\_\\    ___       Q", // 10
		 "Q       \\ \\ \\/ /\\`'__\\/\\ \\/\\ \\      /'__`\\   /'_ `\\  /'__`\\ \\/\\ \\ /' _ `\\     Q", // 11
		 "Q        \\ \\ \\_\\ \\ \\/ \\ \\ \\_\\ \\    /\\ \\L\\.\\_/\\ \\L\\ \\/\\ \\L\\.\\_\\ \\ \\/\\ \\/\\ \\    Q", // 12
		 "Q         \\ \\__\\\\ \\_\\  \\/`____ \\   \\ \\__/.\\_\\ \\____ \\ \\__/.\\_\\\\ \\_\\ \\_\\ \\_\\   Q", // 13
		 "Q          \\/__/ \\/_/   `/___/> \\   \\/__/\\/_/\\/___L\\ \\/__/\\/_/ \\/_/\\/_/\\/_/   Q", // 14
		 "Q                          /\\___/              /\\____/                        Q", // 15
		 "Q                          \\/__/               \\_/__/                         Q", // 16
		 "Q                                                                             Q", // 17
		 "Q                                                                             Q", // 18
		 "Q                                                                             Q", // 19
		 "Q                                                                             Q", // 20
		 "Q                                                                             Q", // 21
		 "Q                                                                             Q", // 22
		 "Q                                                                             Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	system("cls");


	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], disqualifiedBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displayLoss()
{
	const char* victoryBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                             Q", // 1
		 "Q                                                                             Q", // 2
		 "Q                                                                             Q", // 3
		 "Q                                                                             Q", // 4
		 "Q                                                                             Q", // 5
		 "Q                  __   __            _                   _                   Q", // 6
		 "Q                  \\ \\ / /__  _   _  | |    ___  ___  ___| |                  Q", // 7
		 "Q                   \\ V / _ \\| | | | | |   / _ \\/ __|/ _ \\ |                  Q", // 8
		 "Q                    | | (_) | |_| | | |__| (_) \\__ \\  __/_|                  Q", // 9
		 "Q                    |_|\\___/ \\__,_| |_____\\___/|___/\\___(_)                  Q", // 10
		 "Q                                                                             Q", // 11
		 "Q                                                                             Q", // 12
		 "Q                                                                             Q", // 13
		 "Q                             _'''''''''_                                     Q", // 14
		 "Q                           .'          '.                                    Q", // 15
		 "Q                          /   O      O   \\                                   Q", // 16
		 "Q                         :           `    :                                  Q", // 17
		 "Q                         |                |                                  Q", // 18
		 "Q                         :    .------.    :                                  Q", // 19
		 "Q                          \\  '        '  /                                   Q", // 20
		 "Q                           '.          .'                                    Q", // 21
		 "Q                             '-......-'                                      Q", // 22
		 "Q                                                                             Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	system("cls");


	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], victoryBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}
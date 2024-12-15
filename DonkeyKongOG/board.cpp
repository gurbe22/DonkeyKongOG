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
		 "Q               Press ESC to continue or Y to lose and exit :(                Q", // 15
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


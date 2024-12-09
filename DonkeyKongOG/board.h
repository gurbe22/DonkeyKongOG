#ifndef BOARD_H
#define BOARD_H
#include "gameConfig.h"

class Board
{
	//hi
	const char* originalBoard[gameConfig::GAME_HEIGHT] = {
		// !123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                   $                                         Q", // 1
		  "Q                      ============================                           Q", // 2
		  "Q                                                                             Q", // 3
		  "Q                                   &                                         Q", // 4
		  "Q               <<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>                   Q", // 5
		  "Q                H                H     H                 H                   Q", // 6
		  "Q                H                H     H                 H                   Q", // 7
		  "Q                H                H     H                 H                   Q", // 8
		  "Q            <<<<<<<<<<  ======================  >>>>>>>>>>>>>>>>>            Q", // 9
		  "Q             H            H                  H                  H            Q", // 10
		  "Q             H            H                  H                  H            Q", // 11
		  "Q             H            H                  H                  H            Q", // 12
		  "Q         <<<<<<<<<<<<   <<<<<<<<<<<<>>>>>>>>>>>  >>>>>>>>>>>>>>>>>>>         Q", // 13
		  "Q         H              H                     H                    H         Q", // 14
		  "Q         H              H                     H                    H         Q", // 15
		  "Q         H              H                     H                    H         Q", // 16
		  "Q    <<<<<<<<<<<  ===================================   >>>>>>>>>>>>>>>>>     Q", // 17
		  "Q    H             H                                H                   H     Q", // 18
		  "Q    H             H                                H                   H     Q", // 19
		  "Q    H             H                                H                   H     Q", // 20
		  "Q  <<<<<<<<<<<<<  <<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>> >>>>>>>>>>>>>>>>>>>   Q", // 21
		  "Q  H              H                                   H                   H   Q", // 22
		  "Q <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1]; // +1 for null terminator
public:
	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
};
#endif

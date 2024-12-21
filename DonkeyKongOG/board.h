#ifndef BOARD_H
#define BOARD_H

#include <windows.h>

#include "gameConfig.h"

class Board
{
	const char* originalBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                 $                                 |LIVES:3| Q", // 1
		 "Q                      ==========================                             Q", // 2
		 "Q                       H                   H                                 Q", // 3
		 "Q                       H           &       H                                 Q", // 4
		 "Q      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                  Q", // 5
		 "Q         H      H                H     H                 H                   Q", // 6
		 "Q         H      H                H     H                 H                   Q", // 7
		 "Q         H      H                H     H                 H                   Q", // 8
		 "Q         H   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                  Q", // 9
		 "Q         H   H            H                  H                  H            Q", // 10
		 "Q         H   H            H                  H                  H            Q", // 11
		 "Q         H   H            H                  H                  H            Q", // 12
		 "Q         >>>>>>>>>>>>   <<<<<<<<<<<<>>>>>>>>>>>  >>>>>>>>>>>>>>>>>>>>        Q", // 13
		 "Q         H              H                     H                    H         Q", // 14
		 "Q         H              H                     H                    H         Q", // 15
		 "Q         H              H                     H                    H         Q", // 16
		 "Q    <<<<<<<<<<<  >>>>>>>>>>>>>>==============>>>>>>>   >>>>>>>===>>>>>>>     Q", // 17
		 "Q    H             H                                H                   H     Q", // 18
		 "Q    H             H                                H                   H     Q", // 19
		 "Q    H             H                                H                   H     Q", // 20
		 "Q  <<<<<<<<<<<<<  <<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   Q", // 21
		 "Q        H        H                                   H                   H   Q", // 22
		 "Q<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	char currentBoard[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH + 1]; // +1 for null terminator

public:
	

	void reset();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
	void setChar(int x, int y, char c) {
		currentBoard[y][x] = c; 
	}
	void displayPauseScreen();
};
#endif

#include <cstring>
#include <iostream>

#include "Board.h"

void Board::reset() 
{
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], gameConfig::GAME_WIDTH + 1);  
	}
}

void Board::print() const {
	for (int i = 0; i < gameConfig::GAME_HEIGHT - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[gameConfig::GAME_HEIGHT - 1];
}

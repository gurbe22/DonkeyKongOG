#include "Board.h"

// Reset the board to its original state
void Board::reset()     
{
	// Copy the original board layout into the current board
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], gameConfig::GAME_WIDTH + 1);
	}
}

// Print the board to the console
void Board::print() const 
{
	// Loop through each row and print it
	for (int i = 0; i < gameConfig::GAME_HEIGHT - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	// Print the last row without an additional newline
	std::cout << currentBoard[gameConfig::GAME_HEIGHT - 1];
}

//
void Board::load(const std::string& filename, int& marioStartingX, int& marioStartingY) {
	std::ifstream screen_file(filename);
	std::cout << screen_file.is_open() << std::endl;
	// TODO: handle errors (all sort of...) - do not submit it like that :)
	int curr_row = 0;
	int curr_col = 0;
	char c;
	while (!screen_file.get(c).eof() && curr_row < gameConfig::GAME_HEIGHT) {
		if (c == '\n') {
			if (curr_col < gameConfig::GAME_WIDTH) {
				// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(gameConfig::GAME_WIDTH - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < gameConfig::GAME_WIDTH) {
			// handle special chars
			if (c == gameConfig::MARIO) {
				marioStartingX = curr_col;
				marioStartingY = curr_row;
			}
			else if (c == gameConfig::PAULINE) {
				//endPos = { curr_col, curr_row };
				;
			}
			originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < gameConfig::GAME_HEIGHT ? curr_row : gameConfig::GAME_HEIGHT - 1);
	// add a closing frame
	// first line
#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[0], std::string(gameConfig::GAME_WIDTH, gameConfig::LIMIT).c_str());
	// last line
#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[last_row], std::string(gameConfig::GAME_WIDTH, gameConfig::LIMIT).c_str());
	// first col + last col
	for (int row = 1; row < last_row; ++row) {
		originalBoard[row][0] = gameConfig::LIMIT;
		originalBoard[row][gameConfig::GAME_WIDTH - 1] = gameConfig::LIMIT;
	}
}

// Display the pause screen
void Board::displayPauseScreen()
{
	const char* pauseBoard[gameConfig::GAME_HEIGHT] = 
	{
		   //!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                $                                                             Q", // 1
			"Q              ======                                                          Q", // 2
			"Q              H                                                               Q", // 3
			"Q        &     H                                                               Q", // 4
			"Q       ==>>==================================                                 Q", // 5
			"Q                                 H                    _                       Q", // 6
			"Q                       _ __   __ _ _   _ ___  ___  __| |                      Q", // 7
			"Q                      | '_ \\ / _` | | | / __|/ _ \\/ _` |                      Q", // 8
			"Q                      | |_) | (_| | |_| \\__ \\  __/ (_| |                      Q", // 9
			"Q                      | .__/ \\__,_|\\__,_|___/\\___|\\__,_|                      Q", // 10
			"Q                      |_|     H                                               Q", // 11
			"Q                      >>>>>=====================  ====                        Q", // 12
			"Q                                                   H                          Q", // 13
			"Q           press ESC to continue or ENTER to exit and lose the game :(        Q", // 14
			"Q                                                   H                          Q", // 15
			"Q               =================================  ==========                  Q", // 16
			"Q                 H                                                            Q", // 17
			"Q                 H                                                            Q", // 18
			"Q                 H                                                            Q", // 19
			"Q            ============================================================      Q", // 20
			"Q                                                                       H      Q", // 21
			"Q                                                                       H      Q", // 22
			"Q==============================================================================Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"

	};

	
	system("cls");

	// Copy the pause board layout into the current board
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], pauseBoard[i], gameConfig::GAME_WIDTH + 1); 
	} 
	print();
}

// Display the victory screen
void Board::displayVictory()
{
	const char* victoryBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                             Q", // 1
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

	// Copy the victory board layout into the current board
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], victoryBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

// Display the disqualified screen
void Board::displayDisqualified()
{
	const char* disqualifiedBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q       __                                                                     Q", // 8
		 "Q      /\\ \\__                                                __                Q", // 9
		 "Q      \\ \\ ,_\\  _ __   __  __         __       __      __   /\\_\\    ___        Q", // 10
		 "Q       \\ \\ \\/ /\\`'__\\/\\ \\/\\ \\      /'__`\\   /'_ `\\  /'__`\\ \\/\\ \\ /' _ `\\      Q", // 11
		 "Q        \\ \\ \\_\\ \\ \\/ \\ \\ \\_\\ \\    /\\ \\L\\.\\_/\\ \\L\\ \\/\\ \\L\\.\\_\\ \\ \\/\\ \\/\\ \\     Q", // 12
		 "Q         \\ \\__\\\\ \\_\\  \\/`____ \\   \\ \\__/.\\_\\ \\____ \\ \\__/.\\_\\\\ \\_\\ \\_\\ \\_\\    Q", // 13
		 "Q          \\/__/ \\/_/   `/___/> \\   \\/__/\\/_/\\/___L\\ \\/__/\\/_/ \\/_/\\/_/\\/_/    Q", // 14
		 "Q                          /\\___/              /\\____/                         Q", // 15
		 "Q                          \\/__/               \\_/__/                          Q", // 16
		 "Q                                                                              Q", // 17
		 "Q                                                                              Q", // 18
		 "Q                                                                              Q", // 19
		 "Q                                                                              Q", // 20
		 "Q                                                                              Q", // 21
		 "Q                                                                              Q", // 22
		 "Q                                                                              Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	system("cls");

	// Copy the pause board layout into the current board
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], disqualifiedBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

// Display the loss screen
void Board::displayLoss()
{
	const char* victoryBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                  __   __            _                   _                    Q", // 6
		 "Q                  \\ \\ / /__  _   _  | |    ___  ___  ___| |                   Q", // 7
		 "Q                   \\ V / _ \\| | | | | |   / _ \\/ __|/ _ \\ |                   Q", // 8
		 "Q                    | | (_) | |_| | | |__| (_) \\__ \\  __/_|                   Q", // 9
		 "Q                    |_|\\___/ \\__,_| |_____\\___/|___/\\___(_)                   Q", // 10
		 "Q                                                                              Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                                                                              Q", // 13
		 "Q                             _'''''''''_                                      Q", // 14
		 "Q                           .'          '.                                     Q", // 15
		 "Q                          /   O      O   \\                                    Q", // 16
		 "Q                         :           `    :                                   Q", // 17
		 "Q                         |                |                                   Q", // 18
		 "Q                         :    .------.    :                                   Q", // 19
		 "Q                          \\  '        '  /                                    Q", // 20
		 "Q                           '.          .'                                     Q", // 21
		 "Q                             '-......-'                                       Q", // 22
		 "Q                                                                              Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	system("cls");

	// Copy the pause board layout into the current board
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		memcpy(currentBoard[i], victoryBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}
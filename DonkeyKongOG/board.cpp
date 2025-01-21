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


bool Board::load(const std::string& filename) {
	std::ifstream screen_file(filename);
	if (!screen_file.is_open())
	{
		displayLoadingFileFailed();
		return false;
	}
	int curr_row = 0;
	int curr_col = 0;
	char c;
	bool isGameWithLimit = false;
	bool isPaulineFound = false;
	bool isDonkeyKongFound = false;
	bool isHammerFound = false;
	bool isMarioFound = false;
	bool isInfoFound = false;

	while (!screen_file.get(c).eof() && curr_row < gameConfig::GAME_HEIGHT) {
		if (c == '\n') {
			if (curr_col < gameConfig::GAME_WIDTH) {
				// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(gameConfig::GAME_WIDTH - curr_col - 1, gameConfig::OPEN_SPACE).c_str());


			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < gameConfig::GAME_WIDTH)
		{
			if (c == gameConfig::LIMIT) {
				isGameWithLimit = true;
			}
			// handle special chars
			if (!handleSpecialChar(c, curr_row, curr_col, isPaulineFound, isDonkeyKongFound, isHammerFound, isMarioFound, isInfoFound))
			{
				return false;
			}
		}
	}

	if (!(isPaulineFound && isDonkeyKongFound && isHammerFound && isMarioFound && isInfoFound))
	{
		displaySignificantCharacterMissing();
		Sleep(2000);
		return false;
	}

	if(!isDonkeyKongInLegalPlace())
	{
		displayDonkeyKongInIllegalPlace();
		Sleep(2000);
		return false;
	}

	int last_row = min(curr_row, gameConfig::GAME_HEIGHT - 1);

	if (isGameWithLimit)
	{
#pragma warning(suppress : 4996) // to allow strcpy
		strcpy(originalBoard[0], std::string(gameConfig::GAME_WIDTH, gameConfig::LIMIT).c_str());
		originalBoard[0][gameConfig::GAME_WIDTH] = '\0';
		// last line
#pragma warning(suppress : 4996) // to allow strcpy
		strcpy(originalBoard[last_row], std::string(gameConfig::GAME_WIDTH, gameConfig::LIMIT).c_str());
		originalBoard[last_row][gameConfig::GAME_WIDTH] = '\0';
		// first col + last col

		for (int row = 1; row < last_row; ++row) {
			originalBoard[row][0] = gameConfig::LIMIT;
			originalBoard[row][gameConfig::GAME_WIDTH - 1] = gameConfig::LIMIT;
			originalBoard[row][gameConfig::GAME_WIDTH] = '\0';
		}

		addFloor(originalBoard[gameConfig::GAME_HEIGHT - 2], gameConfig::GAME_WIDTH);
	}
	else
	{
		for (int row = 0; row < gameConfig::GAME_HEIGHT; ++row)
		{
			originalBoard[row][gameConfig::GAME_WIDTH] = '\0';
		}

		addFloor(originalBoard[gameConfig::GAME_HEIGHT - 1], gameConfig::GAME_WIDTH);
	}

	addInfo(infoPosX, infoPosY);
	return true;
}

// Handle special characters in the board layout
bool Board::handleSpecialChar(char c, int& curr_row, int& curr_col, bool& isPaulineFound, bool& isDonkeyKongFound, bool& isHammerFound, bool& isMarioFound, bool& isInfoFound) {
	switch (c) {
	case gameConfig::MARIO:
		if (!isMarioFound)
		{
			marioStartingX = curr_col;
			marioStartingY = curr_row;
			isMarioFound = true;
		}
		originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		break;
	case gameConfig::DONKEYKONG:
		if (!isDonkeyKongFound)
		{
			donkeyPosX = curr_col;
			donkeyPosY = curr_row;
			originalBoard[curr_row][curr_col++] = c;
			isDonkeyKongFound = true;
		}
		else
		{
			originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		}
		break;
	case gameConfig::INFO_POS:
		if (!isInfoFound)
		{
			infoPosX = curr_col;
			infoPosY = curr_row;
			isInfoFound = true;
		}
		originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		break;
	case gameConfig::GHOST:
		ghostPos.push_back({ curr_col, curr_row });
		originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		break;
	case gameConfig::HAMMER:
		if (!isHammerFound)
		{
			originalBoard[curr_row][curr_col++] = c;
			isHammerFound = true;
		}
		else
		{
			originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		}
		break;
	case gameConfig::PAULINE:
		if (!isPaulineFound)
		{
			originalBoard[curr_row][curr_col++] = c;
			isPaulineFound = true;
		}
		else
		{
			originalBoard[curr_row][curr_col++] = gameConfig::OPEN_SPACE;
		}
		break;
	case gameConfig::LIMIT:
	case gameConfig::FLOOR:
	case gameConfig::LFLOOR:
	case gameConfig::RFLOOR:
	case gameConfig::LADDER:
	case gameConfig::OPEN_SPACE:
		originalBoard[curr_row][curr_col++] = c;
		break;
	default:
		displayErrorUnacceptableCharacter();
		Sleep(2000);
		return false;
		break;
	}
	return true;
}

// Add floor to a row
void Board::addFloor(char* row, int width) {
	for (int col = 0; col < width; ++col) {
		if (row[col] == gameConfig::OPEN_SPACE) {
			row[col] = gameConfig::FLOOR;
		}
	}
}

// Add the information to the board
void Board::addInfo(int infoPosX, int infoPosY)
{
	if (infoPosY + INFO_HEIGHT > gameConfig::GAME_HEIGHT || infoPosX + INFO_WIDTH > gameConfig::GAME_WIDTH) {
		std::cerr << "Error: Info position is out of bounds." << std::endl;
		return;
	}

	const char* info[INFO_HEIGHT] =
	{ // !123456789!123456789!
		"    Level: 1        ",
		"    Score: 0000     ",
		" Lives: 3  Hammer:X "

	};

	for (int i = 0; i < INFO_HEIGHT; i++)
	{
		memcpy(originalBoard[infoPosY + i] + infoPosX + 1, info[i], INFO_WIDTH);
	}

}

bool Board::isDonkeyKongInLegalPlace()
{
	if (donkeyPosY < gameConfig::GAME_HEIGHT - 2)
	{
		char ch = originalBoard[donkeyPosY + 1][donkeyPosX];
		if (ch == gameConfig::FLOOR || ch == gameConfig::LFLOOR || ch == gameConfig::RFLOOR)
		{
			return true;
		}
	}
	return false;

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

// Display the error screen when no files are found
void Board::displayErrorNoFiles()
{
	const char* noFilesErrorBoard[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q                  No suitable files for the game to begin                     Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], noFilesErrorBoard[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displayDonkeyKongInIllegalPlace()
{
	const char* donkeyKongInIllegalPlace[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q             Donkey Kong is in illegal place (has to be on a floor)           Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], donkeyKongInIllegalPlace[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displayErrorNotExistFile()
{

	const char* notExistFile[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q             You asked to play on a board that does not exist.                Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], notExistFile[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displayLoadingFileFailed()
{
	const char* loadingFileFailed[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q                          Failed to load th file                              Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], loadingFileFailed[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}

void Board::displaySignificantCharacterMissing()
{
	const char* significantCharacterMissing[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q            Significant character is missing cannot begin the game            Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], significantCharacterMissing[i], gameConfig::GAME_WIDTH + 1);
	}
	print();
}


// Display the error screen when no files are found
void Board::displayErrorUnacceptableCharacter()
{
	const char* UnacceptableCharacter[gameConfig::GAME_HEIGHT] = {
		//!123456789!123456789!123456789!123456789!123456789!123456789!123456789!123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                                                                              Q", // 7
		 "Q                                                                              Q", // 8
		 "Q                                 ERROR                                        Q", // 9
		 "Q                                                                              Q", // 10
		 "Q            An unacceptable character was found in the keyboard.              Q", // 11
		 "Q                                                                              Q", // 12
		 "Q                       Check your files and try again                         Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
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
		memcpy(currentBoard[i], UnacceptableCharacter[i], gameConfig::GAME_WIDTH + 1);
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
		 "Q                  Well Done! You finished all the levels                     Q", // 3
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

void Board::addScore(int score, int returningX, int returningY) 
{
	std::string strScore;

	int indentation;

	indentation = getNewScoreIndetation(score);
	
	printScore(score, returningX, returningY, indentation);

	strScore = std::to_string(score);

	setLine(strScore, getScorePositionX() + indentation, getScorePositionY());
}

void Board::printScore(int score, int returningX, int returningY, int indentation) const
{
	gotoxy(getScorePositionX() + indentation, getScorePositionY());
	cout << score;
	gotoxy(returningX, returningY);
}

int Board::getNewScoreIndetation(int score) const
{
	int indentation = 0;

	indentation = getMaxNewPointIndentation(); 
	score = score / 10;

	while ( score != 0)
	{
		indentation -- ;
		score = score / 10;
	}

	return indentation; 
}

int Board::getMaxNewPointIndentation() const 
{
	int maxScore = gameConfig::MAX_SCORE; 
	int maxIndentation = 0;

	maxScore = maxScore / 10;

	while (maxScore != 0)
	{
		maxIndentation++;
		maxScore = maxScore / 10;
	}

	return maxIndentation;
}

void Board::setLine(std::string line, int posX, int posY)
{
	const char* newLine = line.c_str();
	
	memcpy(originalBoard[posY] + posX + 1 , newLine , line.length()); 
}

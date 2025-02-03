#include "game.h"
using namespace std;

// Function to display the main menu
void Game::mainMenu()
{
	vector<std::string> fileNames;
	bool running = RUNNING;
	ShowConsoleCursor(false); // Hide the cursor
	getAllBoardFileNames(fileNames);
	sort(fileNames.begin(), fileNames.end());

	while (running) {
		system("cls"); // Clear the screen
		cin.clear();

		displayMenuWithAnimation(); // הצגת תפריט המשחק עם אנימציה

		// Get user input
		int choiceInt = _getch(); // קלט כ-int
		char choice = static_cast<char>(choiceInt);
		int levelChoice;

		switch (choice) {
		case START_NEW_GAME:
			runGame(fileNames);  // Start a new game
			break;
		case START_NEW_SPECIFC_LEVEL:
			levelChoice = displayLevelsChoices(fileNames);
			if (levelChoice == -1) {
				continue; // חזרה ללולאה
			}
			runGame(fileNames, levelChoice); // קריאה למשחק
			break;
		case SHOW_INSTRUCTIONS:
			displayInstructions();  // Show game instructions
			break;
		case EXIT_GAME:
			running = STOP_RUNNING;  // Exit the game
			break;
		default:
			cout << "Invalid choice. Please enter a valid option (1, 2, 8, 9).\n";
			Sleep(1000);
			break;
		}
	}
	system("cls"); // Clear the screen after exiting
	cout << "Exiting the game. Goodbye!\n";
}
bool Game::filesValidation(int levelChoice, int amountOfFiles, Board board) const
{
	if (levelChoice > amountOfFiles)
	{
		board.displayErrorNotExistFile();
		Sleep(GameConfig::DISPLAY_SPEED);
		return true;
	}
	if (amountOfFiles == 0)
	{
		board.displayErrorNoFiles();
		Sleep(GameConfig::DISPLAY_SPEED);
		return true;
	}

	return false;
}

// Function to run the game
void Game::runGame(vector<std::string> fileNames, int levelChoice, bool isSilent)
{
	system("cls"); // Clear the screen
	Board board;
	Mario mario;
	bool victory = false, winLevel = false, unmatching_result_found = false;
	level = 0;

	if (filesValidation(levelChoice, fileNames.size(), board)) return; // Validate files

	for (const auto& filename : fileNames) { // Loop through all levels
		size_t iteration = 0;
		Results results;
		Steps steps;
		long random_seed;
		string filename_prefix = filename.substr(0, filename.find_last_of('.'));
		string stepsFilename = filename_prefix + ".steps";
		string resultsFilename = filename_prefix + ".result";

		initializeGameData(stepsFilename, resultsFilename, random_seed, steps, results);
		srand(random_seed);
		level++;

		if (levelChoice == 0 || levelChoice == level) { // If playing all levels or selected one
			victory = false;
			winLevel = false;
			board.resetGhostPos();

			if (!board.load(filename)) continue; // Skip level if loading fails

			setMarioPos(board, mario); // Set Mario's start position
			vector<Enemy*> enemies;
			enemies.reserve(10);

			int currentFrame;
			int barrelsX = bendingDirX(board.getDonkeyPosX()) + board.getDonkeyPosX();
			int barrelsY = board.getDonkeyPosY();
			size_t nextDisqualificationIteration = 0;

			while (mario.getLives() > 0 && !winLevel) { // Main game loop
				currentFrame = DELAY;
				mario.setMarioToStart();
				deleteDynamicEnemies(enemies);
				displayBoard(board, mario, isSilent);
				createAllGhosts(enemies, board);
				mario.setBoard(board);

				int lives = mario.getLives();
				GameConfig::eKeys keyPressed = GameConfig::eKeys::STAY;

				while (RUNNING) { // Input and gameplay loop
					++iteration;
					validateResultsAndUpdateDisqualificationIteration(results, iteration, nextDisqualificationIteration, unmatching_result_found, filename);
					if (unmatching_result_found) break;

					if (currentFrame % DELAY == 0) {
						enemies.push_back(new Barrel(board, barrelsX, barrelsY)); // Spawn barrels
					}
					currentFrame++;

					bool flag = processGameInput(steps, results, iteration, board, mario, keyPressed);
					if (flag) {
						if (mario.getLives() > 0)
							handleDisqualification(nextDisqualificationIteration, unmatching_result_found, iteration, results, filename);
						break;
					}

					mario.moveMario(keyPressed, enemies);

					if (mario.isWon()) { // Check if Mario has won
						validateWin(levelChoice, fileNames.capacity(), board, winLevel, victory, level);
						break;
					}

					if (!isSilent) mario.drawMario();
					moveEnemies(enemies, isSilent);

					goToSleep();

					if (!isSilent) eraseAllCharacters(enemies, mario);

					if (lives != mario.getLives()) { // Check if Mario lost a life
						if (mario.getLives() != 0) {
							handleDisqualification(nextDisqualificationIteration, unmatching_result_found, iteration, results, filename);
							board.displayDisqualified();
							Sleep(GameConfig::DISPLAY_SPEED);
						}
						break;
					}

					checkIfDisqualificationMatch(iteration, nextDisqualificationIteration, unmatching_result_found, filename);
				}
				if (unmatching_result_found) break;
			}

			deleteDynamicEnemies(enemies);
			handleGameResult(victory, winLevel, iteration, steps, results, stepsFilename, resultsFilename, unmatching_result_found, filename);

			if (mario.getLives() == 0) break; // Exit if Mario is out of lives
		}
	}
	// Display final game result
	if (victory) {
		board.displayVictory();
		Sleep(GameConfig::DISPLAY_SPEED);
	}
	else {
		board.displayLoss();
		Sleep(GameConfig::DISPLAY_SPEED);
	}
}
// Function to validate if the level is won
void Game::validateWin(int levelChoice, int amountOfLevels, Board& board, bool& winLevel, bool& victory, int level)
{
	if (levelChoice == 0 && level < amountOfLevels)
	{
		board.displayWonLevel();
		Sleep(GameConfig::DISPLAY_SPEED);
		winLevel = true;
	}
	else
	{
		winLevel = true;
		victory = true;
	}
}
// Function to delete dynamically allocated enemies
void Game::deleteDynamicEnemies(std::vector<Enemy*>& enemies)
{
	for (auto enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
}
// Function to get all board file names
void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
			std::cout << " ^ added!!\n";
			vec_to_fill.push_back(filenameStr);
		}
	}
	if (vec_to_fill.size() == 0)
	{
		std::cout << " ";
	}
}

/* Setting all game's data */
void Game::setScoreLine(Board& board, Mario& mario)
{
	int score, scoreIdentation;
	score = mario.getScore();
	std::string strScore = std::to_string(score);
	scoreIdentation = board.getNewScoreIndetation(score);
	board.setLine(strScore, board.getScorePositionX() + scoreIdentation, board.getScorePositionY());
}

void Game::setLevelLine(Board& board)
{
	std::string strLevel = std::to_string(level);
	board.setLine(strLevel, board.getLevelPositionX(), board.getLevelPositionY()); // Set number of lives on the board
}

void Game::setLivesChar(Board& board, Mario& mario)
{
	char livesChar = static_cast<char>('0' + mario.getLives()); // Convert integer to character representation
	board.setChar(board.getLivesPositionX(), board.getLivesPositionY(), livesChar); // Update the board with lives
}
/**************************/

// Function to set Mario's starting position
void Game::setMarioPos(Board& board, Mario& mario)
{
	mario.setStartingX(board.getMarioStartingX());
	mario.setStartingY(board.getMarioStartingY());
}
// Function to set the hammer status on the board
void Game::setHammer(Board& board, Mario& mario)
{
	if (mario.getIsHammer())
	{
		board.setChar(board.getHammerStatusPositionX(), board.getHammerStatusPositionY(), GameConfig::WITH_HAMMER); // Set the hammer status on the board
		board.setChar(board.getHammerPositionX(), board.getHammerPositionY(), GameConfig::OPEN_SPACE); // Set the hammer on the board

	}
	else
		board.setChar(board.getHammerStatusPositionX(), board.getHammerStatusPositionY(), GameConfig::WITHOUT_HAMMER); // Set the hammer status on the boardB
}

// Function to create all ghosts
void Game::createAllGhosts(vector<Enemy*>& enemies, Board board)
{
	std::vector<std::pair<int, int>> ghostPos = board.getGhostPos();
	std::vector<std::pair<int, int>> specialGhostPos = board.getSpecialGhostPos();

	for (const auto& pos : ghostPos) enemies.push_back(new Ghost(board, pos.first, pos.second));
	for (const auto& pos : specialGhostPos)	enemies.push_back(new SpecialGhost(board, pos.first, pos.second));
}

/* Erasing all game's characters */
void Game::eraseAllCharacters(vector<Enemy*>& enemies, Mario& mario)
{
	mario.eraseMario();
	eraseEnemies(enemies);
}

void Game::eraseEnemies(vector<Enemy*>& enemies)
{
	for (auto& enemy : enemies) {
		enemy->erase();
	}
}
/***********************************/

// Moves all enemies and removes exploded barrels
void Game::moveEnemies(vector<Enemy*>& enemies, bool isSilent) 
{
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		Enemy* enemy = *it;
		enemy->move(enemies); 

		// Remove exploded barrels
		if (typeid(*enemy) == typeid(Barrel) && enemy->getIsExplode())
		{
			delete enemy; 
			it = enemies.erase(it); 
		}
		else
		{
			if (!isSilent) enemy->draw();
			it++;
		}
		
	}
}
// Handling pause situation
bool Game::isPause(Board& board, int& key) const
{
	if (key == (int)GameConfig::eKeys::ESC)
	{
		board.displayPauseScreen(); // Display pause screen
		key = 0; // Reset key
		while (true)
		{
			key = _getch(); // Wait for key press
			key = tolower(key);

			if (key == (int)GameConfig::eKeys::ESC || key == (int)GameConfig::eKeys::EXIT || key == (int)GameConfig::eKeys::SUICIDE)
				break; // Exit if ESC or EXIT is pressed
		}

		return true;
	}
	return false;
}
// Displays level selection menu and handles user input 
int Game::displayLevelsChoices(vector<string>& fileNames) const {
	size_t size = fileNames.size();
	int currentPage = 0;
	string levelChoice;

	while (true) {
		system("cls"); 
		cout << "Choose a level to play:" << endl;

		// Display levels for the current page
		size_t start = currentPage * LEVELS_PER_PAGE;
		size_t end = min(start + LEVELS_PER_PAGE, size);
		for (size_t i = start; i < end; i++) {
			cout << i + 1 << ". " << fileNames[i] << endl;
		}

		// Navigation options
		if (start + LEVELS_PER_PAGE < size) cout << "n. Next page\n";
		if (currentPage > 0) cout << "p. Previous page\n";
		cout << "m. Return to main menu\n";
		cout << "Enter the level number and press Enter: ";

		cin >> levelChoice;

		// Return to main menu
		if (levelChoice == "m" || levelChoice == "M") 	return -1; 

		// Navigate pages
		if (levelChoice == "n" || levelChoice == "N") {
			if (start + LEVELS_PER_PAGE < size) {
				currentPage++; 
			}
			else {
				cout << "No more pages. Press any key to continue...\n";
				cin.ignore();
				Sleep(1500);
			}
			continue;
		}
		if (levelChoice == "p" || levelChoice == "P") {
			if (currentPage > 0) {
				currentPage--; 
			}
			else {
				cout << "No previous page. Press any key to continue...\n";
				cin.ignore();
				Sleep(1500);
			}
			continue;
		}
		// Validate level selection
		if (levelChoice[0] >= '1' && levelChoice[0] <= '9') {
			int choice = stoi(levelChoice);
			if (choice >= 1 && choice <= size) {
				return choice; 
			}
			else {
				cout << "Invalid choice. Please try again.\n";
				cin.ignore();
				Sleep(1500);
			}
		}
		else {
			cout << "Invalid input. Please try again.\n";
			cin.ignore();
			Sleep(1500);
		}
	}
}
// Displays the full menu with title, art, and options animation
void Game::displayMenuWithAnimation() const
{
	displayTitleWithAnimation();    
	displayDonkyKongArtWithAnimation();      
	displayOptionsWithAnimation();  
}
// Displays the game title with animation
void Game::displayTitleWithAnimation() const {
	std::vector<std::string> gameTitle = {
		" DDDDD   OOOOO   N   N  K   K   EEEEE   Y   Y    K   K    OOOOO  N   N  GGGG  ",
		" D    D O     O  NN  N  K  K    E        YYY     K  K    O     O NN  N  G     ",
		" D    D O     O  N N N  KKK     EEEE      Y      KKK    O       ON N N  G  GG ",
		" D    D O     O  N  NN  K  K    E         Y      K  K    O     O N  NN  G   G ",
		" DDDDD   OOOOO   N   N  K   K   EEEEE     Y      K   K    OOOOO  N   N  GGGG  "
	};
	printWithAnimation(gameTitle, ANIMATION_SPEED);
}
// Displays the main menu options with animation 
void Game::displayDonkyKongArtWithAnimation() const
{
	std::vector<std::string> donkyKongArt = {
		"      ,.-\" \"-. ,",
		"     /    ===   \\",
		"    /  =======   \\",
		"  __|  (0)   (0)  |__",
		" / _|    .---.    |_ \\",
		"|/.----/ O O \\----.\\ |",
		" \\/     |     |     \\/",
		" |    _________     |",
		" |   /         \\    |",
		" |   |  >---<  |    |",
		""
	};
	printWithAnimation(donkyKongArt, ANIMATION_SPEED);
}

void Game::displayOptionsWithAnimation() const
{
	std::vector<std::string> options = {
		"               MAIN MENU               ",
		"---------------------------------------",
		"1. Start a new game",
		"2. Start a specific level",
		"8. Show instructions",
		"9. Exit the game",
		"---------------------------------------",
		"Enter your choice: "
	};
	printWithAnimation(options, ANIMATION_SPEED);
}
// Prints lines with a delay for animation effect. 
void Game::printWithAnimation(const std::vector<std::string>& lines, unsigned int delayMs) const
{
	for (const auto& line : lines) {
		std::cout << line << std::endl;
		Sleep(delayMs); 
	}
}

// Function to display the instructions
void Game::displayInstructions() const
{
	system("cls"); // Clear the screen
	cout << "---------------------------------------\n";
	cout << "            GAME INSTRUCTIONS          \n";
	cout << "---------------------------------------\n";
	cout << "Use the following keys to control Mario:\n";
	cout << "  A/a - Move Left\n";
	cout << "  D/d - Move Right\n";
	cout << "  W/w - Jump\n";
	cout << "  X/x - Move Down\n";
	cout << "  S/s - Stay\n";
	cout << "  P/p - Destroy a barrel or kill a ghost\n";
	cout << "---------------------------------------\n";
	cout << "Press any key to return to the menu...\n";
	(void)_getch(); // Wait for user key press to return
}

// Function to display the board
void Game::displayBoard(Board& board, Mario& mario, bool isSilent)
{
	system("cls"); // Clear the screen
	board.reset(); // Reset the board

	setLivesChar(board, mario);
	setScoreLine(board, mario);
	setLevelLine(board);
	setHammer(board, mario);
	if (!isSilent)
	{
		board.print(); // Print the board
	}
}

// Displays an error message related to game results
void Game::reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue..." << std::endl;
	(void)_getch();
}

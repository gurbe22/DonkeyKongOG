#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#define BARREL 'O'
#define BARREL_START_Y 40
#define BARREL_START_Y 40

class gameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's', ESC = 27, EXIT = '\r'};
	static constexpr int GAME_WIDTH = 79;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr char PAULINE = '$';
	static constexpr char DONKEYKONG = '&';

	//static const int COLORS[];
	//static const int NUM_OF_COLORS;
};

#endif



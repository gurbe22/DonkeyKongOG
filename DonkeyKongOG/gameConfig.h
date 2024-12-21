#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H


class gameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's', ESC = 27, EXIT = '\r', NONE = 'n' };
	static constexpr int GAME_WIDTH = 79;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr char PAULINE = '$';
	static constexpr char DONKEYKONG = '&';
	static constexpr char  BARREL = 'O';
	static constexpr char MARIO = '@';
	static constexpr int NUM_OF_BARRELS = 12;

	//static const int COLORS[];
	//static const int NUM_OF_COLORS;
};

#endif



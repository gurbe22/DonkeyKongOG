#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#define MARIO '@' 
#define LADDER 'H'
#define FLOOR '='
#define LFLOOR '<'
#define RFLOOR '>'
#define OPENSPACE ' '


class gameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAY = 's', ESC = 27, EXIT = 'Y'};
	static constexpr int GAME_WIDTH = 79;
	static constexpr int GAME_HEIGHT = 25;

	//static const int COLORS[];
	//static const int NUM_OF_COLORS;
};

#endif



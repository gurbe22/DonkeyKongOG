#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

//#include "io_utils.h"
//#include "Snake.h"

class TheDonkyKongGame {
	enum { ESC = 27 };
	Snake s[2];
public:
	void init();
	void run();
};

#endif
#ifndef BOARD_H
#define BOARD_H

#include "brick.h"

class Board
{

public:
	Board();
	static const int BOARD_HEIGHT = 3;
	static const int BOARD_WIDTH = 5;
	
private:
	int getState();	//return an integer value of what it's state might be in?  I dunno
	Brick* board[BOARD_HEIGHT][BOARD_WIDTH];

protected:
	
};



#endif //BOARD_H
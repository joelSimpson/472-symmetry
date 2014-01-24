#ifndef BOARD_H
#define BOARD_H

class Board
{

public:
	Board();
	 

private:
	int getState();	//return an integer value of what it's state might be in?  I dunno

protected:
	static const int BOARD_WIDTH = 5;
	static const int BOARD_HEIGHT = 3;
};



#endif //BOARD_H
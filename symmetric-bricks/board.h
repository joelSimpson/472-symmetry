#ifndef BOARD_H
#define BOARD_H

#include "brick.h"
#include <iostream>
#include <vector>

using namespace std;

class Board
{

public:
	Board(string);
	void drawBoard();
	void drawVisited();
	void writeToOutput(ofstream &);

	static const int BOARD_HEIGHT = 3;
	static const int BOARD_WIDTH = 5;

	string currentOutputFile;

	Brick *emptyBrick;

	bool moveUp();
	bool moveRight();
	bool moveDown();
	bool moveLeft();

	bool move(Brick*);//move empty brick to passed brick.  returns false if they aren't neighbours.

	bool isGoalState();
	vector<Brick*> getAvailableLegalMoves();
	
private:
	int getState();	//return an integer value of what it's state might be in?  I dunno
	Brick* board[BOARD_HEIGHT][BOARD_WIDTH];

protected:
	
};



#endif //BOARD_H
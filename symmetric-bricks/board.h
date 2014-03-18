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
	void writeToOutput(ofstream &);
	int heuristic1();
	int heuristic2();
	int heuristic3();
	int findClosestSameColourBrick(int x, int y);
	Brick* makeRandomMove(Brick* previous);
	vector<Brick*> Board::getAvailableLegalMoves();
	bool move(Brick* newPosition);
	bool doesRowHaveMoreThanHalf(int row);
	int* getEmptyBrickPosition();

	static const int BOARD_HEIGHT = 3;
	static const int BOARD_WIDTH = 5;
	int totalMoves;
	int colourCount;
	string currentOutputFile;

	Brick *emptyBrick;

	int blues;
	int reds;
	int whites;
	int greens;
	int yellows;

	bool moveUp();
	bool moveRight();
	bool moveDown();
	bool moveLeft();
	bool isGoalState();

	string toString();
	
private:
	int getState();	//return an integer value of what it's state might be in?  I dunno
	Brick* board[BOARD_HEIGHT][BOARD_WIDTH];

protected:
	
};



#endif //BOARD_H
#include <iostream>
#include <stdlib.h>
#include "board.h"
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <stdlib.h>
#include <time.h>


using namespace std;


//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board(string colours)
{
	this->whites = 0;
	this->blues = 0;
	this->reds = 0;
	this->greens = 0;
	this->yellows = 0;

	int count = 0;
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k <  this->BOARD_WIDTH; k++)
		{
			if(colours[count] == ' '){
				count++;
			}
			board[i][k] = new Brick(colours[count]);
			switch (colours[count])
			{
				case 'e': emptyBrick = board[i][k];//make the moveable brick.
					break;
				case 'w': this->whites++;
					break;
				case 'b': this->blues++;
					break;
				case 'r': this->reds++;
					break;
				case 'g': this->greens++;
					break;
				case 'y': this->yellows++;
					break;
			}
			count++;
		}
	}

	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k <  this->BOARD_WIDTH; k++)
		{
			//cout << "board[" << i << "][" << k << "] is : " << board[i][k]->getColour() << endl;
			if(i > 0){
				board[i][k]->setTopNeighbour(board[i - 1][k]);
				//cout << "board[" << i << "][" << k << "] -- has a TopNeighbour." << endl;
			}
			if(k <  this->BOARD_WIDTH - 1){
				board[i][k]->setRightNeighbour(board[i][k + 1]);
				//cout << "board[" << i << "][" << k << "] -- has a RightNeighbour." << endl;
			}
			if(i <  this->BOARD_HEIGHT - 1){
				board[i][k]->setBottomNeighbour(board[i + 1][k]);
				//cout << "board[" << i << "][" << k << "] -- has a BottomNeighbour." << endl;
			}
			if(k > 0){
				board[i][k]->setLeftNeighbour(board[i][k - 1]);
				//cout << "board[" << i << "][" << k << "] -- has a LeftNeighbour." << endl;
			}
		}
	}
	this->totalMoves = 0;
}

//--------------Moving for Bricks
bool Board::moveUp()
{
	Brick *top = emptyBrick->getTopNeighbour();

	if(top == NULL)
		return false;

	//Swap color
	emptyBrick->setColour(top->getColour());
	top->setColour('e');

	//Set new empty brick pointer
	emptyBrick = top;
	return true;
}

bool Board::moveRight()
{
	Brick *right = emptyBrick->getRightNeighbour();

	if(right == NULL)
		return false;

	//Swap color
	emptyBrick->setColour(right->getColour());
	right->setColour('e');

	//Set new empty brick pointer
	emptyBrick = right;
	return true;
}

bool Board::moveDown()
{
	Brick *down = emptyBrick->getBottomNeighbour();

	if(down == NULL)
		return false;

	//Swap color
	emptyBrick->setColour(down->getColour());
	down->setColour('e');

	//Set new empty brick pointer
	emptyBrick = down;
	return true;
}

bool Board::moveLeft()
{
	Brick *left = emptyBrick->getLeftNeighbour();

	if(left == NULL)
		return false;

	//Swap color
	emptyBrick->setColour(left->getColour());
	left->setColour('e');

	//Set new empty brick pointer
	emptyBrick = left;
	return true;
}
//--------------------------------

bool Board::isGoalState()
{
	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		if(board[0][col]->getColour() != board[this->BOARD_HEIGHT-1][col]->getColour())
		{
			return false;
		}
	}

	return true;
}

int Board::heuristic1()
{
	int value = 0;
	if(this->isGoalState()){
		return 0;
	}

	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		if(board[0][col]->getColour() != board[this->BOARD_HEIGHT-1][col]->getColour())
		{
			value++;
		}
	}
	return value;
}

int Board::heuristic2()
{
	//Under construction!
	int value = 0;
	if(this->isGoalState()){
		return 0;
	}

	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		if(board[0][col]->getColour() != board[this->BOARD_HEIGHT-1][col]->getColour())
		{
			value += 2;
			value += findClosestSameColourBrick(this->BOARD_HEIGHT-1, col);
		}
	}
	return value;
}

int Board::heuristic3()
{
	int value = 0;
	if(this->isGoalState()){
		return 0;
	}

	Brick* previous = emptyBrick;

	//More than half of the same colour can't be on the same row.
	while(doesRowHaveMoreThanHalf(0) && doesRowHaveMoreThanHalf(2))
	{
		previous = this->makeRandomMove(previous);//We pass the previous postion to avoid going back to the same spot again.
	}//Make random moves until less than half of all colours are not on the same top/bot row.

	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		if(board[0][col]->getColour() != board[this->BOARD_HEIGHT-1][col]->getColour())
		{
			value += findClosestSameColourBrick(0, col);//Could use logic here to avoid aiming at same one multiple times.
		}
	}
	return value;
}

Brick* Board::makeRandomMove(Brick* previous)
{
	std::vector<Brick*> availablesMoves = this->getAvailableLegalMoves();
	srand (time(NULL));
	int rNum = rand() % availablesMoves.size() + 1;
	while(availablesMoves[rNum] == previous){//Choose a random move that wasn't where we previously came from.
		rNum = rand() % availablesMoves.size() + 1;
	}
	
	Brick* prev = emptyBrick;
	move(availablesMoves[rNum]);
	return prev;
}

int* Board::getEmptyBrickPosition()
{
	int position[2];

	for(int row = 0; row < BOARD_WIDTH; row++)
	{
		for(int col = 0; col < BOARD_HEIGHT; col++)
		{
			if(this->board[row][col]->getColour() == 'e')
			{
				position[0] = row;
				position[1] = col;
				return position;
			}
		}
	}
}
bool Board::doesRowHaveMoreThanHalf(int row)
{
	int rowWhites = 0;
	int rowReds = 0;
	int rowGreens = 0;
	int rowBlues = 0;
	int rowYellows = 0;

	for(int col = 0; col < this->BOARD_WIDTH; col++)
	{
		switch(this->board[row][col]->getColour())
		{
			case 'w': rowWhites++;
				break;
			case 'b': rowBlues++;
				break;
			case 'r': rowReds++;
				break;
			case 'g': rowGreens++;
				break;
			case 'y': rowYellows++;
				break;
		}
	}

	if(rowWhites > whites/2){
		return true;
	}else if(rowBlues > blues/2){
		return true;
	}else if(rowReds > reds/2){
		return true;
	}else if(rowGreens > greens/2){
		return true;
	}else if(rowYellows > yellows/2){
		return true;
	}
	return false;
}

int Board::findClosestSameColourBrick(int x, int y)
{
	int shortest = numeric_limits<int>::max(); //furthest away it can be.
	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		for(int row = 0; row <  this->BOARD_HEIGHT; row++)
		{
			if(board[row][col]->getColour() == board[x][y]->getColour())//Same color as one we're looking for?
			{
				if(shortest > abs( sqrt(y - col) + sqrt(x - row))){
					shortest = abs( sqrt(y - col) + sqrt(x - row));
				}
			}
		}
	}
	return shortest;
}

//Draw the current board.
void Board::drawBoard()
{
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k < this->BOARD_WIDTH; k++)
		{
			cout << board[i][k]->getColour() << " ";
		}
		cout << endl;
	}
}

void Board::writeToOutput(std::ofstream &output)
{
	if(output.is_open())
	{
		for(int i = 0; i < this->BOARD_HEIGHT; i++)
		{
			for(int k = 0; k < this->BOARD_WIDTH; k++)
			{
				output << board[i][k]->getColour();
			}
		}
		output << "\n";
		this->totalMoves++;
	}

}

string Board::toString()
{
	string str = "";
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k < this->BOARD_WIDTH; k++)
		{
			str += board[i][k]->getColour();
		}
	}

	return str;
}

vector<Brick*> Board::getAvailableLegalMoves()
{
    vector<Brick*> legalMoves;

	if(emptyBrick->getTopNeighbour() != NULL){
		legalMoves.push_back(emptyBrick->getTopNeighbour());
	}
	if(emptyBrick->getRightNeighbour() != NULL){
		legalMoves.push_back(emptyBrick->getRightNeighbour());
	}
	if(emptyBrick->getBottomNeighbour() != NULL){
		legalMoves.push_back(emptyBrick->getBottomNeighbour());
	}
	if(emptyBrick->getLeftNeighbour() != NULL){
		legalMoves.push_back(emptyBrick->getLeftNeighbour());
	}

	return legalMoves;
}

bool Board::move(Brick* newPosition)
{
	if(emptyBrick->getTopNeighbour() == newPosition){
		return moveUp();
	} else if (emptyBrick->getRightNeighbour() == newPosition){
		return moveRight();
	} else if (emptyBrick->getBottomNeighbour() == newPosition){
		return moveDown();
	} else if (emptyBrick->getLeftNeighbour() == newPosition){
		return moveLeft();
	}
	return false;
}
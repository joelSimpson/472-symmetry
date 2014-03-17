#include <iostream>
#include <stdlib.h>
#include "board.h"
#include <string>
#include<fstream>


using namespace std;


//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board(string colours)
{
	int count = 0;
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k <  this->BOARD_WIDTH; k++)
		{
			if(colours[count] == ' '){
				count++;
			}
			board[i][k] = new Brick(colours[count]);
			if(colours[count] == 'e')
				emptyBrick = board[i][k];//make the moveable brick.

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

int Board::findClosestSameColourBrick(int x, int y)
{
	int shortest = 7; //furthest away it can be.
	for(int col = 0; col <  this->BOARD_WIDTH; col++)
	{
		for(int row = 0; row <  this->BOARD_HEIGHT; row++)
		{
			if(board[row][col]->getColour() == board[x][y]->getColour())//Same color as one we're looking for?
			{
				if(shortest > abs( (y - col) + (x - row))){
					shortest = abs( (y - col) + (x - row));
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
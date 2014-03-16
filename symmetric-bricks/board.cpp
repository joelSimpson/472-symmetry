#include <iostream>
#include <stdlib.h>
#include "board.h"
#include <string>
#include <fstream>
#include <vector>

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
			cout << "board[" << i << "][" << k << "] is : " << board[i][k]->getColour() << endl;
			if(i > 0){
				board[i][k]->setTopNeighbour(board[i - 1][k]);
				cout << "board[" << i << "][" << k << "] -- has a TopNeighbour." << endl;
			}
			if(k <  this->BOARD_WIDTH - 1){
				board[i][k]->setRightNeighbour(board[i][k + 1]);
				cout << "board[" << i << "][" << k << "] -- has a RightNeighbour." << endl;
			}
			if(i <  this->BOARD_HEIGHT - 1){
				board[i][k]->setBottomNeighbour(board[i + 1][k]);
				cout << "board[" << i << "][" << k << "] -- has a BottomNeighbour." << endl;
			}
			if(k > 0){
				board[i][k]->setLeftNeighbour(board[i][k - 1]);
				cout << "board[" << i << "][" << k << "] -- has a LeftNeighbour." << endl;
			}
		}
	}
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
	cout << "=========" <<endl;
	std::system("pause");
}

void Board::drawVisited()
{
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k < this->BOARD_WIDTH; k++)
		{
			cout << board[i][k]->visited << " ";
		}
		cout << endl;
	}
	cout << "=========" <<endl;
}

void Board::cleanVisited()
{
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k < this->BOARD_WIDTH; k++)
		{
			board[i][k]->visited = false;
		}
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
	}
}

vector<Brick*> Board::getAvailableLegalMoves() 
{
    vector<Brick*> legalMoves;

	if(emptyBrick->getTopNeighbour() != NULL && emptyBrick->getTopNeighbour()->visited == false){
		legalMoves.push_back(emptyBrick->getTopNeighbour());
	}
	if(emptyBrick->getRightNeighbour() != NULL && emptyBrick->getRightNeighbour()->visited == false){
		legalMoves.push_back(emptyBrick->getRightNeighbour());
	}
	if(emptyBrick->getBottomNeighbour() != NULL && emptyBrick->getBottomNeighbour()->visited == false){
		legalMoves.push_back(emptyBrick->getBottomNeighbour());
	}
	if(emptyBrick->getLeftNeighbour() != NULL && emptyBrick->getLeftNeighbour()->visited == false){
		legalMoves.push_back(emptyBrick->getLeftNeighbour());
	}

	cout << "# of legal moves " << legalMoves.size() << endl;
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
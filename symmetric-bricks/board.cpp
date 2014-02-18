#include <iostream>
using namespace std;

#include <stdlib.h>
#include "board.h"

//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board(string colours)
{
	int count = 0;
	for(int i = 0; i < this->BOARD_HEIGHT; i++)
	{
		for(int k = 0; k <  this->BOARD_WIDTH; k++)
		{
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
				board[i][k]->setTopNeighbour(board[i-1][k]);
				cout << "board[" << i << "][" << k << "] -- has a TopNeighbour." << endl;
			}
			if(k <  this->BOARD_HEIGHT - 1){
				board[i][k]->setRightNeighbour(board[i][k+1]);
				cout << "board[" << i << "][" << k << "] -- has a RightNeighbour." << endl;
			}
			if(i <  this->BOARD_WIDTH - 1){
				board[i][k]->setBottomNeighbour(board[i+1][k]);
				cout << "board[" << i << "][" << k << "] -- has a BottomNeighbour." << endl;
			}
			if(k > 0){
				board[i][k]->setLeftNeighbour(board[i-1][k]);
				cout << "board[" << i << "][" << k << "] -- has a LeftNeighbour." << endl;
			}
		}
	}
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

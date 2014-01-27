#include <iostream>
using namespace std;

#include <stdlib.h>
#include "board.h"

//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board(int height, int width, int redCount, int blueCount, int whiteCount)
{
	this->redCount = redCount;
	this->blueCount = blueCount;
	this->whiteCount = whiteCount;

	for(int i = 0; i < height; i++)
	{
		for(int k = 0; k < width; k++)
		{
			board[i][k] = new Brick('r');
		}
	}

	for(int i = 0; i < height; i++)
	{
		for(int k = 0; k < width; k++)
		{
			if(i > 0){
				board[i][k]->setTopNeighbour(board[i-1][k]);
				cout << "board[" << i << "][" << k << "] -- has a TopNeighbour." << endl;
			}
			if(k < width-1){
				board[i][k]->setRightNeighbour(board[i][k+1]);
				cout << "board[" << i << "][" << k << "] -- has a RightNeighbour." << endl;
			}
			if(i < height - 1){
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

/*
char generateRandomColour(int redCount, int blueCount, int whiteCount)
{
	int x = (rand() % 2);

	while(true){
		switch(x)
		{
		case 0: 
			if(redCount > 0){
				cout << "Red" << endl;
				redCount--;
				return 'r';
			}
			break;
		case 1:
			if(blueCount > 0){
				cout << "Blue" << endl;
				blueCount--;
				return 'b';
			}
			break;
		case 2:
			if(whiteCount > 0){
				cout << "White" << endl;
				whiteCount--;
				return 'w';
			}
			break;
		default: //This should never happend
			//cout << "generateRandomColour spat out something bad." << endl;
				return 'T';
		}

	}
	return 'e';//this should never happen either
}
*/


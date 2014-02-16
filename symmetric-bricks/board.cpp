#include <iostream>
using namespace std;

#include <stdlib.h>
#include "board.h"
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board(string colours, int height, int width)
{
	for(int i = 0; i < height; i++)
	{
		for(int k = 0; k < width; k++)
		{
			board[i][k] = new Brick(colours[i+k]);
		}
	}

	for(int i = 0; i < height; i++)
	{
		for(int k = 0; k < width; k++)
		{
			cout << "board[" << i << "][" << k << "] is : " << board[i][k]->getColour() << endl;
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

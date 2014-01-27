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
			//char colour = generateRandomColour(this->redCount, this->blueCount, this->whiteCount);
			board[i][k] = new Brick('r');
			/*I'll implement logic to generate our "cyber" board.  Given bricks their proper neighbours so we can move around the board.
				I'm thinking will have a Board class or maybe just a 2-d array of bricks to represent the board.  I'm leaning towards the class so we can implement some functions on it easily.
			*/

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


#include <iostream>
using namespace std;

#include "board.h"

//Board constructor.  Generate the board structure with bricks knowing who their neighbours are.
Board::Board()
{
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int k = 0; k <BOARD_WIDTH; k++)
		{
			char colour = generateRandomColour();
			board[i][k] = new Brick();
			/*I'll implement logic to generate our "cyber" board.  Given bricks their proper neighbours so we can move around the board.
				I'm thinking will have a Board class or maybe just a 2-d array of bricks to represent the board.  I'm leaning towards the class so we can implement some functions on it easily.
			*/

		}
	}
}

char generateRandomColour()
{

}




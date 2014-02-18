#include <iostream>
using namespace std;

#include "brick.h"
#include "board.h"

int main(int argc, char* argv[]) {
	cout << "This is the board you passed:" << argv[1] << endl;

	system("pause");

	Board *board = new Board(argv[1]);
	cout << "This is the current board" << endl;
	board->drawBoard();

	return 0;
}



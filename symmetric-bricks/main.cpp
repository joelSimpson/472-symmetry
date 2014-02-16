#include <iostream>
using namespace std;

#include "brick.h"
#include "board.h"

static const int BOARD_WIDTH = 5;
static const int BOARD_HEIGHT = 3;

int main(int argc, char* argv[]) {
	cout << "This is the board you passed:" << argv[1] << endl;

	system("pause");

	Board *board = new Board(argv[1], BOARD_HEIGHT, BOARD_WIDTH);
	system("pause");

	return 0;
}

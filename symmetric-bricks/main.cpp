#include <iostream>
using namespace std;

#include "brick.h"
#include "board.h"

static const int BOARD_WIDTH = 5;
static const int BOARD_HEIGHT = 3;

int main(int argc, char** argv) {
	cout << "Hello World" << endl;
	system("pause");
	int redCount = 6;
	int blueCount = 6;
	int whiteCount = 2;
	Board *board = new Board(BOARD_HEIGHT, BOARD_WIDTH, redCount, blueCount, whiteCount);

	system("pause");
	return 0;
}

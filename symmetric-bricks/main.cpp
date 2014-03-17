#include "brick.h"
#include "board.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;

const string file1 = "../test1";
const string OUTPUT_FILE = "../OUTPUT.txt";

void menuMove(Board* board, ofstream& output);

int main(int argc, char* argv[]) {
	cout << "Reading from file: " << file1 << endl;

	string inputString;
	ifstream input(file1+".txt");

	if(input.is_open()){
		while(getline (input, inputString))
		{
			cout << "I read this line: " << inputString << endl;
			Board *board = new Board(inputString);

			ofstream output(OUTPUT_FILE);
			board->drawBoard();

			//Start Timer
			std::clock_t start;
			double duration;
			start = std::clock();

			//Prompt for moving
			menuMove(board, output);

			//Stop Timer
			duration = ( std::clock() - start );
			output << "Time taken to solve: " << duration << "ms.\n";
			output << board->totalMoves << " total moves taken to solve puzzle.\n";
			//TODO: Move the close outside the while for a complete read of file
			input.close();//Force close reading so we only read first line.. for now.
			output.close();
		}
		
	}else{
		cout << "Unable to open file." << endl;
	}

	system("pause");
	return 0;
}

void menuMove(Board* board, std::ofstream& output)
{
	bool active = true;

	while (active)
	{
		bool movement_status = false;
		cout << "\nEnter wasd to move the empty spot or e to exit: ";
		string key;
		cin >> key;
		cout << "\n";
		//Check for input
		if(key == "w")
			movement_status = board->moveUp();
		if(key == "a")
			movement_status = board->moveLeft();
        if(key == "d")
			movement_status = board->moveRight();
        if(key == "s")
			movement_status = board->moveDown();

		if(key == "e")
		{
			active = false;
		}
		else if(!movement_status) //Print status
		{
			cout << "Illegal move! Please try again.\n\n";
		}
		else if(board->isGoalState())
		{
			cout << "This is a goal state!\n\n";
		}
		//Print board
		board->drawBoard();

		//save legal moves only
		if(movement_status)
			board->writeToOutput(output);
	}
}



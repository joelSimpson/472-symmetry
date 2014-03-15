#include "brick.h"
#include "board.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const string file1 = "../test1";
const int MAX_DEPTH = 2;

void menuMove(Board* board);
void startTraverse(Board* board, int depth);
void traverse(Board* board, int depth, std::stack<std::vector<Brick*>> moves);
void cleanVisitedBricks(std::vector<Brick*> bricks);

int main(int argc, char* argv[]) {
	cout << "Reading from file: " << file1 << endl;

	string inputString;
	ifstream input(file1+".txt");
	if(input.is_open()){
		while(getline (input, inputString))
		{
			//inputString.append(inputString);
			
			cout << "I read this line: " << inputString << endl;

			Board *board = new Board(inputString);
			board->currentOutputFile = file1 + "OUTPUT.txt";
			board->drawBoard();

			//Prompt for moving
			//menuMove(board);

			//Replacing menuMove.
			startTraverse(board, MAX_DEPTH);

			//TODO: Move the close outside the while for a complete read of file
			input.close();//Force close reading so we only read first line.. for now.
		}
		
	}else{
		cout << "Unable to open file." << endl;
	}

	system("pause");
	return 0;
}

void startTraverse(Board* board, int depth)
{
	ofstream output(board->currentOutputFile);
	//Currently just goes to n'th depth.
	while(!board->isGoalState())
	{
		std::stack<std::vector<Brick*>> moves;
		traverse(board, depth, moves);
	}
	output.close();

	cout << "Made it to a goal state!" << endl;
}

void traverse(Board* board, int depth, std::stack<std::vector<Brick*>> moves)
{
	std::vector<Brick*> availablesMoves = board->getAvailableLegalMoves();//Get's array of possible moves given current emptyBrick spot.
	moves.push(board->getAvailableLegalMoves());//Get's array of possible moves given current emptyBrick spot.
	vector<Brick*> visitedBricks;	
	for(std::vector<Brick*>::iterator it = availablesMoves.begin(); it != availablesMoves.end(); ++it) { //For each possible move
			board->move(*it);
			(*it)->visited = true;
			visitedBricks.push_back((*it));
			
			if(depth > 0){
				startTraverse(board, depth-1);
			}else{
				//Got to the furthest leaf. 
				board->drawBoard();
				board->drawVisited();
				system("pause");
				cleanVisitedBricks(visitedBricks);
				//Need to reset back to the initial position
			}
		}
}

void cleanVisitedBricks(std::vector<Brick*> bricks)
{
	for(std::vector<Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it) { //For each possible move
		(*it)->visited = false;
	}
	bricks.erase (bricks.begin(),bricks.end());
}

void menuMove(Board* board)
{
	bool active = true;
	ofstream output(board->currentOutputFile);
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

	output.close();
}



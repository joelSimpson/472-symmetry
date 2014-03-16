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
const int MAX_DEPTH = 5;

void menuMove(Board* board);
void startTraverse(Board* board);
void traverse(Board* board, int depth, std::vector<Brick*> moves, Brick* previous);
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

			//Prompt for moving
			//menuMove(board);

			//Replacing menuMove.
			startTraverse(board);

			//TODO: Move the close outside the while for a complete read of file
			input.close();//Force close reading so we only read first line.. for now.
		}
		
	}else{
		cout << "Unable to open file." << endl;
	}

	system("pause");
	return 0;
}

void startTraverse(Board* board)
{
	ofstream output(board->currentOutputFile);

	std::vector<Brick*> availablesMoves = board->getAvailableLegalMoves();//Get 4 moves
	for(std::vector<Brick*>::iterator it = availablesMoves.begin(); it != availablesMoves.end(); ++it)
	{
		for(int i = 0; i < MAX_DEPTH; i++)//Until max depth
		{
			Brick* previous = board->emptyBrick;
			board->move(*it);//move

			std::stack<std::vector<Brick*>> moreMoves;
			moreMoves.push(board->getAvailableLegalMoves());

			for(std::vector<Brick*>::iterator itt = moreMoves.top().begin(); itt != moreMoves.top().end(); ++itt)//get moves
			{
				cout << "We now have:" << moreMoves.size() << " moves available" << endl;
				if((*itt) != previous){
					board->move(*itt);
					moreMoves.push(board->getAvailableLegalMoves());//This doesn't work because there's no way to.. "refresh" the data held in the for loop.
					board->drawBoard();
					system("pause");
				}
					
			
				//}
			}
			
		}
	}
	//Currently just goes to n'th depth.
	//while(!board->isGoalState())
	//{
		//traverse(board, depth, board->getAvailableLegalMoves(), board->emptyBrick);
	//}
	output.close();

	cout << "Made it to a goal state!" << endl;
}

void traverse(Board* board, int depth, std::vector<Brick*> moves, Brick* previous)
{
	//std::vector<Brick*> availablesMoves = board->getAvailableLegalMoves();//Get's array of possible moves given current emptyBrick spot.
	//moves.push(board->getAvailableLegalMoves());//Get's array of possible moves given current emptyBrick spot.

	vector<Brick*> visitedBricks;
	for(std::vector<Brick*>::iterator it = moves.begin(); it != moves.end(); ++it) { //For each possible move
		if((*it) == previous){

			break;
		}
		previous = board->emptyBrick;
		board->move(*it);
		board->drawBoard();
		//(*it)->visited = true;
		//visitedBricks.push_back((*it));
			
		if(depth > 0){
			cout << "CALLING TRAVERSE" << endl;
			//moves.push(board->getAvailableLegalMoves());//Get's array of possible moves given current emptyBrick spot.
			traverse(board, depth-1, board->getAvailableLegalMoves(), previous);
		}else{
			//Got to the furthest leaf.
			//board->drawBoard();
			//system("pause");
			//Need to reset back to the initial position
			//(*it)->visited = false;
			//board->move(previous);
			//board->drawBoard();
			//
		}
		
		system("pause");	
	}


	//system("pause");
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



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
	std::cout << "Reading from file: " << file1 << endl;

	string inputString;
	ifstream input(file1+".txt");
	if(input.is_open()){
		while(getline (input, inputString))
		{
			//inputString.append(inputString);
			
			std::cout << "I read this line: " << inputString << endl;

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
		std::cout << "Unable to open file." << endl;
	}

	std::system("pause");
	return 0;
}

void startTraverse(Board* board)
{
	ofstream output(board->currentOutputFile);

	int count = 0;
	std::vector<Brick*> availablesMoves1 = board->getAvailableLegalMoves();//Depth 1
	for(std::vector<Brick*>::iterator it1 = availablesMoves1.begin(); it1 != availablesMoves1.end(); ++it1)
	{
		Brick* previous1 = board->emptyBrick;
		if((*it1) != previous1)
			board->move(*it1);//move
		else
			std::cout << "Avoiding useless move" << endl;

		std::vector<Brick*> availablesMoves2 = board->getAvailableLegalMoves();//Depth 2
		for(std::vector<Brick*>::iterator it2 = availablesMoves2.begin(); it2 != availablesMoves2.end(); ++it2)
		{
			Brick* previous2 = board->emptyBrick;
			if((*it2) != previous2)
				board->move(*it2);//move
			else
				std::cout << "Avoiding useless move" << endl;

			std::vector<Brick*> availablesMoves3 = board->getAvailableLegalMoves();//Depth 3
			for(std::vector<Brick*>::iterator it3 = availablesMoves3.begin(); it3 != availablesMoves3.end(); ++it3)
			{
				Brick* previous3 = board->emptyBrick;
				if((*it3) != previous3)
					board->move(*it3);//move
				else
					std::cout << "Avoiding useless move" << endl;

				std::vector<Brick*> availablesMoves4 = board->getAvailableLegalMoves();//Depth 4
				for(std::vector<Brick*>::iterator it4 = availablesMoves4.begin(); it4 != availablesMoves4.end(); ++it4)
				{
					Brick* previous4 = board->emptyBrick;
					if((*it4) != previous4)
						board->move(*it4);//Move
					else
						std::cout << "Avoiding useless move" << endl;

					std::vector<Brick*> availablesMoves5 = board->getAvailableLegalMoves();//Depth 5
					for(std::vector<Brick*>::iterator it5 = availablesMoves5.begin(); it5 != availablesMoves5.end(); ++it5)
					{
						Brick* previous5 = board->emptyBrick;
						if((*it5) != previous5){
							board->move(*it5);
							board->drawBoard();
							board->move(previous5);
						}else{
							std::cout << "Avoiding useless move" << endl;
						}
						//Leaf node. 5 deep.
						
					}

					board->move(previous4);
				}

				board->move(previous3);
			}

			board->move(previous2);
		}

		board->move(previous1);
	}
	//Currently just goes to n'th depth.
	//while(!board->isGoalState())
	//{
		//traverse(board, depth, board->getAvailableLegalMoves(), board->emptyBrick);
	//}
	output.close();

	std::cout << "Made it to a goal state!" << endl;
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
			std::cout << "CALLING TRAVERSE" << endl;
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
		
		std::system("pause");	
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
		std::cout << "\nEnter wasd to move the empty spot or e to exit: ";
		string key;
		cin >> key;
		std::cout << "\n";
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
			std::cout << "Illegal move! Please try again.\n\n";
		}
		else if(board->isGoalState())
		{
			std::cout << "This is a goal state!\n\n";
		}
		//Print board
		board->drawBoard();

		//save legal moves only
		if(movement_status)
			board->writeToOutput(output);
	}

	output.close();
}



#include "brick.h"
#include "board.h"
#include "node.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <limits>

using namespace std;

const string file1 = "../test1";
const string OUTPUT_FILE = "../OUTPUT.txt";
const int heuristic = 2;

void menuMove(Board* board, ofstream& output);
vector<Node*> reconstruct_path(Node *node);
vector<Node*> a_star(Node *root);

int main(int argc, char* argv[]) {
	cout << "Reading from file: " << file1 << endl;

	string inputString;
	ifstream input(file1+".txt");

	if(input.is_open()){
		ofstream output(OUTPUT_FILE);
		//Start Timer
		std::clock_t start;
		start = std::clock();
		double lastTime = 0;
		int total_steps = 0;
		int puzzle_count = 0;
		while(getline (input, inputString))
		{
			puzzle_count++;
			Board *board = new Board(inputString);
			Node *treeRoot = new Node(board, heuristic);
			vector<Node*> optimal_path = a_star(treeRoot);

			Node *currentNode = NULL;
			string move_sequence = "";
			int initial_size = optimal_path.size();
			total_steps += initial_size;

			//Print the moves
			for (int i = 0; i < initial_size; i++)
			{
				currentNode = optimal_path.back();
				Board *currentBoard = currentNode->data;
				char position = currentBoard->getEmptyPositionLetter();
				cout << "\nMove #" << i;

				if(i == initial_size - 1)
				{
					cout << " (GOAL)";
				}
				cout << " Position: " << position;
				cout << "\n-----------------\n";
				move_sequence += position;
				currentNode->data->drawBoard();
				optimal_path.pop_back();
			}
			double time = ( std::clock() - start - lastTime );
			cout << "moves: " << move_sequence << "\n";
			cout << "Time: " << time << " ms\n";
			cout << "Steps: " << initial_size << "\n";
			output << move_sequence << "\n";
			output << time << "ms\n";
			//Prompt for moving
			//menuMove(board, output);
			lastTime = std::clock() - start;
		}
		input.close();
		
		cout << "-----------------\n";
		cout << "Total time: " << lastTime << " ms\n";
		cout << "Total steps: " << total_steps << "\n";
		cout << "Total of puzzle solved: " << puzzle_count << "\n";
		cout << "Avg number of steps: " << total_steps / puzzle_count << "\n";
		cout << "Avg solving time: " << lastTime / puzzle_count << " ms\n";
		output << total_steps << "\n";
		output << lastTime << "\n";
		output.close();
		
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

vector<Node*> reconstruct_path(Node *node)
{

	vector<Node*> path;
	Node *currentPathNode = node;
	path.push_back(currentPathNode);

	while (currentPathNode->parent != NULL)
	{
		currentPathNode = currentPathNode->parent;
		path.push_back(currentPathNode);
	}
	return path;
} 

//Using a star to search through the tree
//Returns the path as a vector
//Pop the vector for the first node in the path
vector<Node*> a_star(Node *root)
{
	vector<Node*> openList;
	vector<Node*> closeList;
	vector<Node*> path;
	Node *bestnode = NULL;

	//Push start node into open list
	openList.push_back(root);
	
	while(openList.size() > 0)
	{
		int min_f = numeric_limits<int>::max();
		int index = -1;
		bestnode = NULL;
		//Get optimal node in open list
		for (int i = 0; i < openList.size(); i++)
		{
			Node *currentNode = openList[i];
			int f = 1 + currentNode->h_cost;
			int estimate = currentNode->g_cost_so_far + f;
			if(estimate < min_f)
			{
				min_f = estimate;
				bestnode = currentNode;
				index = i;
			}
		}

		//Goal state found, we return the reconstructed path
		if(bestnode->data->isGoalState())
		{
			return reconstruct_path(bestnode);
		}

		openList.erase(openList.begin() + index);
		closeList.push_back(bestnode);

		bestnode->generateChildrens();
		vector<Node*> neighbors = bestnode->children;
		for (int i = 0; i < neighbors.size(); i++)
		{
			Node *currentNeighbor = neighbors[i];

			//If node is already on the closed list skip the node
			if(find(closeList.begin(), closeList.end(), currentNeighbor) != closeList.end())
			{
				continue;
			}

			int g_cost = bestnode->g_cost_so_far + 1;

			//Check if the neighbor is not already on the open list
			bool notOpened = find(openList.begin(), openList.end(), currentNeighbor) == openList.end();

			if(notOpened || g_cost < currentNeighbor->g_cost_so_far)
			{
				currentNeighbor->parent = bestnode;
				currentNeighbor->g_cost_so_far = g_cost;

				if(notOpened)
				{
					openList.push_back(currentNeighbor);
				}
			}
		}
	}

	//Return optimal path without finding the goal state
	//This is the worst case and would be equivalent to Dijkstra's algorithm
	return reconstruct_path(bestnode);
}



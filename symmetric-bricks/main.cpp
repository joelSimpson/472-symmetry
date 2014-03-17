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

void menuMove(Board* board, ofstream& output);

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
			int f = 1 + currentNode->getHeuristic2();
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
			int depth = 9;
			Node *treeRoot = new Node(board);
			treeRoot->generateTree(1, depth);
			bool goal_found = false;

			while(!goal_found)
			{
				vector<Node*> optimal_path = a_star(treeRoot);
				int initial_size = optimal_path.size();
				Node *currentNode;
				//Print the path
				for (int i = 0; i < initial_size; i++)
				{
					currentNode = optimal_path.back();
					cout << "\nMove #" << i;

					if(i == optimal_path.size() - 1 && currentNode->data->isGoalState())
					{
						cout << " (GOAL)";
						goal_found = true;
					}

					cout << "\n-----------------\n";
				
					currentNode->data->drawBoard();
					optimal_path.pop_back();
				}

				//If goal was not found generate new tree and continue search
				if(!goal_found)
				{
					//TODO: maybe try delete old tree and create new Node then create a tree. For efficiency nd testing
					currentNode->generateTree(1, depth);
					treeRoot = currentNode;
					cout << "\ncontinue...\n";
					string input;
					cin >> input;
				}
			}

			//TODO: Remove the manual moving for deliverable 2, 3
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



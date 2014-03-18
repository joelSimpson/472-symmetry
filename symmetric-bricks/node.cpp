#include "node.h"
using namespace std;

Node::Node()
{
	data = NULL;
	parent = NULL;
	g_cost_so_far = 0;
	h_cost = 0;
	heuristic = 0;
}

Node::Node(Board *currentBoard, int heuristic)
{
	data = currentBoard;
	parent = NULL;
	g_cost_so_far = 0;

	this->heuristic = heuristic;

	switch (heuristic)
	{
		case 1:
			h_cost = currentBoard->heuristic1();
			break;
		case 2:
			h_cost = currentBoard->heuristic2();
			break;
		default:
			h_cost = currentBoard->heuristic2();
			break;
	}
}

//Generate the possible moves as children
void Node::generateChildrens()
{
	if(this->data != NULL)
	{
		string lastMove = "";

		if(parent != NULL)
			lastMove = parent->data->toString();

		Board *up = new Board(data->toString());
		Board *right = new Board(data->toString());
		Board *left = new Board(data->toString());
		Board *down = new Board(data->toString());

		//Push only valid moves
		if(up->moveUp() && lastMove.compare(up->toString()) != 0)
			children.push_back(new Node(up, heuristic));
		if(right->moveRight() && lastMove.compare(right->toString()) != 0)
			children.push_back(new Node(right, heuristic));
		if(left->moveLeft() && lastMove.compare(left->toString()) != 0)
			children.push_back(new Node(left, heuristic));
		if(down->moveDown() && lastMove.compare(down->toString()) != 0)
			children.push_back(new Node(down, heuristic));

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->parent = this;
		}
	}
}

//When calling this method to generate the tree current depth should be set to 1
void Node::generateTree(int currentDepth, int depth)
{
	if(this->data != NULL && currentDepth <= depth)
	{
		this->generateChildrens();

		for(vector<Node*>::iterator currentNode = this->children.begin(); currentNode != this->children.end(); currentNode++)
		{
			(*currentNode)->generateTree(currentDepth + 1, depth);
		}
	}
}
#include "node.h"
using namespace std;

Node::Node()
{
	data = NULL;
}

Node::Node(Board *currentBoard)
{
	data = currentBoard;
}

//Generate the possible moves as children
void Node::generateChildrens()
{
	if(this->data != NULL)
	{
		Board *up = new Board(data->toString());
		Board *right = new Board(data->toString());
		Board *left = new Board(data->toString());
		Board *down = new Board(data->toString());

		//Push only valid moves
		if(up->moveUp())
			children.push_back(new Node(up));
		if(right->moveRight())
			children.push_back(new Node(right));
		if(left->moveLeft())
			children.push_back(new Node(left));
		if(down->moveDown())
			children.push_back(new Node(down));
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
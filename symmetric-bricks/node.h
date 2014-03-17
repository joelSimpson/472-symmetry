#ifndef NODE_H
#define NODE_H

#include <vector>
#include "board.h"

using namespace std;

class Node
{
	public:
		Node();
		Node(Board*);

		Board *data;
		vector<Node*> children;
		Node *parent;

		void generateChildrens();
		void generateTree(int currentDepth, int depth);
};
#endif
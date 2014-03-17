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
		int g_cost_so_far;
		int h_cost;

		int getHeuristic1();
		int getHeuristic2();
		void generateChildrens();
		void generateTree(int currentDepth, int depth);
};
#endif
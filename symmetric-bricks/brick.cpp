#include "brick.h"

//Brick constructor
Brick::Brick(char assignedColour)
{
	this->colour = assignedColour;
}

//Getters for Bricks
Brick* Brick::getTopNeighbour()
{
	return this->topNeighbour;
}

Brick* Brick::getRightNeighbour()
{
	return this->rightNeighbour;
}

Brick* Brick::getBottomNeighbour()
{
	return this->bottomNeighbour;
}

Brick* Brick::getLeftNeighbour()
{
	return this->leftNeighbour;
}

char Brick::getColour()
{
	return this->colour;
}


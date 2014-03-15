#include "brick.h"
#include <iostream>
using namespace std;

//Brick constructor
Brick::Brick(char colour)
{
	this->colour = colour;
	this->visited = false;
	this->topNeighbour = NULL;
	this->rightNeighbour = NULL;
	this->leftNeighbour = NULL;
	this->bottomNeighbour = NULL;
}


//--------------Getters for Bricks
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
//--------------------------------

//--------------Setters for Bricks
void Brick::setTopNeighbour(Brick* neighbour)
{
	this->topNeighbour = neighbour;
}

void Brick::setRightNeighbour(Brick* neighbour)
{
	this->rightNeighbour = neighbour;
}

void Brick::setBottomNeighbour(Brick* neighbour)
{
	this->bottomNeighbour = neighbour;
}

void Brick::setLeftNeighbour(Brick* neighbour)
{
	this->leftNeighbour = neighbour;
}

//--------------------------------
void Brick::setColour(char colour)
{
	this->colour = colour;
}

char Brick::getColour()
{
	return this->colour;
}


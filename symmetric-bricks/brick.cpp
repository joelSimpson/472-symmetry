#include "brick.h"

//Brick constructor
Brick::Brick()
{

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
char Brick::getColour()
{
	return this->colour;
}


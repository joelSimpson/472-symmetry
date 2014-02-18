#include "brick.h"
#include <iostream>
using namespace std;

//Brick constructor
Brick::Brick(char colour)
{
	this->colour = colour;

}

//--------------Moving for Bricks
void Brick::moveUp(Brick* emptyBrick)
{
	if(this->getTopNeighbour() != NULL){
		
	}else{
		cout << "Cannot move Up." << endl;
	}
	
}

void Brick::moveRight()
{
	if(this->getRightNeighbour() != NULL){

	}else{
		cout << "Cannot move Right." << endl;
	}
}

void Brick::moveDown()
{
	if(this->getBottomNeighbour() != NULL){

	}else{
		cout << "Cannot move Down." << endl;
	}
}

void Brick::moveLeft()
{
	if(this->getLeftNeighbour() != NULL){

	}else{
		cout << "Cannot move Left." << endl;
	}
}
//--------------------------------

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


#ifndef BRICK_H
#define BRICK_H
#include <iostream>

class Brick
{

public:
	Brick(char);
	
	Brick* topNeighbour;
	Brick* rightNeighbour;
	Brick* bottomNeighbour;
	Brick* leftNeighbour;
	
	Brick* getTopNeighbour();
	Brick* getRightNeighbour();
	Brick* getBottomNeighbour();
	Brick* getLeftNeighbour();

	void setTopNeighbour(Brick*);
	void setRightNeighbour(Brick*);
	void setBottomNeighbour(Brick*);
	void setLeftNeighbour(Brick*);

	char getColour();
	void Brick::setColour(char);

private:
	char colour;
	

};



#endif //BRICK_H
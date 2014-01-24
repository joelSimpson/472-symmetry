#ifndef BRICK_H
#define BRICK_H

class Brick
{

public:
	Brick(char);
	Brick* getTopNeighbour();
	Brick* getRightNeighbour();
	Brick* getBottomNeighbour();
	Brick* getLeftNeighbour();
	char getColour();

private:
	char colour;
	Brick* topNeighbour;
	Brick* rightNeighbour;
	Brick* bottomNeighbour;
	Brick* leftNeighbour;
};



#endif //BRICK_H
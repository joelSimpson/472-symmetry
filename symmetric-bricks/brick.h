#ifndef BRICK_H
#define BRICK_H

class Brick
{

public:
	Brick();
	
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

private:
	char colour;
	

};



#endif //BRICK_H
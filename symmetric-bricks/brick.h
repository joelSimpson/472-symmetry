#ifndef BRICK_H
#define BRICK_H

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

	void moveUp(Brick*);
	void moveRight();
	void moveDown();
	void moveLeft();

	char getColour();

private:
	char colour;
	

};



#endif //BRICK_H
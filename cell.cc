#include "cell.h"
#include <iostream>
using namespace std;

// ctor for a Cell
Cell::Cell(): isAlive{false}, numNeighbours{0}, aliveNeighbours{0} {
	for (int i = 0; i < maxNeighbours; ++i)
		neighbours[i] = nullptr;
}

//dtor for a cell
// sets all of neighbours to nullptr, makes sure it is the grid 
// that destroys them all
Cell::~Cell(){
	for (int i = 0; i < maxNeighbours; ++i)
		neighbours[i] = nullptr;
}

// setliving will make this cell alive
void Cell::setLiving(){
	isAlive = true;
	draw();
}

// addneighbour will add the given cell to this cell's list of neighbours
void Cell::addNeighbour(Cell *neighbour) {
	if (numNeighbours == maxNeighbours){
		cerr << "You're adding too many neighbours!" << endl;
		return;
	}
	neighbours[numNeighbours] = neighbour;
	numNeighbours++;
}

// a neighbour will call this to say they are alive.
// It updates this cell's count of how many neighbours are alive
void Cell::neighbourIsAlive() {
	++aliveNeighbours;
}

// alertNeighbours will go through each neighbour, telling them I am alive,
//	only if I am alive
void Cell::alertNeighbours(){
	if (!isAlive) return;
	for (int i = 0; i < numNeighbours; ++i){
		neighbours[i]->neighbourIsAlive();
	}
}

// recalculate will check to see if a cell is alive or dead based on the rules and
// 	how many of it's neighbours are alive. 
// It then resets to be ready for the next iteration
void Cell::recalculate(){
	if (!isAlive) {
		if (aliveNeighbours == 3){ isAlive = true;
			draw();
		}
	} else if (aliveNeighbours < 2 || aliveNeighbours > 3) {
		isAlive = false;
		undraw();
	}
	aliveNeighbours = 0;
}

ostream &operator<<(ostream &out, const Cell &c){
	if (c.isAlive){
		out << "X";
	} else {
		out << "_";
	}
	return out;
}

// sets the coordinates and the height/width of a cell
void Cell::setCoordinates(int x, int y, int height, int width, Xwindow *xw){
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->xw = xw;
	undraw();
}

// draw is called to draw an alive cell
void Cell::draw(){
	xw->fillRectangle(x,y,width,height);
}

// undraw is valled when a cell dies
void Cell::undraw(){
	xw->fillRectangle(x,y,width,height, 0);
}

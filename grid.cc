#include "grid.h"
using namespace std;

// ctor for a grid
Grid::Grid(): size{0} {
 xw = new Xwindow();
}

// dtor for a grid
Grid::~Grid() {
 clearGrid();
}

// init will create an nxn grid willed with cells
// it sets the coordinates for each call and calls each cell's undraw method
void Grid::init(int n){
	clearGrid();
	size = n;
	if (n == 0) return;
	for (int i = 0; i < n; ++i){
		vector<Cell> v;
		for (int j = 0; j < n; ++j) {
			Cell c;
			int height = 500 / n;
			int xcoor = height * j;
			int ycoor = height * i;
			c.setCoordinates(xcoor, ycoor, height, height, xw);  
			v.emplace_back(c);
			}
		theGrid.emplace_back(v);
	}
	fillNeighbours();
}

// fillNeighbours will loop through each cell and fill it's array of neighbours 
void Grid::fillNeighbours() {
	int i = 0;
	for (vector<vector<Cell>>::iterator it = theGrid.begin();
					it != theGrid.end(); ++it, ++i){
		int j = 0;
		for(vector<Cell>::iterator cit = it->begin(); 
					 cit != it->end(); ++cit, ++j) {
			findAbove(i, j, *cit);
			findBelow(i, j, *cit);
			findSides(i, j, *cit);
		}
	}
} 
		
// findAbove will find all of a cell's neighbours in the row above it
void Grid::findAbove(int row, int col, Cell &c){
	if (row == 0) return;
	c.addNeighbour(findCell(row-1, col));
	if (col != 0) c.addNeighbour(findCell(row-1, col-1));
	if (col != size-1) c.addNeighbour(findCell(row-1, col+1));
}

// findBelow finds all of a cell's neighbours in the row below the cell
void Grid::findBelow(int row, int col, Cell &c){
	if (row == size-1) return;
	c.addNeighbour(findCell(row+1, col));
	if (col != 0) c.addNeighbour(findCell(row+1, col-1));
	if (col != size-1) c.addNeighbour(findCell(row+1, col+1));
}

// findSides will find all of a cell's neighbours to either side in 
//	the same row
void Grid::findSides(int row, int col, Cell &c){
	if (col != 0) c.addNeighbour(findCell(row, col-1));
	if (col != size-1) c.addNeighbour(findCell(row, col+1));
}

// findCell will return a pointer to the cell in the given row and column
Cell *Grid::findCell(int row, int col){
	return &(theGrid.at(row).at(col));
}

// turnOn will make the cell at the given coordinates alive
void Grid::turnOn(int x, int y){
	findCell(y, x)->setLiving();
}

//tick runs one iteration of the game
void Grid::tick(){
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			theGrid.at(i).at(j).alertNeighbours();
		}
	}
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j) {
			theGrid.at(i).at(j).recalculate();
		}
	} 
}

// clearGrid destroys the grid 
void Grid::clearGrid() {
	theGrid.clear();
}

// this is the output operator for a Grid
ostream & operator<<(ostream &out, const Grid &g){
	int n = g.size;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j){
			out << g.theGrid.at(i).at(j);
		}
	out << endl;
	}
return out;
}

#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "window.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.

  // Add private members, if necessary.
  int size;
  void fillNeighbours(); // adds each cell's neighbours
  void clearGrid();   // Frees the grid.
  Cell *findCell(int, int); // return a specific cell
  void findAbove(int, int, Cell&);
  void findBelow(int, int, Cell&);
  void findSides(int, int, Cell&);
  Xwindow *xw;

 public:
  Grid();
  ~Grid();

  void init(int n); // Sets up an n x n grid.  Clears old grid, if necessary.
                    // Initializes every cell in the grid, and tells each
                    // cell who its neighbours are.

  void tick();      // Runs one iteration of the simulation.
                    // Tells each cell to alert its neighbours, and then
                    // tells each cell to recalculate.

  void turnOn(int i, int j);  // Sets cell at i, j to living.

  friend std::ostream& operator<<(std::ostream &out, const Grid &g);
};

#endif

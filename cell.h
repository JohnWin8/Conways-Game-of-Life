#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "window.h"

const int maxNeighbours = 8;

class Cell {
  bool isAlive;
  int numNeighbours;
  Cell *neighbours[maxNeighbours];
  int aliveNeighbours;
  int x, y, height, width;
  Xwindow *xw;
  void draw();
  void undraw();    
  // Add other private members if necessary

 public:
  Cell();  // Default constructor
  ~Cell(); // Destructor

  void setCoordinates(int, int, int, int, Xwindow*);

  void setLiving();         // Explicitly sets me to living.

  void addNeighbour(Cell *neighbour);  // Adds a pointer to one of my
                            // neighbours to my array.

  void neighbourIsAlive();  // My neighbours will call this, to let me know
                            // they're alive.

  void alertNeighbours();   // Tell all of my neighbours that I am alive
                            // (if I'm alive).

  void recalculate();       // Reassess my living-or-dead status, based on
                            // info from neighbours.

  friend std::ostream& ::operator<<(std::ostream &out, const Cell &c);
};

#endif

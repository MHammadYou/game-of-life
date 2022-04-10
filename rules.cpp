#include "cell.cpp"

class Rules
{

public:

//  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//  Any live cell with more than three live neighbours dies, as if by overpopulation.

  static void populationCrisis(Cell* cell, int aliveNeighbours)
  {
    if ((aliveNeighbours < 2 || aliveNeighbours > 3) && cell->isAlive())
    {
      cell->kill();
    }
  }

//  Any live cell with two or three live neighbours lives on to the next generation.
//  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

  static void birth(Cell* cell, int aliveNeighbours)
  {
    if (aliveNeighbours == 3 && cell->isDead())
    {
      cell->birth();
    }
  }

};
#include <iostream>
#include <vector>

class Cell
{
private:
  std::string m_State;
  int m_X, m_Y;

public:
  Cell(const std::string& state, int x, int y)
  {
    m_State = state;
    m_X = x;
    m_Y = y;
  }

  std::vector< std::vector<int> > getNeighbours(int worldSize)
  {

    std::vector< std::vector<int> > neighbours;

    int possibleNeighbours[8][2] = {
      {m_X - 1, m_Y - 1}, {m_X - 1, m_Y}, {m_X - 1, m_Y + 1},
      {m_X, m_Y - 1},                     {m_X, m_Y + 1},
      {m_X + 1, m_Y - 1}, {m_X + 1, m_Y}, {m_X + 1, m_Y + 1},};

    for (int i = 0; i < 8; i++)
    {
      const int x = possibleNeighbours[i][0];
      const int y = possibleNeighbours[i][1];


      if (!(x < 0 || x > worldSize - 1 || y > worldSize - 1 || y < 0)) {

        std::vector<int> neighbour;
        neighbour.push_back(x);
        neighbour.push_back(y);
        neighbours.push_back(neighbour);
      }
    }

    return neighbours;

  }


  std::string getState()
  {
    return m_State;
  }

  void setState(const std::string& newState)
  {
    m_State = newState;
  }

  int getX() const
  {
    return m_X;
  }

  int getY() const
  {
    return m_Y;
  }
};


class Rules
{

//  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//  Any live cell with more than three live neighbours dies, as if by overpopulation.

public:

  static void populationCrisis(Cell* cell, int aliveNeighbours)
  {
    if ((aliveNeighbours < 2 || aliveNeighbours > 3) && cell->getState() == " # ")
    {
      cell->setState(" . ");
    }
  }

//  Any live cell with two or three live neighbours lives on to the next generation.


//  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

  static void birth(Cell* cell, int aliveNeighbours)
  {
    if (aliveNeighbours == 3 && cell->getState() == " . ")
    {
      cell->setState(" # ");
    }
  }


};


class World
{
private:
  static const int worldSize = 10;
  Cell* m_World[worldSize][worldSize];

public:
  World() : m_World()
  {

    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        m_World[i][j] = new Cell(" . ", i, j);
      }
    }
    m_World[5][1]->setState(" # ");
    m_World[2][2]->setState(" # ");
    m_World[3][2]->setState(" # ");
    m_World[7][4]->setState(" # ");
    m_World[9][1]->setState(" # ");
    m_World[2][8]->setState(" # ");
    m_World[2][6]->setState(" # ");
    m_World[2][7]->setState(" # ");
    m_World[2][8]->setState(" # ");
    m_World[1][6]->setState(" # ");
    m_World[4][6]->setState(" # ");
    m_World[1][3]->setState(" # ");
    m_World[0][5]->setState(" # ");
    m_World[1][2]->setState(" # ");
  }

  std::vector< Cell* > getAliveNeighbours(int _i, int _j)
  {
    std::vector< std::vector<int> > neighbours = m_World[_i][_j]->getNeighbours(worldSize);
    std::vector< Cell* > aliveNeighbours;


    for (int i = 0; i < neighbours.size(); i++)
    {
      Cell* cell = m_World[neighbours[i][0]][neighbours[i][1]];
      if (cell->getState() == " # ")
      {
        aliveNeighbours.push_back(cell);
      }
    }

    return aliveNeighbours;
  }

  void applyRules()
  {
    for (int i = 0; i < worldSize; i++)
    {
      for (int j = 0; j < worldSize; j++)
      {
        const std::vector<Cell*> aliveNeighbours = getAliveNeighbours(i, j);
        Rules::birth(m_World[i][j], aliveNeighbours.size());
        Rules::populationCrisis(m_World[i][j], aliveNeighbours.size());
      }
    }

  }

  void logWorld()
  {
    std::cout << "  ";
    for (int i = 0; i < 10; i++)
    {
      std::cout << "___";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++)
    {
      std::cout << "| ";
      for (int j = 0; j < 10; j++)
      {
        std::cout << m_World[i][j]->getState();
      }
      std::cout << " |" << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i < 10; i++)
    {
      std::cout << "___";
    }
    std::cout << std::endl;
  }
};



int main()
{
  World world;

  for (int i = 0; i < 10; i++)
  {
    world.logWorld();
    world.applyRules();
  }
  world.logWorld();
}

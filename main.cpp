#include <iostream>
#include <vector>

class Cell
{
private:
  std::string m_State;
  int m_X, m_Y;

  void setState(const std::string& newState)
  {
    m_State = newState;
  }

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

    for (auto & possibleNeighbour : possibleNeighbours)
    {
      const int x = possibleNeighbour[0];
      const int y = possibleNeighbour[1];


      if (!(x < 0 || x > worldSize - 1 || y > worldSize - 1 || y < 0))
      {

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

  void kill()
  {
    setState(" . ");
  }

  void birth()
  {
    setState(" # ");
  }

  bool isAlive()
  {
    return getState() == " # ";
  }

  bool isDead()
  {
    return getState() == " . ";
  }
};


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


class World
{
private:
  static const int worldSize = 10;
  Cell* m_World[worldSize][worldSize];

public:
  explicit World(int size) : m_World()
  {

    for (int i = 0; i < worldSize; i++)
    {
      for (int j = 0; j < worldSize; j++)
      {
        m_World[i][j] = new Cell(" . ", i, j);
      }
    }

    const int liveCellsCount = 15;

    int initialCells[liveCellsCount][2] = {{5, 1},
                               {1, 1},
                               {2, 2},
                               {3, 2},
                               {7, 4},
                               {9, 1},
                               {2, 8},
                               {2, 6},
                               {2, 7},
                               {1, 6},
                               {4, 6},
                               {1, 3},
                               {0, 5},
                               {1, 2},
                               {0, 6}};

    for (auto & initialCell : initialCells)
    {
      const int _i = initialCell[0];
      const int _j = initialCell[1];
      m_World[_i][_j]->birth();
    }
  }

  int getAliveNeighbours(int _i, int _j)
  {
    std::vector< std::vector<int> > neighbours = m_World[_i][_j]->getNeighbours(worldSize);
    int aliveNeighbours = 0;


    for (auto & neighbour : neighbours)
    {
      Cell* cell = m_World[neighbour[0]][neighbour[1]];
      if (cell->isAlive())
      {
        aliveNeighbours++;
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
        int totalAliveNeighbours = getAliveNeighbours(i, j);
        Rules::birth(m_World[i][j], totalAliveNeighbours);
        Rules::populationCrisis(m_World[i][j], totalAliveNeighbours);
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
    for (auto & i : m_World)
    {
      std::cout << "| ";
      for (auto & j : i)
      {
        std::cout << j->getState();
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
  World world{10};

  for (int i = 0; i < 50; i++)
  {
    world.logWorld();
    world.applyRules();
  }
  world.logWorld();
}

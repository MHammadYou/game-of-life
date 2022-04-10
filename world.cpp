#include "rules.cpp"

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
                                           {1, 7},
                                           {2, 5},
                                           {2, 5},
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
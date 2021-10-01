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

  void getNeighbours(int worldSize)
  {

    std::vector< std::vector<int> > neighbours;

    int possibleNeighbours[8][2] = {
      {m_X - 1, m_Y - 1}, {m_X - 1, m_Y}, {m_X - 1, m_Y + 1},
      {m_X, m_Y - 1},                     {m_X, m_Y + 1},
      {m_X + 1, m_Y - 1}, {m_X + 1, m_Y}, {m_X + 1, m_Y + 1},};

    for (int i = 0; i < 8; i++)
    {
      if (!(possibleNeighbours[i][0] < 0 || possibleNeighbours[i][1] < 0) || possibleNeighbours[i][0] > worldSize || possibleNeighbours[i][1] > worldSize) {
        std::cout << "X: " << possibleNeighbours[i][0] << "  Y: " << possibleNeighbours[i][1] << std::endl;
      }
    }
  }

  std::string getState()
  {
    return m_State;
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


class World
{
private:
  static const int worldSize = 10;
  Cell* m_World[worldSize][worldSize];

public:
  World() : m_World() {

    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        m_World[i][j] = new Cell(" . ", i, j);
      }
    }
  }

  void doSomething()
  {
    m_World[10][10]->getNeighbours(worldSize);
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


class Rules
{

};



int main()
{
  World world;
  world.logWorld();
  world.doSomething();
}

#include <iostream>

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
  Cell* m_World[10][10];

public:
  World() {

    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        m_World[i][j] = new Cell(".", i, j);
      }
    }
  }
  void logWorld()
  {
    for (int i = 0; i < 10; i++)
    {
      std::cout << "_";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        std::cout << m_World[i][j]->getState();
      }
      std::cout << std::endl;
    }
  }
};


class Rules
{

};



int main()
{
  World world;
  world.logWorld();

}

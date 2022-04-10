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
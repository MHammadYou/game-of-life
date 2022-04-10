#include <chrono>
#include <thread>

#include "world.cpp"

int main()
{
  World world{10};
  world.logWorld();

  for (int i = 0; i < 50; i++)
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(500ms);

    world.applyRules();
    world.logWorld();
  }
}

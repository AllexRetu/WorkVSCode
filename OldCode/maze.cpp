// make_maze.cpp
// Неделя 10. Как бы оно могло быть сделано на основе
// Стандартной библиотеки C++...
#include <iterator>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
using namespace std;

template <class Rng>
auto make_maze(size_t w, size_t h, Rng & rng)
{
  vector<string> maze(h, string(w, '#'));
  auto walk = [&](size_t x, size_t y, auto & self) -> void
  {
    int dirs[] { 26, 28, 19, 35 };
    shuffle(begin(dirs), end(dirs), rng);
    maze[y][x] = ' ';
    for (int d: dirs)
    {
      int const dx = (d&7)-3, dy = ((d>>3)&7)-3;
      size_t const nx = x + 2*dx, ny = y + 2*dy;
      if (nx < 1 || maze[0].size() <= nx
       || ny < 1 || maze.size() <= ny
       || maze[ny][nx] != '#') continue;
      maze[y + dy][x + dx] = ' ';
      self(nx, ny, self);
    }
  };

  walk(w/2 | 1, h/2 | 1, walk);
  return maze;
}

int main()
{
  mt19937_64 rng(random_device{}());
  for (auto & line: make_maze(79, 23, rng))
    cout << line << '\n';
  return 0;
}

#include <iostream>
#include <ctime>
#include <fstream>

int main()
{
  srand((unsigned int)time(0));
  int n;
  std::cin >> n;
  std::ofstream out("Scores.txt");
  for(int i = 1; i < n; ++i)
  {
    for(int i = 0; i < 3; ++i)
      out << rand() % 101 << '\t';
    for(int i = 0; i < 3; ++i)
      out << rand() % 2 << '\t';
    out << std::endl;
  }
  for(int i = 0; i < 3; ++i)
    out << rand() % 101 << '\t';
  for(int i = 0; i < 2; ++i)
    out << rand() % 2 << '\t';
  out << rand() % 2;
  out.close();
  return 0;
}
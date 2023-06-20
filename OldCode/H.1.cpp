#include <iostream>
#include <fstream>
#include <dir.h>
#include <ctime>


// Создаем файл, которые будут столбцами
int main()
{
  srand((unsigned int)time(0));
  using namespace std;

  mkdir(".\\cols");
  for(size_t i = 0; i < 10; ++i)
  {
    string str = ".\\cols\\";
    str = str + to_string(i) + ".txt"; 
    ofstream f(str);

    for(size_t j = rand() % 11; j > 0; --j)
    {
      string line;

      for(size_t i = rand() % 11; i > 0; --i)
        line += (char)((rand() % 26) + 65);
      f << line << '\n';
    }

    string line;

    for(size_t i = rand() % 11; i > 0; --i)
      line += (char)((rand() % 26) + 65);
    f << line;

    f.close();
  }
}
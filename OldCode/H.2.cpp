#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

// Функция поиска максимальной длинны строки в файле
size_t max_line_size_in_file(ifstream & in)
{
  size_t max_size = 0;
  while(!in.eof())
  {
    string line;
    getline(in, line);
    if(max_size < line.size())
      max_size = line.size();
  }

  return max_size;
}

int main(int argc, char * argv[])
{
  // Массив файлов.
  vector<ifstream> files;
  // Открыть все файлы.
  for (int i = 1; i < argc; ++i)
    files.emplace_back(argv[i]);
  // Убрать файлы, которые не удалось открыть.
  files.erase(remove_if(files.begin(), files.end(),
    [](ifstream & f) { return !f.is_open(); }), files.end());
  
  // Поиск максимальной длинны строки в файлах
  vector<size_t> sizes(files.size());
  for(size_t i = 0; i < files.size(); ++i)
    sizes[i] = max_line_size_in_file(files[i]);
  
  // Повторное чтение файлов
  files.clear();
  for (int i = 1; i < argc; ++i)
    files.emplace_back(argv[i]);
  files.erase(remove_if(files.begin(), files.end(),
    [](ifstream & f) { return !f.is_open(); }), files.end());

  ofstream table("out.txt");
  string line;
  string tmp;
  while (any_of(files.begin(), files.end(), 
    [](ifstream & f) { return f.good(); }))
  {   
    size_t i = 0; 
    for (auto & in: files)
    {
      line.clear();
      getline(in, line);
      line.append(sizes[i] - line.size() + 3, ' ');   // регулируемый отступ 
      table << line;
      ++i;
    }

    table << '\n';
  }

  table.close();


  return 0;
}

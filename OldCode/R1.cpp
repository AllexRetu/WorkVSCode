#include <iostream>
#include <vector>
#include <fstream>

template <typename Matrix>
void print_matrix(std::ostream & out, Matrix const & matrix)
{
  for (auto r : matrix)
  {
    for (auto c : r)
      out << c;
    out << '\n';
  }
}

template <typename Matrix>
void scan_matrix(std::string fileName, Matrix & matrix)
{
  std::ifstream in1(fileName);
  size_t n = 0;
  size_t m = 0;
  std::string tmp;
  while (getline(in1, tmp) && tmp.find_first_not_of("01") == std::string::npos)
  {
    ++m;
    if (tmp.size() > n)
      n = tmp.size();
  }
  in1.close();

  matrix.resize(m, typename Matrix::value_type(n));

  std::ifstream in2(fileName);


  for (size_t i = 0; i < m; ++i)
  {
    getline(in2, tmp);
    for (size_t j = 0; j < n; ++j)
    {
      if (j < tmp.size())
        matrix[i][j] = tmp[j] - '0';
      else
        matrix[i][j] = 0;
    }
  }

  in2.close();
}

int main()
{
  std::vector<std::vector<int>> adjacencyMatrix
  {
    {0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0},
    {0, 0, 1, 1, 0},
  };

  std::ofstream out("Out.txt");
  for (auto const & a: adjacencyMatrix)
  {
    for (size_t i = 0; i < a.size(); ++i)
        out << a[i];
    out << '\n';
  }
  out.close();

  std::vector<std::vector<int>> am;

  scan_matrix("Out.txt", am);
  print_matrix(std::cout, am);
}
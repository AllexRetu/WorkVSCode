#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

template <typename Matrix>
void print(ofstream & out, Matrix const & matrix)
{
  out << matrix.size() << "x" << matrix.at(0).size() << '\n';

  for (auto r : matrix)
  {
    for (auto c : r)
      out << c;
    out << '\n';
  }
}

template <typename Matrix>
void scan(ifstream & in, Matrix & matrix)
{
  size_t n = 0;
  size_t m = 0;
  string tmp;
  getline(in, tmp);
  
  if (tmp.find('x') == string::npos)
    n = m = stoi(tmp);
  else
  {
    m = stoi(tmp.substr(0, tmp.find('x')));
    n = stoi(tmp.substr(tmp.find('x') + 1, string::npos));
  }

  matrix.resize(m, typename Matrix::value_type(n));


  for (size_t i = 0; i < m; ++i)
  {
    getline(in, tmp);
    for (size_t j = 0; j < n; ++j)
    {
      if (j < tmp.size())
        matrix[i][j] = tmp[j] - '0';
      else
        matrix[i][j] = 0;
    }
  }
}

int main()
{
  vector<vector<int>> adjacencyMatrix
  {
    {0, 1, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 0},
  };

  ofstream out("R2.txt");
  out << "5x6" << '\n';
  for (auto const & a: adjacencyMatrix)
  {
    for (size_t i = 0; i < a.size(); ++i)
        out << a[i];
    out << '\n';
  }
  out.close();

  vector<vector<int>> am;

  ifstream in("R2.txt");

  scan(in, am);
  in.close();

  ofstream out2("Out.txt");

  print(out2, am);
  out2.close();

  ifstream in2("Out.txt");
  for (string str; getline(in2, str);)
    cout << str << endl;
  in2.close();
}
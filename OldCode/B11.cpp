#include <iostream>
#include <vector>

using namespace std;

template <typename Matrix, typename Report>
void report_undirected_edges_of_incidents_matrix(Matrix const & matrix, Report report)
{
  int row_size = 0;
  if (!matrix.empty())
    row_size = matrix.at(0).size();


  for (int i = 0; i < row_size; ++i)
    for (int j = 0, u = -1; j < matrix.size(); ++j)
      if (matrix.at(j).at(i) == 1)
      {
        if (u == -1)
          u = j;
        else
        {
          report(u, j);
          report(j, u);
        }
      }
}

void print_edge(int u, int v)
{
  cout << u << " - " << v << endl;
}

int main()
{
  vector<vector<int>> graph
  { 
    {0, 0, 1, 0, 1},  // 0
    {1, 1, 0, 0, 0},  // 1
    {1, 0, 1, 1, 0},  // 2
    {0, 0, 0, 0, 1},  // 3
    {0, 1, 0, 1, 0}   // 4
  };

  report_undirected_edges_of_incidents_matrix(graph, print_edge);
}
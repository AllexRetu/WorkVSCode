#include <map>
#include <vector>
#include <iostream>

using namespace std;

map<int, vector<int>> transform_directed_adjacency_matrix_to_adjacency_list(vector<vector<int>> const & graph)
{
  map<int, vector<int>> graph2;
  for (size_t i = 0; i < graph.size(); ++i)
    graph2.emplace(i, vector<int>());
  
  for (size_t i = 0; i < graph.size(); ++i)
    for (size_t j = i; j < graph.size(); ++j)
    {
      if (graph.at(i).at(j) == 1)
        graph2.at(j).push_back(i);
      if (graph.at(i).at(j) == -1)
        graph2.at(i).push_back(j);
    }

  return graph2;
}

int main()
{
  vector<vector<int>> adjacency_matrix
  {
    {0, 1, 0 , -1, 0, 0},
    {-1, 0, -1, -1, 1, 0},
    {0, 1, 0, 0, 0, 1 },
    {1, 1, 0, 0, 1, -1 },
    {0, -1, 0, -1, 0, 0},
    {0, 0, -1, 1, 0, 0 }
  };

  map<int, vector<int>> adjacency_list = transform_directed_adjacency_matrix_to_adjacency_list(adjacency_matrix);

  for (size_t u = 0; u < adjacency_list.size(); ++u)
  {
    cout << u << " -- { ";
    for (auto v : adjacency_list.at(u))
      cout << v << ", ";
    cout << '}' << '\n';
  }
}
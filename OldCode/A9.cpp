#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename AdjacencyList>
void print_adjacency_list(AdjacencyList& list)
{
  for (size_t i = 0; i < list.size(); ++i)
  {
    cout << i << " -- { ";
    for (auto v: list[i])
      cout << v << ", ";
    cout << " }" << endl;
  }
}

template <typename AdjacencyList>
void add_directed_linear_adjacency_list(AdjacencyList& list, size_t u, size_t v)
{
  list[u].emplace_back(v);
}

int main()
{
  std::map<size_t, std::vector<size_t>> list
  { 
    {0, {1, 2, 5}},
    {1, {2, 4}},
    {2, {1, 3, 4}},
    {3, {0, 4, 5}},
    {4, {2, 3}},
    {5, {}}
  };
  
  print_adjacency_list(list);

  add_directed_linear_adjacency_list(list, 5, 1);
  cout << endl;

  print_adjacency_list(list);
}
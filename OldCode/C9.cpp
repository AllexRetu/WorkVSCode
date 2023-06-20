#include <vector>
#include <iostream>
#include <cmath>

size_t number_of_edges_in_undirected_graph(std::vector<size_t> const & am)
{
  size_t n = 0;
  size_t size = sqrt(am.size());
  for (size_t i = 0; i < size; ++i)
    for (size_t j = size*(i+1); j < size*size; j += size)
      n += am[j+i];
  return n;
}

int main()
{
  std::vector<size_t> adjacencyMatrix
  {
    0, 1, 0, 1, 1,
    1, 0, 0, 1, 0,
    0, 0, 0, 1, 1,
    1, 1, 1, 0, 1,
    1, 0, 1, 1, 0,
  };

  std::cout << number_of_edges_in_undirected_graph(adjacencyMatrix) << std::endl;;
}
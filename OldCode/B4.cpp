#include <iostream>
#include <map>
#include <vector>

template <typename AdjacencyList, typename Report>
void report_edges_of_adjacency_list(AdjacencyList const & list, Report report)
{
  for (size_t u = 0; u < list.size(); ++u)
    for (auto & v: list.at(u))
      report(u, v);
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

  report_edges_of_adjacency_list(list, [&](auto u, auto v)
  { std::cout << " { " << u << ", " << v << " }" << std::endl; });
}
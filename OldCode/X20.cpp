#include <map>
#include <vector>
#include <iostream>

template <typename Graph>
void print_direct_product(std::ostream & out, Graph const & g)
{
  for (auto const r : g)
  {
    out << "{ " << r.first.first << ", " << r.first.second << " }" << " - " << "{ ";
    for (auto c : r.second)
      out << "{ " << c.first << ", " << c.second << " }" << " , ";
    out << " }" << '\n';
  }
}

template <typename VT>
std::map<std::pair<VT, VT>, std::vector<std::pair<VT, VT>>> direct_product
(std::map<VT, std::vector<VT>> const & g, std::map<VT, std::vector<VT>> const & h)
{
  std::map<std::pair<VT, VT>, std::vector<std::pair<VT, VT>>> dp;

  for (auto const a : g)
    for (auto const b : h)
    {
      std::pair<VT, VT> vert = std::make_pair(a.first, b.first);
      std::vector<std::pair<VT,VT>> adj;

      for (auto const a1 : a.second)
        adj.push_back(std::make_pair(a.first, a1));
      for (auto const b1 : b.second)
        adj.push_back(std::make_pair(b1, b.first));

      dp.emplace(vert, adj);
    }


  return dp;  
}


int main()
{
  std::map<int, std::vector<int>> g
  {
    {0, {1, 3, 5,} },
    {1, {3, 4,} },
    {2, {0, } },
    {3, {2, 4, } },
    {4, {2, 3, 5} },
    {5, {0, } },
  },
  h
  {
    {0, {1, 2, } },
    {1, {0, 4, } },
    {2, {0, } },
    {3, {0, 1, 2, } },
  };

  print_direct_product(std::cout, direct_product(g, h));
}
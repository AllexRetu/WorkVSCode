#include <iostream>
#include <vector>
#include <map>

using Matrix = std::vector<std::vector<int>>;

void print_matrix(Matrix const & matrix)
{
  for (auto a: matrix)
  {
    for (auto b: a)
    {
      std::cout << b << "  ";
      if ( b != -1 )
        std::cout << " ";
    }
    std::cout << '\n';
  }
}

template <typename AdjacencyList>
Matrix transform_directed_agjacency_to_incidence_matrix(AdjacencyList const & list, Matrix & matrix)
{
  size_t number_of_edges = 0;
  for (size_t i = 0; i < list.size(); ++i)
    number_of_edges += list.at(i).size();
  matrix.resize(list.size(), std::vector<int>(number_of_edges, 0));

  for (size_t i = 0, k = 0; i < list.size(); ++i)
    for (auto j: list.at(i))
    {
      matrix[i][k] = 1;
      matrix[j][k] = -1;
      ++k;
    }

  return matrix;
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

  Matrix matrix;

  transform_directed_agjacency_to_incidence_matrix(list, matrix);

  print_matrix(matrix);
}
#include "G.cpp"
#include <iostream>
using namespace std;

bool sim_matrix_pack_wrapper(int const matrix[], size_t n)
{
  int** rmatrix;
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      rmatrix[j][i] = matrix[i*n + j];
  return sim_matrix( rmatrix, n);
}

int main()
{
  int const matrix[] = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9};
  cout << sim_matrix_pack_wrapper(matrix, 3) << endl;
  return 0;
}
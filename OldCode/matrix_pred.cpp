#include <iostream>

using namespace std;

void displ_rows_matrix(int * const matrix, int row, int rows, int cols)
{
  int link_last_row = rows*(cols-1)-1;
  int last_row[cols];
  for (int i = 0; i<cols; i++)
    last_row[i] = matrix[link_last_row+i];
  for (int n = link_last_row; n>row; n-=cols)
    for (int i = 0; i<cols; i++)
      matrix[n+i] = matrix[n-cols+i];
  for (int i = 0; i<cols; i++)
    matrix[row+i] = last_row[i];
}

void print_matrix(int * const matrix, int rows, int cols)
{
  for (int i = 1; i <= rows*cols; i++)
  {
    cout << matrix[i-1] << '\t';
    if (i%cols==0)
      cout << '\n';
  }
}

bool low_triangular(int const * const matrix, size_t n)
{
  for (size_t row = 0, nt_col = 0; nt_col < n; row+=n, nt_col++)
    for (size_t col = n-1; col > nt_col; col--)
      if (matrix[row+col]!=0)
        return false;
  return true;
}

bool top_triangular(int const * const matrix, int n)
{
  for (int row = 0, col1 = 0; col1 < n; row+=n, col1++)
    for (int col = 0; col < col1; col++)
      if (matrix[row+col]!=0)
        return false;
  return true;
}

int main()
{
  size_t n = 5;
  int const matrix1[n*n]
  { 3, 0, 0, 0, 0,
    0, 8, 0, 0, 0,
    12, 2, 1, 0, 0,
    3, 0, 5, 60, 0,
    4, 10, 8, 5, 2};
  cout << low_triangular(matrix1, n) << endl;

  int const matrix2[n*n]
  { 1, 3, 6, 2, 7,
    0, 8, 36, 1, 0,
    0, 0, 1, 0, 9,
    0, 0, 0, 60, 4,
    0, 0, 0, 0, 2};
  cout << top_triangular(matrix2, n) << endl;

}
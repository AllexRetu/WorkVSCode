#include <iostream>
using namespace std;

bool all_zero(int * const matrix, int rows, int cols, int row, int col)
{
  for (int i = 0, j = cols*row; i<(rows-row); ++i, j+=cols)
    if (matrix[col+j] != 0)
      return false;
  return true;
}

int gcf(int a, int b)
{
  int t;
  if (a < 0)
    a *= -1;
  else if (a==0)
    return b;
  if (b < 0)
    b *= -1;
  else if (b==0)
    return a;
  while (a != b)
  {
    if(a>b)
    {
      t=a;
      a=b;
      b=t;
    }
    b -= a;
  }
  return a;
}

int gcf_line(int * const matrix, int rows, int cols, int row)
{
  int line = cols*row, gcf_line = gcf(matrix[line], matrix[line+1]);
  for (int i = 1; (i<cols-1)&&(gcf_line!=1); ++i)
    gcf_line = gcf(gcf_line, matrix[line+i+1]);
  return gcf_line;
}

int main()
{
  int rows = 3, cols = 5;
  int matrix[rows*cols]
  {
    4, 1, 5, 0, 3,
    2, 3, -8, 2, 6,
    35, 9, 7, -3, -4
  };
  cout << gcf_line(matrix, rows, cols, 1) << endl;
}
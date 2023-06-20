#include <iostream>

using namespace std;

// Функция печатающая матрицу
void print_matrix(int * const matrix, int rows, int cols)
{
  for (int i = 1; i <= rows*cols; i++)
  {
    cout << matrix[i-1] << '\t';
    if (i%cols==0)
      cout << '\n';
  }
}

// Функция "сдвигающая" строки матрицы начиная с указанной вниз
void displ_rows_matrix(int * const matrix, int row, int rows, int cols) 
{
  int link_last_row = cols*(rows-1);
  int* last_row = new int[cols];
  for (int i = 0; i<cols; i++) // сохраняем последнюю строку
    last_row[i] = matrix[link_last_row+i];
  for (int n = link_last_row; n>row; n-=cols) // заменяем(сдвигаем) строку, которая ниже, на строку которая выше 
    for (int i = 0; i<cols; i++)
      matrix[n+i] = matrix[n-cols+i];
  for (int i = 0; i<cols; i++) // заменяем строку, с которой начался сдвиг на нижнюю
    matrix[row+i] = last_row[i];
}

// Функция, проверяющая начало строк блока матрицы
bool all_zero(int * const matrix, int rows, int cols, int n)
{
  for (int i = 0, j = cols*n; i<(rows-n); ++i, j+=cols)
    if (matrix[n+j] != 0)
      return false;
  return true;
}

// НОД
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

// НОД для всех элементов строки
int gcf_line(int * const matrix, int rows, int cols, int row)
{
  int line = cols*row, gcf_line = gcf(matrix[line], matrix[line+1]);
  for (int i = 1; (i<cols-1)&&(gcf_line!=1); ++i)
    gcf_line = gcf(gcf_line, matrix[line+i+1]);
  return gcf_line;
}

void top_triangular_matrix(int * const matrix, int rows, int cols)
{
  int copy; // переменная, служащая для запоминания первого ненулевого элемента строки
  for (int i = 0, n = 0; i<rows-1; i++, n+=cols) // цикл проходится по всем строкам, кроме последней
  {
    while (all_zero(matrix, rows, cols, i))
      i++;
    while(matrix[n+i] == 0) // смещение строки с нулем в начале строки блока матрицы
      displ_rows_matrix(matrix, n, rows, cols);
    for (int j = 0, m = n+cols; j<rows-i-1; j++, m+=cols) // цикл, который проходится по строкам из которых вычитают
    {
      copy = matrix[m+i];
      for (int k = cols-1; k>i-1; k--) // цикл, проходящийся по элементам строки
      {
        matrix[m+k] *= matrix[n+i];
        matrix[m+k] -= matrix[n+k]*copy;
      }
    }
//    print_matrix(matrix, rows, cols); // печать промежуточных результатов
//    cout << '\n' << "-------------" << endl;
  }
  int gcf;
  for (int i = 0, n = 0; i<rows; ++i, n+=cols) // сокращаем на НОД все строки
  {
    gcf = gcf_line(matrix, rows, cols, i);
    for (int j = 0; (j<cols)&&(gcf!=1); ++j)
      matrix[n+j] /= gcf;
  }
}

int main()
{
  int rows = 5, cols = 5;
  int* matrix = new int[rows*cols]
  {
    8, 4, 1, 12, 3,
    5, 3, 6, 8, -3,
    -2, 4, -7, 2, 11,
    1,-9, -3,-8,-6,
    -5, 6, 7, 1, -1
  };
  print_matrix(matrix, rows, cols);
  cout << "\n-----------------" << endl;
  top_triangular_matrix(matrix, rows, cols);
  print_matrix(matrix, rows, cols);
}
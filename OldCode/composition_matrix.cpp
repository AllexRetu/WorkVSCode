#include <iostream>

using namespace std;

void print_matrix(int const * const matrix, size_t rows, size_t cols)
{
  for (size_t i = 1; i <= rows*cols; i++)
  {
    cout << matrix[i-1] << '\t';
    if (i%cols==0)
      cout << '\n';
  }
}

int main()
{
  size_t col1, row1, col2, row2;
  cin >> col1 >> row1 >> col2 >> row2;

  if (col1 == row2)
  {
    int* matrix1 = new int[row1*col1];
    int* matrix2 = new int[row2*col2];
    
    for (size_t i = 0; i < row1*col1; i++)
      cin >> matrix1[i];
    for (size_t i = 0; i < row2*col2; i++)
      cin >> matrix2[i];

    cout << "Введенные матрицы:" << '\n' << endl;
    print_matrix(matrix1, col1, row1);
    cout << '\n' << "--------------------" << '\n' << endl;
    print_matrix(matrix2, col2, row2);
    cout << '\n' << "Полученное произведение: " << '\n' << endl;

    size_t p = row1*col2;
    int* proizv = new int[p];

    for (size_t i = 0; i < row1*col2; i++)
      proizv[i] = 0;
    for (size_t i = 0, n = 0; i < p; i += col2, n += col1)
      for (size_t l = 0; l < col2; l++)
        for (size_t m = 0, j = 0; j < col1; j++, m += col2)
          proizv[i+l] += matrix1[n+j]*matrix2[m+l];
    print_matrix(proizv, col2, row1);

    delete [] proizv;
    delete [] matrix2;
    delete [] matrix1;
  }
  else
    cout << "Операция не определена." << endl;
}
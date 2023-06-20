
#include "K.HPP"
#include <iostream>
#include <iomanip>  // setw

using namespace std;

// Вспомогательная функция для вывода ошибки.
int test_block_diag_matrix
  (
    bool answer,
    int const matrix[],
    size_t n
  )
{
  if (answer != block_diag_matrix(matrix, n))
  {
    auto const old_precision = clog.precision(); // сохраним, чтобы потом вернуть старое значение.
    clog.precision(6);
    clog << "Answer " << answer << " != " << " the result " << !answer << " for the matrix:\n";
    for (size_t i = 0; i<n; matrix += n, ++i)
    {
      for (size_t j = 0; j != n; ++j)
        clog << setw(10) << matrix[j];
      clog << '\n';
    }

    clog << endl;
    clog.precision(old_precision); // вернём старое значение.
    return 1;
  }

  return 0;
}

// Собственно тест.
int test_block_diag_matrix()
{
  int p[]
  {
    1, 3, -2, 0, 0, 0, 0, 0, 0,
    4, -11,5, 0, 0, 0, 0, 0, 0,
    7, 9, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 6, -9, 8, 0, 0, 0,
    0, 0, 0, -50,3, 11,0, 0, 0,
    0, 0, 0, 4, 34, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 30, 2, 9,
    0, 0, 0, 0, 0, 0, 22, -7,6,
    0, 0, 0, 0, 0, 0, -17,1, 8
  };

  int a[]
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };

  int const c[]
  {
    3, 5, 0, 0, 0, 0,
    1, 4, 0, 0, 0, 0,
    0, 0, 12,8, 0, 0,
    0, 0, 11,4, 0, 0,
    0, 0, 0, 0, 33,2,
    0, 0, 0, 0, 9, 3
  };
  
  int e = test_block_diag_matrix(true, p, 9);

  e += test_block_diag_matrix(true, a, 4);
  e += test_block_diag_matrix(false, c, 6);
  
  a[3] = -2;
  e += test_block_diag_matrix(false, a, 4);
  
  p[76] = 1;
  e += test_block_diag_matrix(false, p, 9);

  return e;
}

int main()
{
  clog << "Testing block_diag_matrix:\n";
  int e = test_block_diag_matrix();
  clog << "Errors: " << e << endl;
  return 0;
}
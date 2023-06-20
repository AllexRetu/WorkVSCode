#include "G.HPP"

#include <iterator>
#include <iostream>
#include <iomanip>  // setw

using namespace std;

/// Тип предиката, принимающего матрицу как упакованный массив
using MatrixPred = 
  bool(
    double const matrix[],
    size_t n
  );


/// Вспомогательная функция-обёртка для вызова версии для массива массивов.
bool sim_matrix_pack_wrapper(
    double const matrix[],
    size_t n
  )
{
  // Создадим временный массив для хранения указателей на строки матрицы.
  auto rmatrix = new double const*[n];
  // Заполним его соответствующими указателями.
  for (size_t i = 0; i < n; ++i, matrix += n)
    rmatrix[i] = matrix;
  // Получим результат обёрнутой функции.
  bool const result = sim_matrix(rmatrix, n);
  // Удалим временный массив.
  delete[] rmatrix;
  // И вернём полученный ранее результат.
  return result;
}

/// Вспомогательная функция для вывода матрицы (упакованной в массив) в консоль.
void log_matrix(
    double const matrix[],
    size_t n
  )
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
      clog << setw(4) << matrix[j+i*n];
    clog << '\n';
  }
}

/// Вспомогательная функция для вывода сообщения в случае непрохождения теста.
int test_is_01_matrix(
    MatrixPred * is01,
    double const * matrix,
    size_t n,
    bool answer
  )
{
  if (bool result = is01(matrix, n); result != answer)
  {
    clog << "\nthis matrix is not symmetric\n" << endl;
    log_matrix(matrix, n);
    clog << "\nGot " << result << " != " << answer;
    clog << endl;
    return 1;
  }

  return 0;
}

/// Собственно, набор тестов, проверяющих функцию is01.
int test_is_01_matrix(MatrixPred * is01)
{
  double m[]
  {
    0.,   30.,   1.,  12.3,
    30.,   5.,   0.3, 11.5,
    1.,  0.3,  -0.1,   48.,
    12.3, 11.5, 48., 6.1
  };

  int errors =
      test_is_01_matrix(is01, m, 4, true);


  m[4] = 1.5;
  errors += test_is_01_matrix(is01, m, 4, false);

  m[4] = 30.0;
  m[15] = 1.12;
  errors += test_is_01_matrix(is01, m, 4, true);

  return errors;
}

int main()
{
  MatrixPred * func[] { sim_matrix, sim_matrix_pack_wrapper };
  char const * name[] { "sim_matrix packed", "sim_matrix array of arrays" };
  static_assert(size(func) == size(name));
  for (size_t i = 0; i < size(func); ++i)
  {
    clog << name[i] << ":\n";
    int errors = test_is_01_matrix(func[i]);
    clog << "\nErrors: " << errors << '\n' << endl;
  }

  return 0;
}

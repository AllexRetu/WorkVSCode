#pragma once
#ifndef G_HPP_INCLUDED
#define G_HPP_INCLUDED
#include <cstddef>


// Функция принимающая массив массивов и определяющая,
// является ли матрица заданная этим масивом симметричной!
inline bool sim_matrix(const double * const * matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++)
        if (matrix[i][j] != matrix[j][i])
          return false;
    return true;
}


// Функция принимающая упакованный массиви и определяющая,
// является ли матрица заданная этим массивом симметричной!
inline bool sim_matrix(const double * matrix, size_t n)
{
  for (size_t row = 0, sim_col = 0; sim_col < n; row+=n, sim_col++)
    for (size_t col = 0, sim_row = 0; col < n; col++, sim_row+=n)
      if (matrix[row+col] != matrix[sim_row+sim_col])
        return false;
  return true;
}

#endif
#pragma once
#ifndef K_HPP_INCLUDED
#define K_HPP_INCLUDED

#include <cstddef>
#include <iostream>

inline bool block_diag_matrix(int const * const matrix, size_t n)
{
  size_t size_block = 0;
  for (size_t i = 0; i<n; i++) // Находим размер блока
    if (matrix[i] == 0)
    {
      size_block = i;
      break;
    }
  if (size_block%2 == 0)
    return false;
  else
  {
    for (size_t i = 0, m = 0, l = 0, k = size_block-1; i<n; i++, m+=n)
    {
      for (size_t j = 0; j<n; j++)
        if ((matrix[m+j] != 0) && !(l<=j && k>=j)) // Возвращаем false, если только
          return false;                            // не нуль встретился вне промежутка
      if ((i+1)%size_block == 0) // Изменяем промежуток с блоком
      {
        l+=size_block;
        k+=size_block;
      }
    }
    return true;
  }
}

#endif
#pragma once
#ifndef H_HPP_INCLUDED
#define H_HPP_INCLUDED

#include <cstddef>
#include <cassert>
#include <math.h>

inline std::size_t count_lines(char const * const * text)
{
  // Предусловия.
  assert(text != nullptr);
  // Код.
  std::size_t lines = 0;
  while (*text++ != nullptr)
    ++lines;
  return lines;
}

inline size_t size_str(char const* str)
{
  size_t q = 0;
  while (*str != '\0')
  {
    str++;
    q++;
  }
  return q;
}

inline int string_to_int(char const* str)
{
  char raz;
  int s = 0;
  size_t SIZE = size_str(str);
  size_t st = pow(10, SIZE-1);
  for (; *str != '\0'; str++)
  {
    raz = *str;
    s += (int(raz) - 48)*st;
    st /= 10;
  }
  return s;
}

inline int max_int(char const * const * integers)
{
  int max = string_to_int(*integers);
  for (std::size_t i = 1; i < count_lines(integers); i++)
    if (string_to_int(*(integers + i)) > max)
      max = string_to_int(*(integers + i));
/*  size_t line;
  for (std::size_t i = 0; i < count_lines(integers); i++)
    if (max == int(**(integers + i)))
      line = i + 1;
  return line;*/
  return max;
}

#endif
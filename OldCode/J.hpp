#pragma once
#ifndef J_HPP_INCLUDED
#define J_HPP_INCLUDED
#include <cstddef>
#include <cmath>

struct lomanaya
{
  size_t size;
  double llong;
};

bool is_almost_zero(double x)
{
  return fabs(x) <= 1e-10;
}

inline bool operator==(lomanaya const & lom1, lomanaya const & lom2)
{
  return lom1.size==lom2.size && is_almost_zero(lom1.llong - lom2.llong);
}

inline bool operator!=(lomanaya const & lom1, lomanaya const & lom2)
{
  return !(lom1==lom2);
}

inline lomanaya search_max_size(double const * const X, double const * const Y, size_t n)
{
  size_t max_size = 0, size = 0, tail;

  for(size_t i = 0; i < n; i++)
  {
    if (X[i]*X[i]+Y[i]*Y[i] < 1)
      size++;
    else
    {
      if (size > max_size)
      {
        max_size = size;
        tail = i - 1;
      }
      size = 0;
    }
  }
  if (max_size < size)
  {
    max_size = size;
    tail = n-1;
  }

  double LLONG = 0;

  for(size_t i = 0; i < max_size - 1; i++)
    LLONG += sqrt(pow(X[tail - i] - X[tail - i - 1], 2) 
    + pow(Y[tail - i] - Y[tail - i - 1], 2));
  return { max_size, LLONG};
}

#endif
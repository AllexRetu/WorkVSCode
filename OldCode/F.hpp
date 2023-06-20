#ifndef F_HPP
#define F_HPP
#include <cstddef>
#include <istream>

inline size_t longup(int const nums[], size_t count)
{
  if (count < 2)
    return 0;
  size_t longa = 0, longend = 0;
  for (size_t i = 0; i + 1<count; i++){
    if (nums[i] < nums[i+1])
      longa++;
    else if (longa != 0)
    {
      longend = longa;
      longa = 0;
    }
  }
  if (longa != 0 && longend != longa)
    longend = longa;
  return longend;
} 

inline size_t longup(std::istream & in)
{
  size_t longa = 0, longend = 0;
  if(int first; in >> first)
    for (int second; in >> second; first = second)
    {
      if (first < second)
        longa++;
      else if (longa != 0)
      {
        longend = longa;
        longa = 0;
      }
    }
  if (longa != 0 && longend != longa)
    longend = longa;
  return longend;
}

#endif
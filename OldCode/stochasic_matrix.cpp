#include <cmath>
#include <cstddef>
#include <iostream>
using namespace std;

// Check if array elements belong [0, 1].
bool all_elements_within_01(float const * a, size_t n)
{
  for (size_t i = 0; i < n; ++i)
    if (auto const e = a[i]; e < 0.f || e > 1.f)
      return false;
  return true;
}

// Compute array sum.
float sum(float const * a, size_t n)
{
  float s = 0;
  for (size_t i = 0; i < n; ++i)
    s += a[i];
  return s;
}

// Packed 2D array.
bool is_right_stochastic
  (
    float const * matrix,
    size_t rows,
    size_t cols,
    float tol = 1e-6f
  )
{
  for (; rows--; matrix += cols)
  {
    if (!all_elements_within_01(matrix, cols)
      || fabs(sum(matrix, cols) - 1.f) > tol)
      return false;
  }
  return true;
}

// Test.
int test_is_right_stochastic()
{
  float sm[4][10] {};
  
  if (is_right_stochastic(&sm[0][0], 4, 10))
    return 1;
  sm[0][0] = 1.f;
  if (is_right_stochastic(&sm[0][0], 4, 10))
    return 2;
  if (!is_right_stochastic(&sm[0][0], 1, 10))
    return 3;
  
  for (int i = 0; i < 10; ++i)
    sm[0][i] = 0.1f;
  if (!is_right_stochastic(&sm[0][0], 1, 10))
    return 4;
  // A better summation algorithm may make this check invalid:
  if (is_right_stochastic(&sm[0][0], 1, 10, 0.f))
    return 5;
  
  for (int i = 1; i < 4; ++i)
    sm[i][6 + i] = 1.f;
  if (!is_right_stochastic(&sm[0][0], 4, 10))
    return 6;
  sm[0][9] = -0.1f;
  sm[0][0] = 0.3f;
  if (is_right_stochastic(&sm[0][0], 4, 10))
    return 7;
  sm[0][9] = sm[0][8] = 0.f;
  sm[3][9] = 1.1f;
  if (!is_right_stochastic(&sm[0][0], 3, 10))
    return 8;
  if (is_right_stochastic(&sm[0][0], 4, 10))
    return 9;
  return 0;
}

int main()
{
  cout << test_is_right_stochastic();
}

#include "J.hpp"

#include <iterator>
#include <iostream>
#include <iomanip>

using namespace std;

// Функция печатающая массив
ostream & print_arr(ostream & os, double const * arr, size_t n)
{
  os << "{ ";
  for (size_t i = 0; i < n; i++)
  {
    if (i != 0)
      os << ", ";
    os << arr[i];
  }
  os << " }";
  return os;
}

ostream & operator<<(ostream & os, lomanaya const & lom)
{
  return os << "{ size: " << lom.size 
            << "; long: "  << lom.llong 
            << " }";
}

int test_largest_max_size(
    double const * a,
    double const * b,
    size_t n,
    lomanaya const & answer)
{
  if (auto result = search_max_size(a, b, n); result != answer)
  {
    clog << "For arrays:\n";
    print_arr(clog, a, n);
    clog << '\n';
    print_arr(clog, b, n);
    clog << '\n';
    clog << "Got: " << result << " != " << answer << endl;
    return 1;
  }
}

int test_largest_max_size()
{
  double X[]
  {0.3 , 0.1 , 0.02 , 1.0 , 4.1 , -0.6 , 0.2 , -0.7 , 0.01};
  double Y[]
  {-0.2 , 4.1 , -0.5 , -0.9 , 0.3 , 12.6 , 0 , 0.1 , -0.02};

  size_t n =9;

  int e = test_largest_max_size(X, Y, n, lomanaya { 3, sqrt(0.82)+sqrt(0.5185) });
  Y[6] = 1;
  e += test_largest_max_size(X, Y, n, lomanaya { 2, sqrt(0.5185) });
  Y[1] = 0.6;
  X[3] = 0;
  e += test_largest_max_size(X, Y, n, lomanaya { 4, sqrt(0.68)+sqrt(1.2164)+sqrt(0.1604) });
  X[0] = 30;
  e += test_largest_max_size(X, Y, n, lomanaya { 3, sqrt(1.2164)+sqrt(0.1604) });
  return e;
}

int main()
{
  clog << setprecision(20);
  clog << "Testing largest_max_size:\n";
  int e = test_largest_max_size();
  clog << "Errors: " << e << endl;
  return 0;
}
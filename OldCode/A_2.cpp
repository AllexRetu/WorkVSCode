#include <iostream>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
vector<T> max_dif(size_t k, vector<T> const & a)
{
  k = min(k+1, size(a)) - 1;

  size_t size_b = size(a) - k;
  /*if(size(a) < k+1)
  { size_b = 1;
    k = size(a)-1; }
  else 
    size_b = size(a)-k;*/
  vector<T> b(size_b);

  for (size_t i = 0; i < size_b; ++i)
  {
    T max_value = a[i], min_value = a[i];

    for (size_t j = 1; j < k+1; ++j)
    {
      if(max_value < a[i+j])
        max_value = a[i+j];
      else if(a[i+j] < min_value)
        min_value = a[i+j];
    }
    b[i] = max_value - min_value;
  }

  return b;
}

template <typename T>
void print_vector(vector<T> const & vector, ostream & out)
{
  out << setw(1) << "\n{ ";
  for(auto const & x: vector)
    out << x << ",  ";
  out << "}" << endl;
}

template <typename T>
size_t test_once_max_dif(vector<T> const & a, vector<T> const & ans, ostream & out, size_t k)
{
  vector<T> res = max_dif(k, a);

  if(size(res) != size(ans))
  {
    out << "For group: ";
    print_vector(a, out);
    out << "size of result: ";
    print_vector(res, out);
    out << "does not match the size of the answer: ";
    print_vector(ans, out);
    return 1;
  }

  for(size_t i = 0; i < size(ans); ++i)
    if(res[i] != ans[i])
    {
      out << "For group: ";
      print_vector(a, out);
      out << "with k = " << k << endl;
      out << res[i] << " != " << ans[i] << " in position " << i+1 << endl;
      return 1;
    }

  return 0;
}

size_t test_max_dif()
{
  vector<vector<int>> as
  {
    {1, 3, 4, 8, -2, 9, 13, 0, },
    {15, 30, 0, 5, -2, 6, 1, 5, },
    {3, 8, -3, 21, 94, 94, 94, 94, },
    {-1, -1, -1, -1, 5, 0, 20, 6, },
    {13, 0, 2, 14, 7, -8, 11, 9, },
  },
  answers
  {
    {7, 10, 11, 15, 15, }, {11, 15, 15, }, {15, },
    {30, 32, 8, 8, 8, }, {32, 32, 8, }, {32, },
    {24, 97, 97, 73, 0, }, {97, 97, 97, }, {97, },
    {0, 6, 6, 21, 20, }, {6, 21, 21, }, {21, },
    {14, 14, 22, 22, 19, }, {22, 22, 22, }, {22, },
  };

  size_t errors = 0;

  size_t ks[3] {3, 5, 10};

  for(size_t i = 0; i < size(answers); ++i)
    errors += test_once_max_dif(as[i/3], answers[i], clog, ks[i%3]);
  clog << "Errors: ";
  return errors;
}

int main()
{
  clog << test_max_dif() << endl;
}
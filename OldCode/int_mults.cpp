// int_mults.cpp
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>

/// Итератор, реализующий представление промежутков ряда целых чисел.
template <typename Int = int>
class Int_iterator
{
  Int _val;

public:
  using value_type = Int;
  using reference = value_type const&;
  using pointer = value_type const*;
  using difference_type = Int;
  using iterator_category = std::random_access_iterator_tag;

  explicit Int_iterator(Int val = 0)
    : _val(val) {}

  reference operator*() const { return _val; }
  pointer operator->() const { return &_val; }

  Int_iterator& operator++() // prefix
  {
    ++_val;
    return *this;
  }

  Int_iterator operator++(int) // postfix
  {
    auto old = *this;
    ++(*this);
    return old;
  }

  Int_iterator& operator--() // prefix
  {
    --_val;
    return *this;
  }

  Int_iterator operator--(int) // postfix
  {
    auto old = *this;
    --(*this);
    return old;
  }

  Int_iterator& operator+=(difference_type delta)
  {
    _val += delta;
    return *this;
  }

  Int_iterator& operator-=(difference_type delta)
  {
    _val -= delta;
    return *this;
  }

  Int_iterator operator-(difference_type delta) const
  {
    return { _val - delta };
  }

  difference_type operator-(Int_iterator rhs) const
  {
    return _val - rhs._val;
  }
};

template <typename Int>
bool operator==(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a == *b;
}

template <typename Int>
bool operator!=(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a != *b;
}

template <typename Int>
bool operator<(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a < *b;
}

template <typename Int>
bool operator<=(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a <= *b;
}

template <typename Int>
bool operator>(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a > *b;
}

template <typename Int>
bool operator>=(Int_iterator<Int> a, Int_iterator<Int> b)
{
  return *a >= *b;
}

template <typename Int>
Int_iterator<Int> operator+(Int_iterator<Int> a, Int delta)
{
  return a += delta;
}

template <typename Int>
Int_iterator<Int> operator+(Int delta, Int_iterator<Int> a)
{
  return a + delta;
}


/// Вывод последовательности n, n+1, n+2, ..., m в последовательность по итератору out.
template <typename Int, typename OutIt>
OutIt count_up(Int n, Int m, OutIt out)
{
  Int_iterator<Int> const from{n}, to{m + 1};
  return std::copy(from, to, out);
}

/// Вывод последовательности квадратов натуральных чисел от 1 до n
/// в последовательность по итератору out.
template <typename Int, typename OutIt>
OutIt squares(Int n, OutIt out)
{
  Int_iterator<Int> const from{1}, to{n + 1};
  return std::transform(from, to, from, 
    out, std::multiplies<>{});
}


/// Вывод 1!, 2!, ..., n! в последовательность по итератору out.
template <typename Int, typename OutIt>
OutIt factorials(Int n, OutIt out)
{
  Int_iterator<Int> const from{1}, to{n + 1};
  return std::partial_sum(from, to,
    out, std::multiplies<>{});
}


/// Сумма квадратов натуральных чисел от 1 до n.
template <typename Int>
Int squares_sum(Int n)
{
  Int_iterator<Int> const from{1}, to{n + 1};
  return std::inner_product(from, to, from, Int{0});
}


/// Записать произведения a*1, a*2, ..., a*n в последовательность по итератору out.
template <class Int, class OutIt>
OutIt mult_seq(Int a, Int n, OutIt out)
{
  Int_iterator<Int> const from{1}, to{n + 1};
  return std::transform( from, to,
    out, [a](Int b) { return a * b; });
    // std::bind(std::multiplies<>{}, a, std::placeholders::_1)
}

/// Применить mult_seq для a=1, ..., n, записывая результаты 
/// в последовательность контейнеров по итератору out.
template <class Int, class OutIt>
OutIt mult_table(Int n, OutIt out)
{
  Int_iterator<Int> const from{1}, to{n + 1};
  std::for_each(from, to,
    [n, &out](Int a)
      {
        mult_seq(a, n, std::back_inserter(*out++));
      });
  return out;
}


///// Проверить, делится ли m на n.
//template <class Int>
//class Is_divisible
//{
//  Int m;
//
//public:
//  explicit Is_divisible(Int m)
//    : m(m) {}
//
//  bool operator()(Int n) const
//  {
//    return m % n == 0;
//  }
//};
//
//template <class Int>
//Is_divisible<Int> is_divisible(Int m)
//{
//  return Is_divisible<Int>(m);
//}

/// Вместо закомментированного кода, вариант C++14:
template <class Int>
auto is_divisible(Int m)
{
  return [m](Int n) { return m % n == 0; };
}


/// Вывести только те числа из 2, ..., n, на которые делится m.
template <class Int, class OutIt>
OutIt divisors(Int n, Int m, OutIt out)
{
  Int_iterator<Int> const from{2}, to{n + 1};
  return std::copy_if(from, to, out, is_divisible(m));
}


/// Проверить (перебором делителей) простоту числа n.
struct Is_prime
{
  template <typename Int>
  bool operator()(Int n) const
  {
    Int_iterator<Int> const from{2}, to{n/2 + 1};
    return std::none_of(from, to, is_divisible(n));
  }
} const is_prime;


/// Вывести простые числа из диапазона 2, ..., n.
template <class Int, class OutIt>
OutIt primes(Int n, OutIt out)
{
  Int_iterator<Int> const from{2}, to{n + 1};
  return std::copy_if(from, to, out, is_prime);
}


#include <iostream>
#include <vector>

int main()
{
  using namespace std;
  ostream_iterator<int> c_out(cout, "\t");
  count_up(3, 10, c_out);
  cout << '\n';

  squares(10, c_out);
  cout << '\n';

  factorials(10, c_out);
  cout << '\n';

  mult_seq(2, 10, c_out);
  cout << '\n';

  cout << squares_sum(2) << ' ' << squares_sum(10) << "\n\n";

  vector<vector<int>> table(9);
  mult_table(9, begin(table));
  for (auto &row : table)
  {
    copy(begin(row), end(row), c_out);
    cout << '\n';
  }

  cout << '\n';
  divisors(100, 100, c_out);
  cout << '\n';

  cout << '\n';
  primes(1000, c_out);
  cout << '\n';

  return 0;
}

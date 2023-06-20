#include <iostream>
using namespace std;

bool * find_false(bool * from, bool * to)
{
  while (from != to && *from)
    ++from;
  return from;
}

void fill(bool * from, bool * to, size_t stride)
{
  while ((from += stride) < to)
    *from = true;
}

void eratosphenes(bool sieve[], size_t n)
{
  if (n < 3)
    return;

  auto const end = sieve + n;
  for (auto p = sieve + 2;; ++p)
  {
    p = find_false(p, end);
    if (p == end)
      break;
    size_t const stride = p - sieve;
    if (n <= stride + stride)
      break;
    fill(p, end, stride);
  }
}

int main()
{
  if (size_t n; cin >> n)
  {
    auto sieve = new bool[n]{};
    eratosphenes(sieve, n);
    for (size_t i = 2; i < n; ++i)
      if (!sieve[i])
        cout << i << '\n';
  }
}

#include <iostream>
#include <cmath>

using namespace std;

void print_table_value_func(double const a, double const b, double const d, double (*f)(double))
{
  for (double arg = a; arg<b+d/10; arg+=d)
    cout << arg << '\t' << f(arg) << endl;
}

int main()
{
  print_table_value_func(1, 2, 0.1, sin);
}
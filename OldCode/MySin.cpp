#include <iostream>
#include <cmath>
#include <iomanip>

double MySin(double x)
{
  double y = x, term = x;
  for (int i = 1; i < 20; ++i)
  {
    term *= -x*x/(2*i*(2*i+1));
    y += term;
  }
  return y;
}

int main()
{
  std::cout << std::setprecision(20) << std::endl;
  std::cout << sin(0.5) << std::endl;
  std::cout << MySin(0.5) << std::endl;
}
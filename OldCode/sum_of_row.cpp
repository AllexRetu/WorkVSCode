#include <iostream>
#include <cmath>

using namespace std;

double sum(int n)
{
  double s = 0;
  int a = 4 * pow(n, 4);
  for(int i = 1; i <= n; ++i)
    s += i/sqrt(pow(i, 4) + a);
  return s;
}

int main()
{
  int n;
  cin >> n;
  cout << sum(n) << endl;
  cout << 0.5 * log(1 + sqrt(2)) << endl;
}
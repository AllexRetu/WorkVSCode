#include "J.hpp"

#include <iterator>
#include <iostream>

using namespace std;

int main()
{
  double X[]
  {0.3 , -3.2 , 0.02 , 1.0 , 4.1 , -0.6 , 0.2 , -0.7 , 0.01};
  double Y[]
  {-0.2 , 4.1 , 2.0 , -0.9 , 0.3 , 12.6 , 0 , 0.1 , -0.02};

  lomanaya now;
  now = search_max_size(X, Y, 9);
  cout << now.size << '\t' << now.llong << endl;
}
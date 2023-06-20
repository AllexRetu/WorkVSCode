#include <iostream>
#include <vector>

using namespace std;

void f(vector<int> & vec)
{
  int a = 5;
  vec.push_back(a);
}

int main()
{
  vector<int> vec = {4, 9};
  f(vec);
  for(auto const & x: vec)
    cout << x << '\t';
}

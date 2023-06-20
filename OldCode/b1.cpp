#include <iostream>     
#include <numeric>
#include <vector>
     
using namespace std;
template <typename ItIn, typename ItOut>
ItOut pair_xor(ItIn from, ItIn to, ItOut out)
{
  return adjacent_difference (from, to, out,
      [](auto & a, auto & b){  return a^b;  });
}

int main ()
{
  vector<int> Input {0, 9, 0, 5, 0, 20098, 111};
  vector<int> Output(7);
  pair_xor(begin(Input), end(Input), begin(Output));

  for(auto & x: Output)
    cout << x << endl;
  return 0;
}
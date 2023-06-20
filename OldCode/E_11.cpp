#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename SubType, typename SupType, typename Comp = less<>>
bool is_subset(SupType abegin, SupType aend, SubType bbegin, SubType bend, Comp comp = Comp{})
{
  sort(bbegin, bend, comp);
  return includes(abegin, aend, bbegin, bend);
}

template <typename SubType, typename SupType, typename Comp = less<>>
size_t test(bool answ, SupType abegin, SupType aend, SubType bbegin, SubType bend, Comp comp = Comp{})
{
  if(is_subset(abegin, aend, bbegin, bend, comp) != answ)
    return 1;
  return 0;
}

int main()
{
  vector<vector<int>> subs
  {
    { 3, -95, 15, 0, -1, 7, 61, 50, -4, },
    { 0, -99, 50, 6, 8, 3, },
    { 73, 5, -1, 5, 12, 8, 5, 3, },
    { -20, -1, 5, 1, 66, 15},
    { },
    { 3, 6, -14},
  },
  sups
  {
    { -95, -4, -1, 0, 2, 3, 6, 7, 9, 15, 19, 31, 50, 61, 75, 396, },
    { -555, -99, -82, -50, 0, 3, 6, 8, 13, 39, 50, 391, 569, },
    { -1, 3, 5, 8, 12, 73, 91, },
    { -63, -2, 5, 63, 153, 999, 3000, 3901, 6432, },
    { 5, },
    { },
  };

  vector<bool> answs{ true, true, false, false, true, false, };

  size_t errors = 0;
  for(size_t i = 0; i < subs.size(); ++i)
    errors += test(answs[i], sups[i].begin(), sups[i].end(), subs[i].begin(), subs[i].end());

  cout << "Errors: " << errors << endl;
}
#include <vector>
#include <string>
#include <iostream>

using namespace std;

size_t search_in_pref(char a, string const & str, vector<string> const & text)
{
  for(size_t i = 0; i < text.size(); ++i)
  {
    size_t pos = text[i].rfind(a);
    if(pos == string::npos)
      continue;
    if(text[i].rfind(str, pos) != string::npos)
      return i;
  }
  return string::npos;
}

bool test(char a, string const & str, vector<string> const & text, size_t answ)
{
  if(search_in_pref(a, str, text) != answ)
    return true;
  return false;
}

int main()
{
  vector<vector<string>> texts
  {
    {
      "ergj,l,nroienoijeroij", // 0
      "itgneoij",           // 1
      "etgnri",             // 2
      "pokrgeommqqqqqq",    // 3
      "23rp234230l,el,",    // 4
      "|w,e;,rwr3",         // 5
      ";l,l,|ergl,re",      // 6
    },
    {
      "eprgmepork",         // 0
      "&lekrmw",            // 1
      "8&ekrgee",           // 2
      "&&&&&&&&8",          // 3
      "6790lf[pwl",         // 4
    },
    {
      "-om31p1",            // 0
      "+790832,2-plf",      // 1
      "bsgere-",            // 2
      "1234567890",         // 3
      ";el,g;elr,g;e,rg,[,e",// 4
    },
    {},
  };

  char as[4] = {'|', '&', '-', '1'};
  vector<string> strs{  ",l,", "8", "+7901", "012f"};
  size_t answs[4] = {6, 2, string::npos, string::npos};

  int errors = 0;
  for(size_t i = 0; i < 3; ++i)
    if(test(as[i], strs[i], texts[i], answs[i]))
      ++errors;

  cout << "Errors: " << errors << endl;
}
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <iterator>
using namespace std;

size_t NPOS = string::npos;

size_t search_in_suf(char const & symbol, string const & sought, vector<string> const & text)
{
  for(size_t i = 0; i < size(text); ++i)
  {
    size_t symbol_position = (text[i]).find(symbol);
    if((symbol_position != NPOS) && (text[i]).find(sought, symbol_position) != NPOS)
      return i;
  }

  return NPOS;
}

size_t test_once_search_in_suf(char const & symbol, string const & sought, 
                                vector<string> const & text, size_t answer, size_t text_index)
{
  size_t ver = search_in_suf(symbol, sought, text);

  if(ver == answer)
    return 0;
  if(answer == NPOS)
    clog << "In text number " << text_index + 1 << " not found substring \""
         << sought << "\" after symbol \"" << symbol << "\"" << endl;
  else
    clog << "Substring \"" << sought << "\" is in the string number " << answer << endl;
  
  return 1;
}

size_t test_search_in_suf()
{
  vector<string> Black_Sabbath
  { "Voodoo | Ronnie Dio",
    "Paranoid | John Osbourne",
    "Iron man | Tony Iommi",
    "NIB | Geezer Butler", },
  Led_Zeppelin
  { "Stairway to Heaven | Robert Plant",
    "Immigrant song | Jimmy Page",
    "Whole Lotta Love | John Bonham",
    "Good Times Bad Times | John Jones", },
  Judas_Priest
  { "Braeking the Law | Robert Halford",
    "Night Crawler | Ian Hill",
    "Necromancer | Glenn Tipton",
    "No Surrender | Scott Travis", },
  Ozzy_Osbourne
  { "I don\'t know | Ozzy Osbourne",
    "Crazy Train | Randy Rhoads",
    "Mr.Crowley | John Daisley",
    "The Ultimate Sin | Lee Kerslake", };

  vector<vector<string>> Text {Black_Sabbath, Led_Zeppelin, Judas_Priest, Ozzy_Osbourne, };
  size_t errors = 0;
  vector<string> sought 
  { "omm", "| Ji", "1234", "Train"};

  size_t answers[4] {2, NPOS, NPOS, 1, };
  char symbols[4] {'|', 'y', ' ', 'r', };

  for(size_t i = 0; i < size(Text); ++i)
    errors += test_once_search_in_suf(symbols[i], sought[i], Text[i], answers[i], i);
  clog << "Errors: ";

  return errors;
}

int main()
{
  clog << test_search_in_suf() << endl;
}
#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

class Vocabulary
{
  map<string, string> content;

  public:

  template< typename It = string::iterator>
  Vocabulary(It from1, It to1, It from2, It to2)
  {
    if(to1 - from1 != to2 - from2)
      cout << "На вход были поданы разные по размеру последовательности" << endl;
    else
    {
        while (from1 != to1)
        {
          content.insert(pair(*from1, *from2));
          ++from1;
          ++from2;
        }
    }
  }

  void addition(string rus,  string eng)
  {
    content.insert(pair(eng, rus));
  }

  string take(string word)
  {
    if(content.find(word) != content.end())
      return (*(content.find(word))).second;
    else
    {
      auto it = find_if(content.begin(), content.end(), [&](auto & a){ return a.second == word;});
      if(it != content.end())
        return (*it).first;
    }
    return {};
  }

  void deletion(string word)
  {
    if(content.find(word) != content.end())
      content.erase(word);
    else
    {
      auto it = find_if(content.begin(), content.end(), [&](auto & a){ return a.second == word;});
      if(it != content.end())
        content.erase(it);
    }
  }

  void change(string was, string replace1, string replace2)
  {
    if(content.find(was) != content.end())
    {
      content.erase(content.find(was));
      content.insert(pair(replace1, replace2));
    }
    else
    {
      auto it = find_if(content.begin(), content.end(), [&](auto & a){ return a.second == was;});
      if(it != content.end())
      {
        content.erase(it);
        content.insert(pair(replace1, replace2));
      }
    }
  }
};

int main()
{
  ifstream fin("Rus_Words.txt");
  vector<string> russ;
  string s;
  while( !fin.eof() )
  {
    fin >> s;
    russ.push_back(s);
  }
  fin.close();
  fin.open("Eng_Words.txt");
  vector<string> engs;
  while( !fin.eof() )
  {
    fin >> s;
    engs.push_back(s);
  }
  fin.close();
  if( russ.size() != engs.size() )
  {
    russ.resize(min(russ.size(), engs.size()));
    engs.resize(russ.size());
  }
  Vocabulary MyVoc(russ.begin(), russ.end(), engs.begin(), engs.end());
  cout << MyVoc.take("Bad") << endl;
  MyVoc.deletion("Хорошо");
  MyVoc.change("Плохо", "Плохой", "Bad");
  cout << MyVoc.take("Плохой") << endl;
  MyVoc.addition("Что-то", "Something");
  cout << MyVoc.take("Something");
}
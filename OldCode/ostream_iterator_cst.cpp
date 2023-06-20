// Custom type to specify ostream_iterator behavior.
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <iomanip>
#include <algorithm>
using namespace std;

class By_line
{
  string _data;

public:
  operator string() const { return _data; }
  operator string_view() const { return _data; }

  friend istream& operator>>(istream & is, By_line & line)
  {
    return getline(is, line._data);
  }
};

using By_line_iterator = istream_iterator<By_line>;

class Quoted_output
{
  string_view _view;

public:
  Quoted_output() = default;
  Quoted_output(string const & s) : _view(s) {}
  Quoted_output(string_view sv)   : _view(sv) {}
  Quoted_output(By_line const & bl)
    : _view(string_view{bl}) {}

  friend ostream& operator<<(ostream & os, Quoted_output const & what)
  {
    return os << quoted(what._view);
  }
};

using Quoted_output_iterator = ostream_iterator<Quoted_output>;

int main()
{
  copy(By_line_iterator{cin}, By_line_iterator{},
       Quoted_output_iterator(cout, "\n"));
}

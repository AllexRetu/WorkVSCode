#include <iostream>
#include <vector>

std::string subst(std::string const & text, std::vector<std::string> const & subs)
{
  size_t pos1 = text.find('%');
  std::string result = text.substr(0, pos1);
  
  for(size_t pos2 = text.find_first_of('%', pos1 + 1); pos1 != std::string::npos && pos2 != std::string::npos;
    pos1 = text.find_first_of('%', pos2 + 1), result += text.substr(pos2 + 1, pos1 - pos2 - 1),
    pos2 = text.find_first_of('%', pos1 + 1))
  {
    if( pos2 - pos1 < 2 )
      result += '%';
    else
    {
      std::string replace = text.substr(pos1 + 1, pos2 - pos1 - 1);
      result += subs[stoi(replace)];
    }
  }

  if( pos1 != std::string::npos )
    result += text.substr(pos1);

  return result;
} 

int main()
{
  std::string a = "There are %2% %3% in %0% %1% of %5% with %4%%% acidity.";
  std::vector<std::string> s = {"tank", "B", "250", "litres", "1.5", "water" };

  std::cout << subst(a, s) << std::endl;
}
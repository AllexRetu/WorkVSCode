#include <vector>
#include <string>
#include <iostream>

using namespace std;

size_t number_of_entry(string const & a, string const & b)
{
  size_t count = 0;
  for(size_t i = 0, pos; (pos = a.find(b, i)) != string::npos; ++count)
    i = pos + b.size();
  return count;
}

pair<size_t, size_t> max_number_of_entry(vector<string> const & superset, vector<string> const & subset)
{
  if(subset.empty() || superset.empty())
    return {};
    
  size_t max_quan = 0;
  size_t quans[subset.size()];

  for(size_t i = 0; i < subset.size(); ++i)
  {
    size_t quan = 0;
    for(auto text: superset)
      quan += number_of_entry(text, subset[i]);
    if(max_quan < quan)
      max_quan = quan;
    quans[i] = quan;
  }

  for(size_t i = 0; i < subset.size(); ++i)
    if(quans[i] == max_quan)
      return {i, max_quan};

  return {};
}

bool test(vector<string> const & superset, vector<string> const & subset, pair<size_t, size_t> const & answ)
{
  if(max_number_of_entry(superset, subset) != answ)
    return 1;
  return 0;
}

int main()
{
  vector<vector<string>> supersets
  {
    {
      "in physics, energy is the quantitative property that must be transferred to an object in order to perform work on, or to heat, the object",
      "energy is a conserved quantity; the law of conservation of energy states that energy can be converted in form, but not created or destroyed",
      "the SI unit of energy is the joule, which is the energy transferred to an object by the work of moving it a distance of 1 metre against a force of 1 newton",
    },
    {
      "the more of you that I inspect the more of me I see reflect the more I try to read your lipst the more the mask you're wearing rips",
      "but when I seek out your voice my ears are overcome with noise you show and tell with greatest ease raving impossibilities",
      "engaged in crime I grasp my throat enraged my mind starts to smoke enforce a mental overload angry again, angry again, angry ow",
    },
    {
      "thirteen times I went to the well to draw my thoughts, I’ll gather and tell like bricks that I’ve laid to build my life those that crumbled only caused me strife",
      "thoughts became words, cast into the sea but they returned, always haunting me like a severed arm washed up on the shore i just don’t think I can give anymore",
      "because I’ve lived, how many times do I have to die? because I’ve lived, how many lives do I have to die?",
    },
    {
      "l,ger,",
      "3409r",
      "mwefm wple,fwe mwelfm",
      "ww",
      "",
    },
    {   },
  };
  vector<string> subset
  {
    "in",
    "is",
    "the",
    "energy",
  };
  vector<pair<size_t, size_t>> answs
  {
    {2, 7},
    {0, 7},
    {2, 5},
    {0, 0},
    {},
  };
  size_t errors = 0;
  for(size_t i = 0; i < supersets.size(); ++i)
    errors += test(supersets[i], subset, answs[i]);
  cout << "Errors: " << errors << endl;
}
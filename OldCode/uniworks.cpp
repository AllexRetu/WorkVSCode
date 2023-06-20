// uniworks.cpp
// Unicode C++ example.
// Uses UTF8-CPP to transcode UTF-8 <-> UTF-32 
// (although it may be done manually or through deprecated and possibly poorly supported standard locale functionality).
#include <iterator>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <numeric>

#include "utf8/utf8.h"  // https://github.com/nemtrif/utfcpp

/// Aux function: read a file into a string.
inline std::string read_all(std::istream & in)
{
  // This method is simple, clear and portable, but actual C++ 
  // std library implementation may be quite slow here (not optimized).
  std::istreambuf_iterator<char> from(in.rdbuf()), to;
  return std::string(from, to);
}

/// Split a string into words ignoring delimiter characters specified by the mask.
template <typename String, typename Mask, typename OutWordIt>
OutWordIt split_by_mask(String const & text, Mask const & delims, OutWordIt out)
{
  auto const base_ptr = &text[0];
  for (std::size_t i = 0, j = 0, n = text.size(); i < n; i = j)
  {
    // Find first not-delimiter.
    while (delims[text[i++]] && i < n)
      continue;
    if (i == n)
      break;

    // Now text[i] is not a delimiter.
    // Find first delimiter after it.
    for (j = i + 1; j < n && !delims[text[j]]; ++j)
      continue;

    // Output the next word.
    *out = String(base_ptr + i, base_ptr + j);
  }
  return out;
}


/// The main tool here: all Unicode things bound into a class.
class Uniworks
{
public:
  /// Convert UTF-8 string to UTF-32 string.
  /// Throws on error.
  static std::u32string to_utf32(std::string_view u8)
  {
    if (!utf8::is_valid(u8.begin(), u8.end()))
      std::clog << "!invalid utf-8\n";
    
    std::u32string u32(0, utf8::unchecked::distance(u8.begin(), u8.end()));
    utf8::unchecked::utf8to32(u8.begin(), u8.end(), u32.begin());
    return u32;
  }

  /// Convert UTF-32 string to UTF-8.
  static std::string to_utf8(std::u32string_view u32)
  {
    std::string u8;
    u8.reserve(2 * u32.size());
    utf8::unchecked::utf32to8(u32.begin(), u32.end(), std::back_inserter(u8));
    u8.shrink_to_fit();
    return u8;
  }

  /// Initialize the codepoint info table with the description from a file.
  explicit Uniworks(std::istream & categories)
  {
    _init(categories);
  }

  /// Initialize the codepoint info table with the description from a file (by name).
  explicit Uniworks(char const * categories_filename)
  {
    std::ifstream categories(categories_filename);
    if (!categories.is_open())
      throw std::runtime_error(
        std::string("Uniworks ctor: can't open categories file ") + categories_filename);
    _init(categories);
  }

  /// Get known codepoints.
  char32_t codepoints() const noexcept
  {
    return static_cast<char32_t>(_info.size());
  }

  /// Get name by code.
  std::string const & name(char32_t code) const
  {
    return _info.at(code).name;
  }

  /// Get code by name (linear search, upper case).
  char32_t code(std::string_view name) const
  {
    for (std::size_t i = 0, n = _info.size(); i < n; ++i)
      if (_info[i].name == name)
        return static_cast<char32_t>(i);
  }

  /// Get category code by codepoint.
  std::string_view cc(char32_t code) const
  {
    return _info.at(code).cc;
  }

  /// Make category bitmap.
  std::vector<bool> cc_bitmap(std::string_view cc) const
  {
    if (cc.empty())
      throw std::logic_error("Uniworks cc_bitmap: empty cc not allowed.");

    bool const cc1 = cc.size() == 1;
    auto const sz = _info.size();
    std::vector<bool> result(sz);
    for (std::size_t i = 0; i < sz; ++i)
    {
      char const * cci = _info[i].cc;
      if (cci[0] == cc[0] && (cc1 || cci[1] == cc[1]))
        result[i] = true;
    }

    return result;
  }

  /// Get codepoint by its name (upper case).
  /// Returns -1 if not found.
  char32_t by_name(std::string_view codepoint_name) const noexcept
  {
    auto it = _by_name.find(codepoint_name);
    return it == _by_name.end()? -1: it->second;
  }

  /// Convert string to lower letters in-place.
  std::u32string & inplace_to_lower(std::u32string & u32) const
  {
    return _apply_sub(u32, _to_lower);
  }

  /// Convert string to upper letters in-place.
  std::u32string & inplace_to_upper(std::u32string & u32) const
  {
    return _apply_sub(u32, _to_upper);
  }

private:
  /// Codepoint description.
  struct Codepoint_entry
  {
    std::string name;        ///< Codepoint name.
    std::string category[4]; ///< Category description.
    char cc[3] {};           ///< Category code (two letters plus terminating zero).
  };

  // Data.
  std::vector<Codepoint_entry> _info;
  std::unordered_map<std::string_view, char32_t> _by_name;
  // One-by-one to lower / to upper tables (may be not appropriate for natural languages).
  std::vector<char32_t> _to_lower, _to_upper;

  /// Initialize _info.
  void _init(std::istream & categories)
  {
    _read_categories(categories);
    _init_lower_upper();
  }

  void _read_categories(std::istream & categories)
  {
    _info.reserve(0xE01F0);
    // Parse categories line by line.
    std::istringstream line_parser;
    for (std::string line; std::getline(categories, line);)
    {
      std::uint32_t code = 0;
      line_parser.str(line);
      line_parser >> std::hex >> code;
      // Enforce the table size to hold index code.
      if (code >= _info.size())
        _info.resize(code + 1);
      
      auto & e = _info[code];
      line_parser >> e.cc[0] >> e.cc[1];
      line_parser.ignore(); // ignore the next \t
      for (auto & cat: e.category)
        std::getline(line_parser, cat, u8'\t');

      // The only thing left is the name of the character.
      std::getline(line_parser, e.name);
      line_parser.clear();

      // Bind name to this codepoint.
      _by_name[e.name] = code;
    }
  }

  void _init_lower_upper()
  {
    // Fill to_lower and to_upper with an identity permutation.
    _to_lower.resize(_info.size());
    std::iota(_to_lower.begin(), _to_lower.end(), char32_t(0));
    _to_upper.resize(_info.size());
    std::iota(_to_upper.begin(), _to_upper.end(), char32_t(0));

    // Conv maps a letter name (without small/capital) to a pair of codes
    // of small (first) and capital (second) variants of the letter.
    std::unordered_map<std::string, std::pair<char32_t, char32_t>> conv;
    conv.reserve(2500); // IDK how many letters there...
    for (size_t i = 0, n = _info.size(); i < n; ++i)
    {
      if (auto & e = _info[i]; e.cc[0] == u8'L')
      {
        if (auto const small = e.name.find(u8"SMALL"); small != std::string::npos)
          conv[std::string(e.name).erase(small, 5)].first = i;
        else if (auto const cap = e.name.find(u8"CAPITAL"); cap != std::string::npos)
          conv[std::string(e.name).erase(cap, 7)].second = i;
      }
    }

    // Use conv to fill _to_lower and _to_upper.
    for (auto & [k, v] : conv)
    {
      _to_lower[v.second] = v.first;
      _to_upper[v.first] = v.second;
    }
  }

  template <typename A, typename P>
  static A & _apply_sub(A & a, P const & p)
  {
    auto const sz = p.size();
    for (auto & item : a)
      item = item < sz? p[item]: item;
    return a;
  }
};


int main()
{
  using namespace std;
  string s = u8"Слова, слова и !!! не слова-слова.";
  
  return 0;
}

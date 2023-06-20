#include "H.hpp"

#include <iterator>
#include <iostream>
#include <string>

using namespace std;


// Вспомогательная функция для вывода сообщения об проваленном тесте.
int test_rfind(
    char const * const * integers,
    int answer
  )
{
  if (auto result = max_int(integers); result != answer)
  {
    clog << result;
    clog << " != " << answer << endl;
    return 1;
  }

  return 0;
}

// Собственно тест.
int test_rfind()
{
  int errors = 0;
  char const * integers[]
  {
    "73921",
    "943",
    "321",
    "142",
    "1342",
    "291421"
  };

  int const answer[] 
  {
    291421, 73921, 1342
  };

  size_t const place[]
  {
    5, 0, 4
  };

  char const * const replacement[]
  {
    "431", "824", "21538"
  };

  for (size_t i = 0; i < size(answer); ++i)
  {
    cout << i+1 << endl;
    cout << max_int(integers) << endl;
    errors += test_rfind(integers, answer[i]);
    integers[place[i]] = replacement[i];
  }

  return errors;
}

int main()
{
  clog << "Testing rfind:\n";
  int e = test_rfind();
  clog << "Errors: " << e << endl;
  return 0;
}

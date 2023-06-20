// Pascal decomment state machine.
#include <cstddef>
#include <iostream>
using namespace std;

// Decomment state machine implementation.
// Needs 1 byte padding.
char * pascal_decomment(char const * from, char const * to, char * out)
{
Normal:
  while (from != to)
  {
    char const in = *from++;
    switch (in)
    {
    case '/':
      if (*from == '/')
        goto Oneliner;
      break;
    case '{':
      goto Multiliner1;
    case '(':
      if (*from == '*')
        goto Multiliner2;
      break;
    case '\'':
      *out++ = in;
      goto String;
    }
    *out++ = in;
  }

  return out;

Oneliner:
  while (from != to)
  {
    if (*from++ == '\n')
    {
      *out++ = '\n';
      goto Normal;
    }
  }

  return out;

Multiliner1:
  while (from != to)
  {
    if (*from++ == '}')
    {
      *out++ = ' ';
      goto Normal;
    }
  }

  return out;

Multiliner2:
  ++from; // to skip * from (*
  while (from != to)
  {
    if (*from++ == '*' && *from++ == ')')
    {
      *out++ = ' ';
      goto Normal;
    }
  }

  return out;

String:
  while (from != to)
  {
    if ((*out++ = *from++) == '\'')
      goto Normal;
  }

  return out;
}

// Input.
size_t const MAX_FILE_SIZE = 1 << 20; // 1Mb.
char input[MAX_FILE_SIZE + 16];
char output[MAX_FILE_SIZE];

int main()
{
  cin.read(input, MAX_FILE_SIZE);
  if (!cin.eof())
    cerr << "Warning: input is longer than " << MAX_FILE_SIZE << " bytes.\n";
  cout.write(output,
    pascal_decomment(input, input + cin.gcount(), output) - output);
  if (!cout)
    cerr << "Write error.\n";
  return 0;
}

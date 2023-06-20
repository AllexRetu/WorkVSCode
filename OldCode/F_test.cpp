#include "F.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;

int test_long(int const A[], int const count, int const answer)
{
  if (auto result = longup(A, count), result != answer){
    clog << "for [";
    test_report_array(A, count);
    clog << "]\nresult is " << result << " != " << answer << endl;
    return 1;
  }
  return 0;
}

int test_long(int const A[], size_t count1)
{
  int count[count1] = {5, 2, 7, 4, 1, 8, 2, 6};
  int answer[count1] = {1, 1, 3, 2, 0, 3, 1, 2};
  int errors = 0;
  for (int i = 0; i < count1; i++)
      errors += test_long(A, count[i], answer[i]);
  return errors;
}

size_t call_istream(int const A[], size_t count)
{
  std::stringstream inout;
  for (int i = 0; i<count; i++)
    inout << A[i] << " ";
  return longup(inout);
}

void test_report_array(int const A[], size_t count)
{
  for (size_t i = 0; i < count; ++i)
    clog << A[i] << ' ';
}

int main()
{
  int const A[] = {1, 5, 12, 3, 5, 8, 134, 0};
  size_t count = 8;
  cout << test_long(A,count) << endl;
  cout << test_long(call_istream(A,count)) << endl;
}


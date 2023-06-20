#include "F.HPP"
#include <string>
#include <sstream> // строковые потоки ввода-вывода для тестирования.
#include <iterator>
#include <iostream>
using namespace std;

// Тип *указателя* на функцию, принимающую указатель на массив и размер и возвращающую позицию.
using Tested_function = size_t (*)(int const[], size_t);

// Функция-обёртка, позволяющая вызывать longup, принимающую поток ввода,
// так же, как longup, принимающую массив.
// Такая функция позволяет использовать один тест для проверки обоих вариантов longup.
size_t call_istream_longup(int const a[], size_t count)
{
  // Запишем массив в строковый поток.
  stringstream inout;
  for (size_t i = 0; i < count; ++i)
    inout << a[i] << ' ';

  // Применим к потоку inout функцию longup.
  return longup(inout);
}

// Вспомогательная функция для вывода массива.
void test_report_array(int const nums[], size_t count)
{
  for (size_t i = 0; i < count; ++i)
    clog << nums[i] << ' ';
}

// Вспомогательная функция для вывода сообщения.
int test_longup
  (
    Tested_function fzz, // тестируемая функция.
    int const nums[], // указатель на тестовый массив.
    size_t count,        // его размер.
    size_t answer        // правильный ответ.
  )
{
  if (auto result = fzz(nums, count); result != answer)
  {
    clog << "for [";
    test_report_array(nums, count);
    clog << "]\nresult is " << result << " != " << answer << endl;
    return 1;
  }
  return 0;
}

// Собственно тест.
// Принимает тестируемую функцию, возвращает число ошибок.
int test_longup(Tested_function fzz)
{
  int errors = 0;
  int const t[]
  {
 // 0  1  2  3  4  5  6  7  8  9 10 11 12 
    0, 1, 2, 3, 4, 0, 1, 0, 0, 2, 3, 0, 0
  };

  // Список тестов.
  size_t
    offset[] {  0,  0,  0,  3,  0,  0,  0,  0,  0,  8 },
    count[]  {  0,  5,  6,  8,  9, 13,  2,  6,  4,  5 },
    answer[] {  0,  4,  4,  2,  1,  2,  1,  4,  3,  2 };
  
  static_assert(size(offset) == size(count));
  static_assert(size(offset) == size(answer));

  for (size_t i = 0; i < size(offset); ++i)
    errors += test_longup(fzz, t + offset[i], count[i], answer[i]);

  return errors;
}

int main()
{
  string name[] { "longup(nums[], count)",  "longup(istream&)" };
  Tested_function fzz[] {       longup , call_istream_longup };

  static_assert(size(name) == size(fzz));

  for (size_t i = 0; i < size(fzz); ++i)
  {
    clog << "\nTesting " << name[i] << ":\n";
    int errors = test_longup(fzz[i]);
    clog << "\n======\nErrors: " << errors << endl;
  }
  
  return 0;
}

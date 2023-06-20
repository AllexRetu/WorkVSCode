#include <iostream>
#include <cmath>
#include <cassert> // assert
using namespace std;

// Особое значение "бесконечное (несчётное) количество корней".
int const INFINITE_ROOTS = -1;
// Используемый числовой тип (Number Type).
using NT = float;

NT const // Вспомогательные числовые константы:
  HALF_PI   = 1.5707963267948966, // половина пи,
  PI        = 3.1415926535897932, // число пи,
  DOUBLE_PI = 6.2831853071795865, // два пи,
  TOLERANCE = 1e-10; // граница между "нулём" и "ненулём".

// Проверка значения на близость нулю.
bool is_almost_zero(NT x, NT tolerance = TOLERANCE)
{
  return fabs(x) <= tolerance;
}

// Левая часть уравнения.
NT f(NT a, NT b, NT c, NT x)
{
  return sin(a*PI*cos(b*b*tan(pow(c, 3)*pow(x, 4))));
}

// Решаем уравнение f(a, b, c, root) = 0.
// Функция возвращает "количество корней".
// Если корень найден, то функция записывает его в переменную, переданную по ссылке.
int solve_f(NT a, NT b, NT c, NT & root) 
{
  if (a == 0)
    return INFINITE_ROOTS;
    
  if (b == 0 || c == 0)
    return is_almost_zero(a-floor(a))?
    INFINITE_ROOTS : 0; // нет корней.

  // Счётное число корней, получим один из них.
  NT const
    // Часть выражения:
    expr_part = fabs(atan(HALF_PI/(b*b))/(pow(c, 3)));

  root = sqrt(sqrt(expr_part));
  return 1;
}

// Точка входа.
int main()
{
  cout << "Solving f(a, b, c, x) = 0,"
       << " enter a, b, c:\n";

  cout.precision(16);

  for (NT a, b, c, x; cin >> a >> b >> c;)
  {
    switch (solve_f(a, b, c, x))
    {
    case 0:
      cout << "no roots\n";
      break;
    
    case INFINITE_ROOTS:
      cout << "any number is a root\n";
      break;
    
    case 1: // один корень, записан в x
      cout << "x == " << x 
           << ", error is " << f(a, b, c, x) 
           << endl;
      break;
    
    default:
      assert(!"impossible roots quantity");
      cout << "unknown error\n";
      return 1; // ошибка.
    }
  }

  return 0;
}

// ageo2d.hpp
// Точки и вектора на плоскости, элементарные определения.
// Версия 2: при использовании C++14 (MSVC2015) во многих местах можно было бы записать возвращаемый тип auto.
#include <type_traits>
#ifndef AGEO2D_HPP_INCLUDED_
#define AGEO2D_HPP_INCLUDED_

///////////////////////////////////////////////////////////////////////////////
// Вектора

/// Двумерный вектор.
template <typename X>
struct Vector_2
{
  using Coordinate = X;
  Coordinate x, y;
  /// Конструктор по умолчанию -- нулевой вектор.
  Vector_2()
    : x(Coordinate()), y(Coordinate()) {}
  /// Создать вектор с заданными координатами.
  Vector_2(Coordinate x, Coordinate y)
    : x(x), y(y) {}

  /// Добавить другой вектор "на месте".
  Vector_2& operator+=(Vector_2 const &other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  /// Вычесть другой вектор "на месте".
  Vector_2& operator-=(Vector_2 const&other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  /// Домножить на скаляр "на месте".
  Vector_2& operator*=(Coordinate factor)
  {
    x *= factor;
    y *= factor;
    return *this;
  }
};

/// Определить тип координаты вектора для двух типов чисел, из которых она вычисляется.
template <typename X, typename Y>
using Coordinate_of = typename std::common_type<X, Y>::type;

/// Определить тип вектора для разнотипных координат.
template <typename X, typename Y>
using Vector_2_of = Vector_2<Coordinate_of<X, Y>>;

/// Создать вектор из разнотипных координат.
/// Вспомогательная функция для удобства записи.
template <typename X, typename Y> inline
auto make_vector(X x, Y y)
{
  return Vector_2_of<X, Y>(x, y);
}


/// Проверка пары векторов на равенство.
template <typename Coordinate1, typename Coordinate2> inline
bool operator==(
  Vector_2<Coordinate1> const &a, 
  Vector_2<Coordinate2> const &b)
{
  return a.x == b.x && a.y == b.y;
}

/// Проверка пары векторов на неравенство.
template <typename Coordinate1, typename Coordinate2> inline
bool operator!=(
  Vector_2<Coordinate1> const &a,
  Vector_2<Coordinate2> const &b)
{
  return !(a == b);
}

/// Сумма векторов: операция "+".
template <typename Coordinate1, typename Coordinate2> inline
auto operator+(
  Vector_2<Coordinate1> const &a, 
  Vector_2<Coordinate2> const &b)
{
  return make_vector(a.x + b.x, a.y + b.y);
}

/// Разность векторов: операция "-".
template <typename Coordinate1, typename Coordinate2> inline
auto operator-(
  Vector_2<Coordinate1> const &a, 
  Vector_2<Coordinate2> const &b)
{
  return make_vector(a.x - b.x, a.y - b.y);
}

/// Унарный минус.
template <typename Coordinate> inline
auto operator-(Vector_2<Coordinate> const &a)
{
  return make_vector(-a.x, -a.y);
}

/// Умножение вектора на скаляр слева: операция "*".
template <typename Coordinate1, typename Coordinate2> inline
auto operator*(
  Coordinate1 factor,
  Vector_2<Coordinate2> const &vec)
{
  return make_vector(factor * vec.x, factor * vec.y);
}

/// Умножение вектора на скаляр справа: операция "*".
template <typename Coordinate1, typename Coordinate2> inline
auto operator*(
  Vector_2<Coordinate1> const &vec,
  Coordinate2 factor)
{
  return factor * vec; // то же, что и слева
}


/// Скалярное произведение векторов.
template <typename Coordinate1, typename Coordinate2> inline
auto dotp(
  Vector_2<Coordinate1> const &a,
  Vector_2<Coordinate2> const &b)
{
  return a.x * b.x + a.y * b.y;
}

/// Псевдоскалярное произведение векторов.
/// Равно произведению длин векторов на синус угла между ними.
template <typename Coordinate1, typename Coordinate2> inline
auto crossp(
  Vector_2<Coordinate1> const &a,
  Vector_2<Coordinate2> const &b)
{
  return a.x * b.y - a.y * b.x;
}


///////////////////////////////////////////////////////////////////////////////
// Точки

/// Точка на плоскости.
template <typename X = double>
struct Point_2
{
  using Coordinate = X;
  Coordinate x, y;
  /// Конструктор по умолчанию -- начало координат.
  Point_2()
    : x(Coordinate()), y(Coordinate()) {}
  /// Создать точку с заданными координатами.
  Point_2(Coordinate x, Coordinate y)
    : x(x), y(y) {}

  /// Радиус-вектор точки.
  Vector_2<Coordinate> radius() const
  {
    return make_vector(x, y);
  }

  /// Сместить эту точку на заданный вектор.
  template <typename Y>
  Point_2& operator+=(Vector_2<Y> const &delta)
  {
    x += delta.x;
    y += delta.y;
    return *this;
  }

  /// Сместить эту точку на -delta.
  template <typename Y>
  Point_2& operator-=(Vector_2<Y> const &delta)
  {
    x -= delta.x;
    y -= delta.y;
    return *this;
  }
};

/// Определить тип точки для разнотипных координат.
template <typename X, typename Y>
using Point_2_of = Point_2<Coordinate_of<X, Y>>;

/// Создать точку из разнотипных координат.
/// Вспомогательная функция для удобства записи.
template <typename X, typename Y> inline
Point_2_of<X, Y> make_point(X x, Y y)
{
  return Point_2_of<X, Y>(x, y);
}

/// Проверка пары точек на равенство.
template <typename Coordinate1, typename Coordinate2> inline
bool operator==(
  Point_2<Coordinate1> const &a,
  Point_2<Coordinate2> const &b)
{
  return a.x == b.x && a.y == b.y;
}

/// Проверка пары точек на неравенство.
template <typename Coordinate1, typename Coordinate2> inline
bool operator!=(
  Point_2<Coordinate1> const &a, 
  Point_2<Coordinate2> const &b)
{
  return !(a == b);
}

/// Разность двух точек даёт вектор.
template <typename Coordinate1, typename Coordinate2> inline
Vector_2_of<Coordinate1, Coordinate2>
operator-(
  Point_2<Coordinate1> const &a, 
  Point_2<Coordinate2> const &b)
{
  return make_vector(a.x - b.x, a.y - b.y);
}

/// К точке можно добавить вектор, чтобы получить смещённую точку.
template <typename Coordinate1, typename Coordinate2> inline
Point_2_of<Coordinate1, Coordinate2>
operator+(
  Point_2<Coordinate1> const &a, 
  Vector_2<Coordinate2> const &delta)
{
  return make_point(a.x + delta.x, a.y + delta.y);
}

/// К точке можно добавить вектор, чтобы получить смещённую точку.
template <typename Coordinate1, typename Coordinate2> inline
Point_2_of<Coordinate1, Coordinate2>
operator+(
  Vector_2<Coordinate1> const &delta, 
  Point_2<Coordinate2> const &a)
{
  return a + delta;
}

/// Из точки можно вычесть вектор, чтобы получить смещённую точку.
template <typename Coordinate1, typename Coordinate2> inline
Point_2_of<Coordinate1, Coordinate2>
operator-(
  Point_2<Coordinate1> const &a, 
  Vector_2<Coordinate2> const &delta)
{
  return make_point(a.x - delta.x, a.y - delta.y);
}

#endif//AGEO2D_HPP_INCLUDED_

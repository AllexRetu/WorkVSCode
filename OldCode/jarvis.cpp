// jarvis.cpp
// Алгоритм Джарвиса ("заворачивания подарка")
// построения выпуклой оболочки множества точек на плоскости.
// Версия с использованием стандартных алгоритмов.
#include "ageo2d.hpp" // точки и вектора

#include <cassert>
#include <utility>    // swap
#include <cmath>      // abs
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

/// Сравнение по x, затем по y (лексикографическое сравнение векторов и точек).
auto const less_xy = 
[](auto const & a, auto const & b)
  {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  };

/// В диапазоне точек найти самую верхнюю из самых правых.
template <typename P2_FwdIt> inline
P2_FwdIt find_highest_rightmost(P2_FwdIt begin, P2_FwdIt end)
{
  return std::max_element(begin, end, less_xy);
}


/// Сравнение радиусов-векторов точек по углу относительно заданного начала координат (origin),
/// затем по длине, если вектора коллинеарны.
template <typename P>
auto less_angle(P const & origin)
{
  return [=](P const & a, P const & b)
  {
    const auto
      oa = a - origin,
      ob = b - origin;
    const auto
      cp = crossp(oa, ob);
    return cp < 0 || (cp == 0 && dotp(oa, oa) < dotp(oa, ob));
  };
}


/// В диапазоне точек найти самый дальний поворот по часовой стрелке от точки v.
template <typename P2_FwdIt, typename P2>
P2_FwdIt max_cw_turn(
  P2_FwdIt begin, P2_FwdIt end, P2 const &v)
{
  return std::max_element(begin, end, less_angle(v));
}


/// Алгоритм заворачивания подарка.
/// Переставляет элементы исходного диапазона точек так,
/// чтобы вершины выпуклой оболочки в порядке обхода против часовой стрелки
/// встали в начале диапазона, возвращает указатель на следущую за последней
/// вершиной построенной выпуклой оболочки вершину.
template <typename P2_BidIt>
P2_BidIt convex_hull_jarvis(P2_BidIt begin, P2_BidIt end)
{
  using std::swap;
  using std::prev;
  if (begin == end)
    return end;

  // Найти самую верхнюю из самых правых точек.
  // Это -- последняя вершина выпуклой оболочки.
  auto const last_point = *find_highest_rightmost(begin, end);
  // Удалить все точки, равные last_point, и записать last_point в конец последовательности.
  // чтобы корректно выйти из цикла, когда следующая вершина совпадёт с ней.
  auto const last_pos = std::remove(begin, end, last_point);
  end = std::next(last_pos);
  *last_pos = last_point;

  // Цикл по вершинам выпуклой оболочки.
  for (auto cur = last_pos;;)
  {
    auto const next = max_cw_turn(begin, end, *cur);
    // Поставить следующую вершину.
    swap(*begin, *next);
    cur = begin++;
    if (next == last_pos) // Выпуклая оболочка построена.
      return begin;
  }
}


///////////////////////////////////////////////////////////////////////////////
// Геометрические операции, применяемые при тестировании

/// Вспомогательное значение для корректной инициализации конечного итератора рёбер.
struct End_iterator_tag {} const end_iterator_tag;

/// Итератор, позволяющий перебрать отрезки (как вектора) ломаной,
/// в действительности проходя по вершинам.
template <typename P_FwdIt>
class Edge_iterator
{
  P_FwdIt a, b;

public:
  Edge_iterator() = default;

  explicit Edge_iterator(P_FwdIt a)
    : a(a), b(std::next(a)) { init_val(); }

  Edge_iterator(P_FwdIt a, P_FwdIt b)
    : a(a), b(b) { init_val(); }

  Edge_iterator(P_FwdIt end, End_iterator_tag)
    : a(end) {}

  using iterator_category = std::forward_iterator_tag;
  using value_type = Vector_2<
    typename std::iterator_traits<P_FwdIt>::value_type::Coordinate>;

  using reference = const value_type&;
  using pointer = const value_type*;
  using difference_type = std::ptrdiff_t;

  Edge_iterator& operator++()
  {
    a = b;
    ++b;
    init_val();
    return *this;
  }

  Edge_iterator operator++(int)
  {
    auto old = *this;
    ++(*this);
    return old;
  }

  reference operator*() const { return val; }
  pointer operator->() const { return &val; }

  bool operator==(Edge_iterator const &other) const
  {
    return a == other.a;
  }

  bool operator!=(Edge_iterator const &other) const
  {
    return !(*this == other);
  }

private:
  value_type val;
  void init_val()
  {
    val = *b - *a;
  }
};

template <class P_FwdIt> inline
auto make_edge_iterator_end(P_FwdIt end)
{
  return Edge_iterator<P_FwdIt>(end, end_iterator_tag);
}


/// Компаратор "поворот направо" (против ЧС == counterclockwise == ccw).
auto const is_ccw = [](auto const & a, auto const & b)
  {
    return crossp(a, b) > 0;
  };

/// Логическое отрицание is_ccw.
auto const is_not_ccw = std::not_fn(is_ccw);


/// Проверка многоугольника на строгую выпуклость.
template <typename P2_BidIt>
bool is_strictly_convex(P2_BidIt begin, P2_BidIt end)
{
  using std::next;
  using std::prev;

  if (begin == end)
    return true; // пустое множество

  auto const begin_1 = next(begin);
  if (begin_1 == end)
    return true; // одна точка

  auto const begin_2 = next(begin_1);
  if (begin_2 == end)
    return *begin != *begin_1; // невырожденный отрезок?

  // Проходя по всем углам (парам смежных рёбер) многоугольника,
  // проверять, что поворот происходит строго против ЧС.
  auto const end_1 = prev(end), end_2 = prev(end_1);
  auto const
    edge_begin = Edge_iterator(begin),
    edge_end = make_edge_iterator_end(end_1);

  return is_ccw(*end_1 - *end_2, *begin - *end_1)
    && std::adjacent_find(edge_begin, edge_end, is_not_ccw)
       == edge_end;
}


/// Положение точки относительно множества.
enum class Point_location
{
  inside,   // внутри
  boundary, // на границе
  outside   // снаружи
};

/// Определить положение точки p относительно многоугольника [begin, end),
/// вершины в котором перечислены в порядке обхода против часовой стрелки.
/// Осторожно: на результат может влиять погрешность вычислений.
/// Используется правило витков (== ненулевого индекса).
/// Алгоритм позаимствован с http://geomalgorithms.com/a03-_inclusion.html
template <typename P2_BidIt, typename P2, typename Tol>
Point_location locate_point
  (
    P2_BidIt begin, P2_BidIt end, // многоугольник
    P2 p,                         // точка
    Tol tolerance                 // условный допуск на границе
  )
{
  using std::abs;
  using std::prev;

  if (begin == end)
    return Point_location::outside;

  int wn = 0; // количество витков
  // Проходя по всем рёбрам многоугольника, считать количество витков.
  auto pred = *prev(end);
  do
  {
    auto const next = *begin++;
    auto const
      edge = next - pred,
      prad = p - pred;

    auto const cp = crossp(prad, edge);
    // Ребро пересекает луч снизу-вверх справа от точки p.
    if (pred.y <= p.y && p.y < next.y && 0 < cp)
      ++wn;
    // Ребро пересекает луч сверху-вниз справа от точки p.
    else if (next.y <= p.y && p.y < pred.y && cp < 0)
      --wn;
    // Дополнительная проверка: точка лежит на ребре
    else if (abs(cp) <= tolerance
          && dotp(prad, prad) <= dotp(prad, edge))
      return Point_location::boundary;

    pred = next;
  } while (begin != end);

  return wn == 0?
    Point_location::outside 
  : Point_location::inside;
}


///////////////////////////////////////////////////////////////////////////////
// Тестирование
#include <iostream>
#include <random>


/// Тест на основе заранее известной оболочки.
int test_chj_0()
{
  Point_2<> points[]
  {
    {  0,  0 },
    { 10,  0 },
    {  0, 10 },
    { 10, 10 },
    {  0,  1 },
    {  0,  0 },
    {  5,  0 },
    {  5,  5 },
    {  2,  7 },
  };
  
  Point_2<> const ch[] // convex hull.
  {
    {  0, 10 },
    {  0,  0 },
    { 10,  0 },
    { 10, 10 },
  };
  
  if (
    std::distance(
      std::begin(points),
      convex_hull_jarvis(std::begin(points), std::end(points))
    ) != std::size(ch)) return 1;

  if (!std::equal(std::begin(ch), std::end(ch), points))
    return 2;

  return 0;
}


/// Заполнить диапазон случайными точками с нормальным распределением по каждой координате.
/// Центр в нуле, среднеквадратичное отклонение единица.
std::vector<Point_2<>> make_random_normal(unsigned seed = 1415)
{
  using namespace std;
  mt19937_64 rng(seed);  // генератор псевдослучайных последовательностей бит
  uniform_int_distribution<> sz_distr(3, 2000); // равномерное распределение на целых из [3, 2000]
  normal_distribution<> coord_distr; // нормальное распределение

  std::vector<Point_2<>> pts(sz_distr(rng));
  generate(begin(pts), end(pts),
    [&]() { return make_point(coord_distr(rng), coord_distr(rng)); });

  return pts;
}


/// Проверить алгоритм выпуклой оболочки на заданном наборе точек.
template <typename P2_BidIt>
int test_cvj_on(P2_BidIt begin, P2_BidIt end)
{
  auto const ch_end = convex_hull_jarvis(begin, end);
  if (!is_strictly_convex(begin, ch_end))
    return 1;

  // Все прочие точки находятся внутри оболочки?
  for (auto p = ch_end; p != end; ++p)
    if (locate_point(begin, ch_end, *p, 0.) == Point_location::outside)
      return 2;

  return 0;
}

/// Сгенерировать случайный набор точек и проверить на нём алгоритм выпуклой оболочки.
int test_cvj_1(unsigned seed)
{
  using namespace std;
  // Сгенерировать случайный набор точек.
  auto points = make_random_normal(seed);
  cout << points.size() << '\t';
  // Проверить работу алгоритма на этом наборе точек.
  auto result = test_cvj_on(begin(points), end(points));
  cout << result << '\n';
  return result;
}


int main()
{
  using namespace std;
  auto test_0 = test_chj_0();
  cout << test_0 << endl;

  mt19937 seed_seq(2342); // генератор зёрен.
  while (test_cvj_1(seed_seq()) == 0)
    continue;
  cout << "\nfail";
  return 0;
}

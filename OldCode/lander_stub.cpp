// Взлёт-посадка.
#include <iostream>
#include <cmath>
using namespace std;

// Константы.
double const
  g = 1.62,      // ускорение свободного падения, Луна;
  I = 4600,      // удельный импульс двигателя, водород-кислород;
  M = 10'000,    // масса без топлива;
  fuel = 10'000; // начальная масса топлива.

// Состояние модели.
struct Model_state
{
  double t, m, v, x, w;
};

// Вывод состояния на экран.
ostream& operator<<(ostream & os, Model_state const & s)
{
  os << "t = " << s.t << ", m = " << s.m;
  return os << "\nx = " << s.x << ", v = " << s.v << ", w = " << s.w;
}

// Шаг моделирования.
Model_state unchecked_step(Model_state s0, double dt, double dm)
{
  double const
    m0 = s0.m,
    m1 = m0 + dm,
    ln_m0_m1 = log(m0 / m1),
    v0 = s0.v;

  s0.t += dt;
  s0.m = m1;
  s0.v = v0 - g*dt + I*ln_m0_m1;
  s0.x += dt*(v0 - 0.5*g*dt + (dm != 0? I*(1. + m1/dm * ln_m0_m1): 0));
  s0.w = -I*dm/(m1*dt) - g;

  return s0;
}

Model_state step(Model_state s0, double dt, double dm)
{
  // TODO
  return unchecked_step(s0, dt, dm);
}


int main()
{
  Model_state s { 0, M + fuel };
  for (double dt, dm; cin >> dt >> dm;)
  {
    s = step(s, dt, -dm);
    cout << s << endl;
  }

  return 0;
}

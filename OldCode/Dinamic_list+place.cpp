#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct elem
{
  double time;
  double coord;
  elem* next;
};

struct dyn_list
{
  elem* head;
  elem* tail;
};

void start_list(dyn_list & l)
{
  l.head = NULL;
}

bool clean_list(dyn_list & l)
{
  return(l.head == NULL);
}

void dyn_list_in(dyn_list & l, double TIME, double COORD)
{
  elem* c = new elem();
  c->time = TIME;
  c->coord = COORD;
  if (clean_list(l))
    l.head = c;
  else
    l.tail->next = c;
  l.tail = c;
}

void dynamic_list_clean(dyn_list & l)
{
  elem* pd = new elem();
  while (l.head != NULL)
  {
    pd = l.head;
    l.head = l.head->next;
    delete pd;
  }
  return;
}


int main() {
	double v_wall, v_body, t0, n;
cout << "Введите скорость плоскости, тела, время броска тела, точность(10^-n)" << endl;
cin >> v_wall >> v_body >> t0 >> n;
cout << "Скорость плоскости: " << v_wall << endl;
cout << "Скорость тела: " << v_body << endl;	
cout << "Время броска тела: " << t0 << endl;
if (v_wall < v_body)
{
  dyn_list body_position;
  start_list(body_position);
	double x_wall = v_wall*t0, x_body = 0, t_col = t0, znak, t_catch = t0;
	znak = pow(10,-n);
  double q = v_wall/v_body;
  while (x_wall - x_body > znak)
  {
    t_catch *= q;
    t_col += t_catch;
    x_body = x_wall;
    x_wall += v_wall*t_catch;
    dyn_list_in(body_position, t_col, x_body);
  }
cout << setprecision(10) << "Время столкновения: " << v_body*t0/(v_body-v_wall) << endl;
cout << "Координата столкновения: " << v_body*t0/(v_body-v_wall)*v_wall << endl;
elem* index = body_position.head;
do
{
  cout << "Time: " << index->time << "\t" << "Coord(body): " << index->coord << "\t" << "Coord(wall): " << (index->time)*v_wall << endl;
  index = index->next;
} while (index != body_position.tail);
dynamic_list_clean(body_position);
}
else
	cout << "Тело не догонит плоскость." << endl;
return 0;
}
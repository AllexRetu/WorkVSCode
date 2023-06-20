#include <iostream>

using namespace std;

struct elem
{
  size_t number;
  elem* next;
};

struct dyn_list
{
  elem* head;
  elem* tail;
};

void annons(dyn_list & l)
{
  l.head = NULL;
  return;
}

bool new_list(dyn_list & l)
{
  return(l.head==NULL); 
}

void dyn_list_in(dyn_list & l, size_t NUMBER)
{
  elem* c = new elem();
  c->number = NUMBER;
  if (new_list(l))
  {
    l.head = c;
    l.tail = c;
  }
  else
    l.tail->next = c;
  l.tail = c;
  c->next = l.head;
}

void del_elem(dyn_list & l, elem* d)
{
  if (l.head == d)
  {
    if (d->next == d)
      delete d;
    else
    {      
    l.head = d->next;
    l.tail->next = l.head;
    delete d;
    }
  }
  else
  {  
    elem* pd = new elem();
    pd = l.head;
    while (pd->next != d)
      pd = pd->next;
    pd->next = d->next;
    if (d == l.tail)
      l.tail = pd;
    delete d;
  }
}

int main()
{
  int N, b;
  cin >> N >> b;
  cout << "Количество человек: " << N << endl;
  cout << "Количество слов в считалке: " << b << endl;
    dyn_list numbers;
    annons(numbers);
    for (int i = 1; i<N+1; i++)
      dyn_list_in(numbers, i);
    elem* d = new elem();
    elem* del = new elem(); 
    d = numbers.tail;
    for (int i = 1; i<N; i++)
    {
      for (int j = 1; j<b; j++)
        d = d->next;
      del = d->next;
      del_elem(numbers, del);
    }
    cout << "Номер оставшегося человека: " << (numbers.head)->number << endl;
    del_elem(numbers, numbers.head);
  return 0;
}
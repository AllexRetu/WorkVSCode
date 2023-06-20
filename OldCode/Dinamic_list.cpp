#include <iostream>

using namespace std;

struct elem
{
  int number;
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

void dyn_list_in(dyn_list & l, int NUMBER)
{
  elem* c = new elem();
  c->number = NUMBER;
  if (new_list(l))
    l.head = c;
  else
    l.tail->next = c;
  l.tail = c;
  c->next = l.head;
}

void cleaning(dyn_list & l)
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

void del_elem(dyn_list & l, elem* d)
{
  if (l.head == d)
  {
    l.head = d->next;
    l.tail->next = l.head;
    delete d;
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

void print(dyn_list & l, int count)
{
  elem* ssilka = new elem();
  ssilka = l.head;
    for (int i = 0; i < count; i++)
  {
    cout << ssilka->number << endl;
    ssilka = ssilka->next; 
  }
}

elem* search_value(dyn_list & l, int value)
{
  elem* needed = new elem();
  needed = l.head;
  while (needed->number != value)
    needed = needed->next;
  return needed;
}

int main()
{  
  dyn_list numbers;
  annons(numbers);
  new_list(numbers);
//  for (int i = 1; i<10; i++)
//    dyn_list_in(numbers, i);
  dyn_list_in(numbers, 13);
  dyn_list_in(numbers, 20);
//  del_elem(numbers, search_value(numbers, 1));
  print(numbers, 3);
  cleaning(numbers);
}
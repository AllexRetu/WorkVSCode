#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Student;

struct Slice_word
{
  Student* begin = nullptr;
  Student* end = nullptr;
};

class Group;
class Student
{ 
  private:
  //string Full_name;
  Student* next;

  friend Group;

  public:

  string Full_name;

  Student(string const & Full_name)
  {
    this->Full_name = Full_name;

  }

  Student()
  {
    this->Full_name = "";

  }

  string info()
  { 
    string copy = "Name of student: " + Full_name + "\n";

    return copy;
  }
};

class Group
{
  /*Student* first = nullptr;
  Student* last = nullptr;*/

  size_t number_of_students = 0;

  public:

  Student* first = nullptr;
  Student* last = nullptr;

  Student* search(string const & Full_name)
  {
    if(first->Full_name == Full_name)
      return first;
    for(Student* now = first; now != last; now = now->next)
      if(now->next->Full_name == Full_name)
        return now->next;
    return nullptr;
  }

  Slice_word search_slice_word(Student* start, Student* finish, size_t value, size_t position)
  {
    Slice_word slice;
    for(Student* befor = start; befor != finish; befor = befor->next)
    {
      size_t value2 = static_cast<size_t>(befor->Full_name[position]);
      size_t value3 = static_cast<size_t>(befor->next->Full_name[position]);
      if((value2 < value) && (value3 >= value))
        slice.begin = befor;
      if((value2 <= value) && (value3 > value))
        slice.end = befor->next;
    }
    return slice;
  }

  void append(string const & Full_name)
  {
    Student* new_ = new Student(Full_name);

    if( last == nullptr )
    {
      new_->next = new_;
      last = new_;
      first = new_;
    }

    else
    {
      Student* start = first;
      Student* finish = last;

      size_t ver = static_cast<size_t>(Full_name[0]);

      if( ver < static_cast<size_t>(first->Full_name[0]) )
      {
        last->next = new_;
        new_->next = first;
        first = new_;
      }
      else if( ver > static_cast<size_t>(last->Full_name[0]) )
      {
        new_->next = first;
        last->next = new_;
        last = new_;
      }
      else
      {        
        size_t student_number = 0;       
        for(Student* befor = start; student_number < number_of_students; befor = befor->next, ++student_number)
          if( ver <= static_cast<size_t>(befor->next->Full_name[0]) )
          {
            start = befor;
            break;
          }
          
        new_->next = start->next;
        start->next = new_;
      }
    }
    number_of_students++;
  }

  void print_student(ostream & out, string const & Full_name)
  {
    if(search(Full_name) == nullptr)
      out << "Student named: " << Full_name << " not in this group" << endl;
    else 
      out << search(Full_name)->info() << endl;
  }

  void print_group(ostream & out)
  {
    for(Student* now = first; now != last; now = now->next)
      out << now->info() << endl;
    out << last->info() << endl;
  }

  void deletion(string const & Full_name)
  {

    Student* del = search(Full_name);
    if(del == nullptr)
    {
      cout << "Student named: " << Full_name << " not in this group" << endl;
      delete del;
      return;
    }
    else if(del == first)
    {
        last->next = del->next;
        if(last == first)
        {
          last = nullptr;
          first = nullptr;
        }
    }
    else for(Student* now = first; now != last; now = now->next)
      if(now->next == del)
      {
        now->next = del->next;
        break;
      }
    delete del;
  }

  ~Group()
  {
    Student* del = this->first;
    while(this->first != this->last)
    {
      this->first = this->first->next;
      delete del;
      del = this->first;
    }
    delete del;
    this->first = nullptr;
    this->last = nullptr;

    cout << "Group: " << this << " cleared.";
  }
};

int main()
{
  srand((unsigned int)time(0));

  Group MEN_100705;
  size_t n = 20;
  vector<string> Names(n);
  
  for(size_t i = 0; i < n; ++i)
    Names[i] = (char)((rand() % 26) + 65);

  for(auto const & Name: Names)
    cout << Name[0] << '\n';
  cout << '\n';

  for(size_t i = 0; i < n; ++i)
    MEN_100705.append(Names[i]);

  ofstream f("Binary.txt", ios::binary);
  f.write((char*)&MEN_100705, sizeof(MEN_100705));
  f.close();
  
  MEN_100705.print_group(cout);

  char c = 'C';
  Slice_word slice = MEN_100705.search_slice_word(MEN_100705.first, MEN_100705.last, static_cast<size_t>(c), 0);

  cout << "--------------------------" << endl;
  cout << slice.begin->Full_name << '\t';
  cout << slice.end->Full_name << endl;

}

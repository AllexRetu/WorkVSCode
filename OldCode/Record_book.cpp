#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

class Subject
{
  public:
    virtual ostream& show(ostream & out) = 0;
    virtual void set(int x) = 0;
  
  virtual ~Subject(){};
};

template <typename T = int>
class Attestation : public Subject
{
    T score;
  public:
    ostream& show(ostream & out)
    {
      if(typeid(score) == typeid(bool))
      {
        if(score)
          return out << "Offset passed" << endl;
        return out << "Offset was not passed" << endl;
      }
      return out << "Scores: " << score << endl;
    }
    void set(int x)
    {
      score = (T)x;
    }
};

class Plan
{
  public:
    static const char* const sub[];
};

const char* const Plan::sub[] = { "Calculus", "Algebra and Geometry", "Programming" };

class Group;
class Student
{
  private:
  string full_name;
  vector<Subject*> subjects;
  Student* next;

  friend Group;
  friend Student* next(Student*);

  public:

  Student(string const & full_name, int* Exams, bool* Offsets)
  {
    this->full_name = full_name;
    for(size_t i = 0; i < 3; ++i)
    {
      Attestation<int>* exam = new Attestation<int>();
      exam->set(Exams[i]);
      subjects.push_back(exam);
    }
    for(size_t i = 0; i < 3; ++i)
    {
      Attestation<bool>* offset = new Attestation<bool>();
      offset->set(Offsets[i]);
      subjects.push_back(offset);
    }
  }

  Student(string const & full_name)
  {
    this->full_name = full_name;
    for(size_t i = 0; i < 3; ++i)
    {
      Attestation<int>* exam = new Attestation<int>();
      exam->set(0);
      subjects.push_back(exam);
    }
    for(size_t i = 0; i < 3; ++i)
    {
      Attestation<bool>* offset = new Attestation<bool>();
      offset->set(false);
      subjects.push_back(offset);
    }
  }

  string take_name()
  {
    return full_name;
  }

  vector<Subject*>& take_subjects()
  {
    return subjects;
  }

  ostream& info(ostream & out)
  {
    out << "Name of student: " << full_name << "\n";
    for(size_t i = 0; i < 3; ++i)
    {
      out << Plan::sub[i] << ":\n\t";
      subjects[i]->show(out);
      out << '\t';
      subjects[i+3]->show(out);
    }
    return out;
  }

  void change_scores(int const * const SUBJECTS)
  {
    for(int i = 0; i < 3; ++i)
    {
      Attestation<int>* exam = new Attestation<int>();
      delete subjects[i];
      exam->set(SUBJECTS[i]);
      subjects[i] = exam;
    }
    for(int i = 3; i < 6; ++i)
    {
      Attestation<bool>* offset = new Attestation<bool>();
      delete subjects[i];
      offset->set(SUBJECTS[i]);
      subjects[i] = offset;
    }
  }
};

Student* next(Student* a)
{
  return a->next;
}

ostream & operator<<(ostream & out ,Student* stud)
{
  return stud->info(out);
}

istream & operator>>(istream & in, Student* stud)
{
  int subjects[6];
  for(int i = 0; i < 6; ++i)
    in >> subjects[i];
  stud->change_scores(subjects);
  return in;
}

class Group
{
  Student* first = nullptr;
  Student* last = nullptr;

  Student* early(Student* LAST)
  {
    Student* pen = first;
    while(pen->next != LAST)
      pen = pen->next;
    return pen;
  }

  friend Student;

  public:

  Student* take_first()
  {
    return first;
  }

  Student* take_last()
  {
    return last;
  }

  Student* search(string const & full_name)
  {
    if(first->full_name == full_name)
      return first;
    for(Student* now = first; now != last; now = now->next)
      if(now->next->full_name == full_name)
        return now->next;
    return nullptr;
  }

  Group(vector<string> const & Names, int* const* const EXAMSS = NULL, bool* const* const OFFSETSS = NULL)
  {
    if( EXAMSS != NULL )
      for(size_t i = 0; i < size(Names); ++i)
      {
        Student* _new = new Student(Names[i], EXAMSS[i], OFFSETSS[i]);
        this->append(_new);
      }
    else
      for(size_t i = 0; i < size(Names); ++i)
      {
        Student* _new = new Student(Names[i]);
        this->append(_new);
      }
  }

  void append(Student* _new)
  {
    if( last == nullptr )
    {
      _new->next = _new;
      last = _new;
      first = _new;
    }

    else
    {
      if( _new->full_name <= first->full_name )
      {
            _new->next = first;
            first = _new;
            last->next = first;
            return;
      }

      if( _new->full_name >= last->full_name )
      {
            _new->next = first;
            last->next = _new;
            last = _new;
            return;
      }
      Student* now = first;
      for(size_t j = 0; j < size(_new->full_name); ++j)  
        if((now->full_name < _new->full_name) && (now->next->full_name > _new->full_name))
        {
          _new->next = now->next;
          now->next = _new;
        }
    }
  }

  ostream & print_student(ostream & out, string const & full_name)
  {
    if(search(full_name) == nullptr)
      out << "Student named: " << full_name << " not in this group" << endl;
    else 
      search(full_name)->info(out) << endl;
    return out;
  }

  ostream & print_group(ostream & out)
  {
    if(first != nullptr)
    {
      for(Student* now = first; now != last; now = now->next)
        out << now << endl;
      return out << last << endl;
    }
    else
      return out;
    
  }

  void change_scores(string const & full_name, int * const SUBJECTS)
  {
    search(full_name)->change_scores(SUBJECTS);
  }

  void deletion(string const & full_name)
  {
    Student* del = search(full_name);
    if(del == nullptr)
    {
      cout << "Student named: " << full_name << " not in this group" << endl;
    }
    else if(del == first)
    {
        if(last == first)
        {
          last = nullptr;
          first = nullptr;
        }
        else
        {
          last->next = del->next;
          first = del->next;
        }
    }
    else if(del == last)
    {
      Student* befor = early(del);
      befor->next = first;
      last = befor;
    }
    else for(Student* now = first; now != last; now = now->next)
      if(now->next == del)
      {
        now->next = del->next;
        break;
      }

    delete del;
  }

  Group* operator+(Student* stud)
  {
    this->append(stud);
    return this;
  }

  Group* operator-(string const & full_name)
  {
    this->deletion(full_name);
    return this;
  }

  ~Group()
  {
    if(first != nullptr)
    {
      Student* del = first;
      while(first != last)
      {
        for(size_t i = 0; i < 6; ++i)
          delete del->subjects[i];
        first = first->next;
        delete del;
        del = first;
      }
      delete del;
      first = nullptr;
      last = nullptr;
    }    

    cout << "Group: " << this << " cleared.\n";
  }
};

int main()
{
  vector<string> Names;

  ifstream it("Students.txt");
  string s;
  while(!it.eof())
  {   
    it >> s;  
    Names.push_back(s);
  }
  it.close();

  Group MEN_100705(Names);

  ifstream in("Scores.txt");
  for(int i = 0; !in.eof(); ++i)
    in >> MEN_100705.search(Names[i]);
  in.close();


  Student* tmp = new Student("ONRGNIRN");
  MEN_100705 + tmp;

  ofstream fout("Binary.txt");
  for(Student* now = MEN_100705.take_first(); now != MEN_100705.take_last(); now = next(now))
  {
    fout << now->take_name();
    fout << "\n";
    vector<Subject*> subjects = now->take_subjects();
    for(int i = 0; i < 3; ++i, fout << '\n')
    {
      fout.write((char*)&subjects[i], sizeof(int));
      fout.write((char*)&subjects[i+1], sizeof(bool));
    }
  }
  fout.close();

  MEN_100705.print_group(cout);
  for(size_t i = 0; i < size(Names); ++i)
    MEN_100705 - Names[i];
  cout << "Удалились все, кроме: " << tmp->take_name() << "\n\n";
  MEN_100705.print_group(cout);
  MEN_100705 - tmp->take_name();
  cout << "Пусто\n\n";
  MEN_100705.print_group(cout);

  return 0;
}
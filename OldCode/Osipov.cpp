#include <iostream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

template <typename It, typename Val>
It search_by_value_in_object(It begin, It end, Val value)
{
  for(; begin != end; ++begin)
    if((*begin).get_name() <= value && (*next(begin)).get_name() >= value)
      return begin;
  return end;
}

class Subject
{
  public:
    virtual ostream& show(ostream & out) = 0;
    virtual void set(int x) = 0;
  
  virtual ~Subject(){};
};

template <typename T>
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

struct Plan
{
  static const char* const sub[];
};
const char* const Plan::sub[] = {"МатАн", "ОП", "Алгем"};

class DateClass
{
    vector <Subject*> subjects;
    string name;

  public:

    DateClass()
    {
      this->name = "";
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

    DateClass(ifstream& in)
    {
      in >> this->name;
      for(size_t i = 0; i < 3; ++i)
      {
        int tmp;
        in >> tmp;
        Attestation<int>* exam = new Attestation<int>();
        exam->set(tmp);
        subjects.push_back(exam);
      }
      for(size_t i = 0; i < 3; ++i)
      {
        bool tmp;
        in >> tmp;
        Attestation<bool>* offset = new Attestation<bool>();
        offset->set(tmp);
        subjects.push_back(offset);
      }
    }

    const string& get_name() const
    {
      return name;
    }

    ostream& info(ostream & out) const
    {
      out << "Name of student: " << name << "\n";
      for(size_t i = 0; i < 3; ++i)
      {
        out << Plan::sub[i] << ":\n\t";
        subjects[i]->show(out);
        out << '\t';
        subjects[i+3]->show(out);
      }
      return out;
    }
};

class Group
{
    vector<DateClass> students;

  public:

    Group(ifstream& in)
    {
      while(!in.eof())
        this->set(in);
    }

    ifstream& set(ifstream& in)
    {
      DateClass new_student(in);
      auto a = search_by_value_in_object(students.begin(), students.end(), new_student.get_name());
      if(a == students.end())
        students.push_back(new_student);
      else
        students.insert(a, new_student);
      return in;
    }

    /*ifstream& set(ifstream& in)
    {
      students.push_back(DateClass(in));
      return in;
    }*/

    ostream& print(ostream& out)
    {
      for(auto const & student: students)
        student.info(out);
      return out;
    }

    ~Group()
    {
      students.clear();
      cout << "Group: " << this << " cleared.\n";
    }
};

ifstream& operator>>(ifstream& in, Group& group)
{
  return group.set(in);
}

ostream& operator<<(ostream& out, Group& group)
{
  return group.print(out);
}

int main()
{
  ifstream in("Osipov2.txt");
  Group MyGroup(in);
  cout << MyGroup;
}
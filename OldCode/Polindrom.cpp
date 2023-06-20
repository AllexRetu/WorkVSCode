#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  //ifstream in1("Pily.txt");
  ifstream in2("Poly.txt");
  in2.seekg(0, ios::end);
  int a;
  /*while(!in2.eof())
  {
    in2 >> a;
    cout << a << endl;
    in2.seekg(-2*8, ios::cur);
  }*/
  in2 >> a;
  cout << sizeof(int) << endl;
}
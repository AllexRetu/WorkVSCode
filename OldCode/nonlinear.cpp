#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
	return 3*atan(x) - x*x;
}

int main()
{
	double x0 = 1, xn = 2, xm, maj = 1.7*pow(10,-5);
	int i = 0;
	
	double f0 = f(x0);
	for (; abs(f(xn)) > maj; ++i)
	{
		xm = xn - (f(xn)*(xn-x0))/(f(xn)-f0);
		xn = xm;
		cout << xn << " " << f(xn) << endl;		
	}
	
	cout << "Корень: " << xn << endl;
	cout << "Итераций: " << i << endl;
}
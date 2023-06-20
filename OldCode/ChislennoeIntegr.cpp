#include <iostream>
#include <cmath>

using namespace std;

#define a 2
#define b 4.9

double f(double x)
{
	return 1/log(1 + x*x);
}

double Simpson(double h)
{
	int n = (b-a)/h;
	double S1 = 0;
	double S2 = 0;

	for(int i = 1; i < n; ++i)
	{
		S1 += f(a + h*i);
	}

	for(int i = 0; i < n; ++i)
	{
		S2 += f(a + h*i + h/2);
	}
	
	return (f(a) + f(b) + 2*S1 + 4*S2)*h/6;
}

double Gregori(double h)
{
	int n = (b-a)/h;
	double S1 = (f(a) + f(b))/2;

	for(int i = 1; i < n; ++i)
	{
		S1 += f(a + h*i);
	}

	return h*(S1 + (-3*f(a) + 4*f(a + h) - f(a + 2*h) - 3*f(b) + 4*f(a + (n-1)*h) - f(a + (n-2)*h))/24);
}

double Gauss()
{
	double A,B;
	B = (a + b)/2;
	A = (b - a)/2;
	return A/9.*(5*f(A*(-sqrt(3/5.)) + B) + 8*f(B) + 5*f(A*sqrt(3/5.) + B));
}

int main()
{
	cout.precision(20);
	cout << "Симпсон:" << endl << endl;

	double S1, S2, S3;
	S1 = Simpson(0.1);
	S2 = Simpson(0.05);
	S3 = Simpson(0.025);

	cout << S1 << endl;
	cout << S2 << endl;
	cout << S3 << endl << endl;
	
	double R1, R2, R3;
	
	R1 = (S2 - S1)*16/15;
	R2 = (S2 - S1)/15;
	R3 = (S3 - S2)/15;
	
	cout << R1 << endl;
	cout << R2 << endl;

	R2 = (S3 - S2)*16/15;

	cout << R2 << endl;
	cout << R3 << endl << endl;

	cout << "Грегори:" << endl << endl;
	
	S1 = Gregori(0.1);
	S2 = Gregori(0.05);
	S3 = Gregori(0.025);

	cout << S1 << endl;
	cout << S2 << endl;
	cout << S3 << endl << endl;
	
	R1 = (S2 - S1)*16/15;
	R2 = (S2 - S1)/15;
	R3 = (S3 - S2)/15;
	
	cout << R1 << endl;
	cout << R2 << endl;

	R2 = (S3 - S2)*16/15;

	cout << R2 << endl;
	cout << R3 << endl << endl;

	cout << "Гаусс" << endl << endl;
	cout << Gauss() << endl << endl;
}
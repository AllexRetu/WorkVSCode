#include <iostream>
#include <math.h>

//using namespace std;

#define series1 M_PI*M_PI/6
#define series2 1.202056903
#define series3 pow(M_PI,4)/90

long double sum(int n)
{
	long double s = 0;
		
	for (long long i = 1; i < n + 1; ++i)
	{
		s += (long double)(-2*(357*i-50))/(long double)(i*i*i*i*(i*i + 7*i - 1));
	}
	
	return s;
}

int main()
{
	int n[4] = {20, 100, 1000, 52};
	for(int i=0; i < 4; ++i)
	{
		std::cout << n[i] << " слагаемых: " << sum(n[i]) + 2*series1 + (-14)*series2 + 100*series3 << std::endl;
	}

	return 0;
}
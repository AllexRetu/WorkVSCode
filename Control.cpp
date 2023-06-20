#include <iostream>
#include <cmath>

using namespace std;

double s(double t,double l1,double l2,double l3,double l4)
{
    return (l1*sinh(1-t)+l3*cosh(1-t))*(l1*sinh(1-t)+l3*cosh(1-t))+(l2*sinh(1-t)+l4*cosh(1-t))*(l2*sinh(1-t)+l4*cosh(1-t));
}

double f(double l1,double l2,double l3,double l4)
{
    return l1*cosh(1) + l2*cosh(1) + l3*sinh(1) + l4*sinh(1) - sqrt(max(s(0,l1,l2,l3,l4),s(1,l1,l2,l3,l4))) - 5*l1 + 6*l2 - 18*l3;
}

int main()
{
    double maxf = 0;
    double l1 = -1;
    while (l1 <= 1)
    {
        double l2 = -sqrt(1-l1*l1);
        double l2max = sqrt(1-l1*l1);
        while (l2 <= l2max)
        {
            double l3 = -sqrt(1-l1*l1-l2*l2);
            double l3max = sqrt(1-l1*l1-l2*l2);
            while (l3 <= l3max)
            {
                double modl4 = sqrt(1-l1*l1-l2*l2-l3*l3);
                maxf = max(maxf, max(f(l1,l2,l3,modl4), f(l1,l2,l3,-modl4)));
                l3+=0.001;
            }
            l2+=0.001;
        }
        l1+=0.001;
    }

    cout << maxf;
}
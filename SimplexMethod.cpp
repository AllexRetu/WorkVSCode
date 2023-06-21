#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Matrix.hpp"

using namespace std;

pair<double, vector<double>> simplexMethod(Matrix const & A, Matrix const & b, Matrix const & c)
{
    

    return pair<double, vector<double>>();
}

int main()
{
    Matrix A
    {
        {1,2,3,},
        {3,2,1,},
        {2,2,1.99,},
        /*{1,-4,-7,1,4,0},
        {6,0,1,1,1,1},
        {0,9,11,2,0,1}*/
    },
    B
    {
        {1,0},
        {0,3},
        {1,2}
    };

    //cout << det(A) << endl;
    cout << perRow(A,0,1) << endl;
}
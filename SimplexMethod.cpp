#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Matrix.hpp"

using namespace std;

pair<double, vector<double>> simplexMethod(Matrix const & A, Matrix const & b, Matrix const & c)
{
    size_t m = A.size();
    size_t n = A.at(0).size();

    if (m != b.at(0).size() || n != c.at(0).size()) // проверка на корректность данных
        return pair<double, vector<double>>();

    Matrix E = createMatrix(m,m);   // создаем единичнуб матрицу
    for (int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            E[i][j] = i == j ? 1 : 0;

    Matrix A_ = (E|A);



    return pair<double, vector<double>>();
}

int main()
{
    Matrix A
    {
        {1,2,3,},
        {3,2,1,},
        {2,2,0,},
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

    cout << det(A) << endl;
    cout << perRow(A,0,1) << endl;

    cout << inverse(A) << endl;
    cout << proof(A) << endl;

    cout << 5*(A*B)+B << endl;



}
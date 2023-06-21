#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Matrix.hpp"

using namespace std;

pair<double, Matrix> simplexMethod(Matrix const & A, Matrix const & b, Matrix const & c)    // A - матрица m x n
{                                                                                                   // b - столбец
    size_t m = A.size();                                                                            // c - строка
    size_t n = A.at(0).size();

    if (c.size() != 1 || b.at(0).size() != 1 || m != b.size() || n != c.at(0).size()) // проверка на корректность данных
        return pair<double, Matrix>();

    Matrix E = createMatrix(m,m);   // создаем единичную матрицу
    for (int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            E[i][j] = i == j ? 1 : 0;

    Matrix A_ = (E|A);

    Matrix c1 = createMatrix(1,m);  // создем новый показатель качества
    for (int i = 0; i < m; ++i)
        c1[0][i] = -1e+5;   // -10^5

    Matrix c_ = (c1|c);

    cout << A_ << endl;
    cout << c_ << endl;

    Matrix X = createMatrix(n+m,1);

    









    return pair<double, Matrix>();
}

int main()
{
    Matrix A
    {
        {1,2,3,3},
        {3,2,1,4},
        {2,2,0,6},
        /*{1,-4,-7,1,4,0},
        {6,0,1,1,1,1},
        {0,9,11,2,0,1}*/
    },
    b
    {
        {1,},
        {0,},
        {1,}
    },
    c
    {
        {5,6,-1,6},
    };

    /*cout << det(A) << endl;
    cout << perRow(A,0,1) << endl;

    cout << inverse(A) << endl;
    cout << proof(A) << endl;

    cout << 5*(A*b)+b << endl;

    Matrix C = (A|b);

    cout << disjoin(C,3).first << endl;
    cout << disjoin(C,3).second << endl;*/
    
    simplexMethod(A,b,c);
}
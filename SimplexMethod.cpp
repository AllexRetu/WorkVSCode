#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "Matrix.hpp"

using namespace std;


pair<double, int> min(Matrix& E, Matrix const& b, Matrix & A_index_col, vector<int>& I)
{
    double min = ((inverse(E) * b)[0][0]) / (inverse(E) * A_index_col)[0][0];
    int p = 0;
    for (int i = 1; i < I.size(); ++i)
    {
        double cur = ((inverse(E) * b)[i][0]) / (inverse(E) * A_index_col)[i][0];
        if (cur < min)
        {
            min = cur;
            p = i;
        }
    }
    return make_pair(min, p);
}



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

    Matrix X = createMatrix(m + n, 1);   // столбец размерности m + n (в А_ m + n столбцов)
    Matrix XB = createMatrix(m, 1);
    Matrix XN = createMatrix(n, 1);
    for (int j = 0; j < m + n; ++j)
        X[j][0] = j;    // X - столбец индексов, хз вроде он и не пригодился

    for (int j = 0; j < m + n; ++j)
    {
        if (j < m)
            XB[j][0] = b[j][0];
        else
            XN[j - m][0] = 0;
    }
    //Matrix Xval = createMatrix(1, m + n);
    /*
    for (int j = 0; j < m + n; ++j)
        Xval[0][j] = j<m ? b[0][j] : 0; // Xval - столбец значений, элементы после m-го равны 0 (по алгоритму)
    */
    Matrix c_copy = c;
    Matrix A_copy = A;

    //хз какое должно быть условие выхода
    while (true)
    {
        int index = -1;
        // пункт 1
        for (int i = 0; i < m; ++i)
        {
            if ((c1 * inverse(E) * A_copy - c_copy)[0][i] < 0) // если все компоненты этого выражения > 0 то мы нашли оптимальный результат (см стр.2 низ)
            {
                index = i; // запомнили индекс компоненты < 0
                break;
            }
        }
        if(index == -1)
            return make_pair((c_copy * (XB|XN))[0][0], (XB|XN));

        // пункт 2a
        
        Matrix A_index_col = createMatrix(m, 1);
        for(int i = 0; i < m; ++i)
            A_index_col[i][0] = A_copy[i][index];
        vector<int> I;
        for (int i = 0; i < m; ++i)
            if ((inverse(E) * A_index_col)[i][0] > 0) // если все компоненты данного выражения > 0, то такой индекс добавляем в I
                I.push_back(i);
        if (I.empty()) // если таких индексов нет, то опт. результат = +infinity (см стр. 3)
            return make_pair(INT_MAX, XB|XN);
        
        // пункт 2b

        pair<double, int> min_res = min(E, b, A_index_col, I);
        XN[index][0] = min_res.first; // изсенили компоненту по формуле 3 (см стр. 4)
        int p = min_res.second; // запомнили индекс, на котором достигается минимум

        // переход к новой базисной матрице (см стр. 4)

        vector<double> for_swap = (transpos(E))[p];
        Matrix tE = transpos(E); // чтобю цикл не писать, лень
        Matrix tA = transpos(A_copy);
        tE[p] = tA[index];
        tA[index] = for_swap;
        E = transpos(tE);
        A_copy = transpos(tA);

        double x_swap = XB[p][0];
        XB[p][0] = XN[index][0];
        XN[index][0] = x_swap;
    }

    return make_pair((c_ * (XB|XN))[0][0], XB|XN);
    //return pair<double, Matrix>();
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
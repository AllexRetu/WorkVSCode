#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#include "Matrix.hpp"

using namespace std;


int min(Matrix const & invB, Matrix const & b, Matrix const & colIndexNegativeN, vector<int> const & I)   // функция ищет минимум из 2b формула (3)
{
    Matrix M1 = invB * b;
    Matrix M2 = invB * colIndexNegativeN;
    double min = M1[I.at(0)][0] / M2[I.at(0)][0];
    int p = I.at(0);
    cout << "Min:" << endl;
    cout << min << endl;
    for (int i = 1; i < I.size(); ++i)
    {
        double cur = M1[I[i]][0] / M2[I[i]][0];
        cout << cur << endl;
        if (cur < min)
        {
            min = cur;
            p = I[i];
        }
    }
    return p;
}


pair<double, Matrix> ret(Matrix const & invB, Matrix const & b, Matrix const & c_, vector<int> const & indexX)  // функция расчитывает оптимальное решение(вывод для simplexMethod) по B,b и c
{
    size_t m = invB.size();

    Matrix XB = invB * b;   // считаем ненулевые компоненты решения
    size_t cSize = c_.at(0).size();
    Matrix X = createMatrix(cSize, 1);  // это все компоненты (пока с искусственными)

    for (int j = 0; j < m; ++j)
        X[indexX[j]][0] = XB[j][0];

    return make_pair((c_*X).at(0).at(0), X);
}



pair<double, Matrix> simplexMethod(Matrix const & A, Matrix const & b, Matrix const & c)    // A - матрица m x n
{                                                                                           // b - столбец n x 1
    size_t m = A.size();                                                                    // c - строка 1 x m
    size_t n = A.at(0).size();

    if (c.size() != 1 || b.at(0).size() != 1 || m != b.size() || n != c.at(0).size()) // проверка на корректность данных
        return pair<double, Matrix>();


    // Выбор начального приближения

    
    Matrix E = createMatrix(m,m);   // создаем единичную матрицу
    for (int i = 0; i < m; ++i)
        for(int j = 0; j < m; ++j)
            E[i][j] = i == j ? 1 : 0;
    
    Matrix A_ = (E|A);

    Matrix c1 = createMatrix(1,m);  // создем новый показатель качества
    for (int i = 0; i < m; ++i)
        c1[0][i] = -1e+2;   // -10^2

    Matrix c_ = (c1|c);
    

    vector<int> indexX(n+m,0);   // столбец размерности m + n (в А_ m + n столбцов)
    for (int j = 0; j < m + n; ++j)
        indexX[j] = j;    // X - столбец индексов
    
    
    /*
    Matrix A_ = A;
    Matrix c_ = c;

    vector<int> indexX(n, 0);   // столбец размерности m + n (в А_ m + n столбцов)
    for (int j = 0; j < n; ++j)
        indexX[j] = j;    // X - столбец индексов
    */

    
    // Начало алгоритма
    //хз какое должно быть условие выхода
    while (true)
    {
        auto difA_ = disjoin(A_, m);    // выделим базисную матрицу
        Matrix B = difA_.first;
        Matrix N = difA_.second;

        auto difc_ = disjoin(c_, m);    // выделим базисное решение
        Matrix cB = difc_.first;
        Matrix cN = difc_.second;

        Matrix invB = inverse(B);   // возьмем обратную к базисной

        cout << "B:" << endl;
        cout << B << endl;

        cout << "N:" << endl;
        cout << N << endl;

        cout << "cB:" << endl;
        cout << cB << endl;

        cout << "cN:" << endl;
        cout << cN << endl;

        cout << "B^-1:" << endl;
        cout << invB << endl;

        cout << "B^-1*N" << endl;
        cout << invB*N << endl;

        if (invB == Matrix())
            return pair<double, Matrix>();

        int indexNegative = -1;
        Matrix d = cB * invB * N - cN;

        cout << "d:" << endl;
        cout << d << endl;

        double minJ = 0;
        // пункт 1
        for (int i = 0; i < d[0].size(); ++i)
        {   
            if (d[0][i] < 0) // если все компоненты этого выражения > 0 то мы нашли оптимальный результат (см стр.2 низ)
            {
                indexNegative = i; // запомнили индекс компоненты < 0 (ее будем изменять)
                break;
            }
        }
        if(indexNegative == -1)
            return ret(invB, b, c_, indexX);    // здесь надо будет еще убрать некоторые компоненты, потому что там есть искуственно введенные

        // пункт 2a
        
        Matrix colIndexNegativeN = createMatrix(m, 1);  // возьмем столбец из N соответствующий изменающейся координате XN
        for(int i = 0; i < m; ++i)
            colIndexNegativeN[i][0] = N[i][indexNegative];
        vector<int> I;
        for (int i = 0; i < m; ++i)
            if ((invB * colIndexNegativeN)[i][0] > 0) // если i-ая компонента > 0, то такой индекс добавляем в I
                I.push_back(i);
        if (I.empty()) // если таких индексов нет, то опт. результат = +infinity (см стр. 3)
            return make_pair(INT_MAX, Matrix());

        cout << "I:" << endl;

        for (int i = 0; i < I.size(); ++i)
            cout << I[i] << " ";
        cout << endl << endl;
        
        // пункт 2b

        int p = min(invB, b, colIndexNegativeN, I); // запомнили индекс, на котором достигается минимум(при изменении компоненты indexNegative)

        // переход к новой базисной матрице (см стр. 4)

        A_ = perCol(A_, p, m + indexNegative);
        c_ = perCol(c_, p, m + indexNegative);

        swap(indexX[p],indexX[m + indexNegative]);

        cout << "j = " << indexNegative << endl;
        cout << "p = " << p << endl << endl;
    }

    
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
        {4,},
        {1,}
    },
    c
    {
        {5,6,1,6},
    };

    /*cout << det(A) << endl;
    cout << perRow(A,0,1) << endl;

    cout << inverse(A) << endl;
    cout << proof(A) << endl;

    cout << 5*(A*b)+b << endl;

    Matrix C = (A|b);

    cout << disjoin(C,3).first << endl;
    cout << disjoin(C,3).second << endl;*/
    
    auto T = simplexMethod(A,b,c);

    setlocale(LC_ALL, "Russian");
    cout << "Точка максимума" << endl;
    cout << T.second << endl;

    cout << "Максимум" << endl;
    cout << T.first << endl;

    Matrix A1 = disjoin(perCol(A,1,3),3).first;

    cout << compactGauss((A1|b)).first << endl;
}
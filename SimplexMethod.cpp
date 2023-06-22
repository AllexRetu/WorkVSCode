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

    cout << "Значения по которым ищется минимум(по i из I): " << endl;
    cout << min << " ";
    for (int i = 1; i < I.size(); ++i)
    {
        double cur = M1[I[i]][0] / M2[I[i]][0];
        cout << cur << " ";
        if (cur < min)
        {
            min = cur;
            p = I[i];
        }
    }
    cout << endl << endl;
    return p;
}


pair<double, Matrix> ret(Matrix const & invB, Matrix const & b, Matrix const & c_, vector<int> const & indexX)  // функция расчитывает оптимальное решение(вывод для simplexMethod) по B,b и c
{
    size_t m = invB.size();

    Matrix XB = invB * b;   // считаем ненулевые компоненты решения
    size_t cSize = c_.at(0).size();
    Matrix X = createMatrix(cSize, 1);  // это все компоненты (пока с искусственными)

   for (int i = 0; i < m; ++i) // переставляем иксы на изначальное место
        X[indexX[i]][0] = XB[i][0];

    Matrix c = createMatrix(1, cSize);

    for (int j = 0; j < cSize; ++j) // переставляем компоненты c
        c[0][indexX[j]] = c_[0][j];

    bool isCorrect = true;
    int k = 0;
    while(isCorrect && k < m)
        isCorrect = (X[k++][0] == 0);
      
    if (isCorrect)
    {
        X = transpos(disjoin(transpos(X), m).second);
        c = disjoin(c,m).second;
    }

    cout << "Конец алгоритма." << "\n\n";

    return make_pair((c*X).at(0).at(0), X);
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
    

    
    // Начало алгоритма
    
    int l = 1;

    while (true)
    {   
        cout << l << "-ая итерация: " << endl << endl;

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

        if (invB == Matrix())
            return pair<double, Matrix>();

        int indexNegative = -1;
        Matrix d = cB * invB * N - cN;  // выражение, которое определяет увеличение какой компоненты XN увеличит целевую функцию

        cout << "Выражение перед XN (d):" << endl;
        cout << d << endl;

        
        // пункт 1
        for (int i = 0; i < d[0].size(); ++i)
        {   
            if (d[0][i] < 0) // если все компоненты этого выражения > 0 то мы нашли оптимальный результат (см стр.2 низ)
            {
                indexNegative = i; // запомнили индекс компоненты < 0, берется самая первая (ее будем изменять)
                break;
            }
        }
        if(indexNegative == -1)
            return ret(invB, b, c_, indexX);    // здесь надо будет еще убрать некоторые компоненты, потому что там есть искуственно введенные

        // пункт 2a
        
        Matrix colIndexNegativeN = createMatrix(m, 1);  // возьмем столбец из N соответствующий изменающейся координате XN
        for(int i = 0; i < m; ++i)
            colIndexNegativeN[i][0] = N[i][indexNegative];

        vector<int> I;  // индексы иксов, значения которых будет уменьшаться если увеличивать икс с индексом indexNegative
        for (int i = 0; i < m; ++i)
            if ((invB * colIndexNegativeN)[i][0] > 0) // если i-ая компонента > 0, то такой индекс добавляем в I
                I.push_back(i);

        if (I.empty()) // если таких индексов нет, то опт. результат = +infinity (см стр. 3)
        {
            cout << "Все компоненты XB будут неуменьшаться." << endl;
            cout << "Конец алгоритма." << "\n\n";

            return make_pair(INT_MAX, Matrix());
        }

        cout << "Номера компонент XB, которые будут уменьшаться(I): " << endl;

        for (int i = 0; i < I.size(); ++i)
            cout << I[i] + 1 << " ";
        cout << endl;

        
        // пункт 2b

        int p = min(invB, b, colIndexNegativeN, I); // запомнили индекс, на котором достигается минимум(при изменении компоненты indexNegative)

        // переход к новой базисной матрице (см стр. 4)

        A_ = perCol(A_, p, m + indexNegative);
        c_ = perCol(c_, p, m + indexNegative);

        swap(indexX[p],indexX[m + indexNegative]);  // запоминаем как переставили координаты(стольцы)

        cout << "Номер столбца из N который переставляем(j): " << indexNegative + 1 << endl;
        cout << "Номер столбца из B который переставляем(p): " << p + 1 << endl << endl;

        ++l;
    }

    
    return pair<double, Matrix>();
}

int main()
{
    Matrix A1
    {
        {1,2,3,3},  // A
        {3,10,1,4},
        {2,2,0,6},
        
    },
    b1
    {
        {1,},   // b
        {4,},
        {1,},

    },
    c1
    {
        {5,6,1,6},  // с

    };

    // система с результатом INT_MAX (+infinity)
    Matrix A2
    {
        {1,-1,1,1},  // A
        {1,-1,1,1},
        {1,-1,1,1},

    },
    b2
    {
        {1,},   // b
        {4,},
        {1,},

    },
    c2
    {
        {1,1,1,1},  // с

    };
    /*cout << det(A) << endl;
    cout << perRow(A,0,1) << endl;

    cout << inverse(A) << endl;
    cout << proof(A) << endl;

    cout << 5*(A*b)+b << endl;

    Matrix C = (A|b);

    cout << disjoin(C,3).first << endl;
    cout << disjoin(C,3).second << endl;*/


    // Первые условия (существует конечный максимум)

    cout << "Условия первой задачи: " << endl;
    cout << "A:" << endl;
    cout << A1 << endl;
    cout << "b:" << endl;
    cout << b1 << endl;
    cout << "c" << endl;
    cout << c1 << endl;
    
    auto T1 = simplexMethod(A1,b1,c1);

    
    if (T1.first != INT_MAX)
    {
        
    cout << "Точка максимума: " << endl;
    cout << T1.second;

    cout << "Максимум:" << endl;
    cout << T1.first << endl << endl;
    }
    else
        cout << "функция не ограничена, max = +бесконечность" << endl << endl;



    // Вторые условия (максимум = +беск)

    cout << "Условия второй задачи: " << endl;
    cout << "A:" << endl;
    cout << A2 << endl;
    cout << "b:" << endl;
    cout << b2 << endl;
    cout << "c" << endl;
    cout << c2 << endl;

    auto T2 = simplexMethod(A2,b2,c2);

    if (T2.first != INT_MAX)
    {
            
    cout << "Точка максимума: " << endl;
    cout << T2.second;

    cout << "Максимум:" << endl;
    cout << T2.first << endl;
    }
    else
        cout << "функция не ограничена, max = +бесконечность" << endl;
    

}

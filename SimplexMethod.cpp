#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

using Matrix = vector<vector<double>>;

void printMatrix(Matrix const & matrix, string name)
{
	cout << name << ": " << endl;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			cout << matrix[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';
}

void printMatrix(Matrix const & matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			cout << matrix[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';
}

Matrix product(Matrix const & matrix1, Matrix const & matrix2)
{
    size_t n = matrix2.at(0).size();
    size_t m = matrix1.size();
    size_t p = matrix1.at(0).size();
    if (p != matrix2.size()) // размеры не совместны
        return Matrix();
    Matrix product = Matrix(m, vector<double>(n));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < p; ++k)
                product[i][j] += matrix1[i][k]*matrix2[k][j];
    return product;
}

pair<Matrix, Matrix> compactGauss(Matrix const & A)
{
	size_t m = A.size();
    size_t n = A.at(0).size();
    if (n < m) // система переопределена
        return pair<Matrix,Matrix>();
	Matrix LU(m, vector<double>(n));
	
	for (int k = 0; k < m; ++k)
	{
		for (int i = k; i < m; ++i) // Вычисление B - нижнетреугольной
		{
			LU[i][k] = A[i][k];
			for (int i1 = 0; i1 < k; ++i1)
				LU[i][k] -= LU[i][i1]*LU[i1][k];
		}
		for (int j = k + 1; j < m; ++j) // Вычисление C - верхнетреугольной
		{
			LU[k][j] = A[k][j];
			for (int j1 = 0; j1 < k; ++j1)
				LU[k][j] -= LU[k][j1]*LU[j1][j];
			LU[k][j] = LU[k][j]/LU[k][k];
		}
	}

    if (n == m) // LU-разложение без решения системы
        return make_pair(Matrix(), LU);

	Matrix X(m, vector<double>(n-m));

    for (int j = m; j < n; ++j) // Просчитываем C для всех стобцов правых частей
    {
        for (int i = 0; i < m; ++i)
        {
            LU[i][j] = A[i][j];
			for (int k = 0; k < i; ++k)
				LU[i][j] -= LU[i][k]*LU[k][j];
			LU[i][j] = LU[i][j]/LU[i][i];
        }
    }

	for (int k = 0; k < n-m; ++k) // Вычисление решений
    {
        for (int i = m-1; i >= 0; --i)
        {
            X[i][k] = LU[i][m+k];
            for (int j = m-1; j > i; --j)
                X[i][k] -= X[j][k]*LU[i][j];
        }
    }

	return make_pair(X, LU);
}


Matrix proof(Matrix const & matrix)
{
    size_t n = matrix.size();
    auto T = compactGauss(matrix);
    Matrix L = Matrix(n, vector<double>(n,0));

    for (int j = 0; j < n; ++j)
        for (int i = j; i < n; ++i)
            L[i][j] = T.second[i][j];

    Matrix U = Matrix(n, vector<double>(n,0));

    for (int i = 0; i < n; ++i)
    {
        U[i][i] = 1;
        for (int j = i + 1; j < n; ++j)
            U[i][j] = T.second[i][j];
    }

    return product(L,U);
}

Matrix inverse(Matrix const & matrix)
{
    size_t n = matrix.size();

    if (n != matrix.at(0).size()) // матрица не квадратная(не хочу такую обращать)
        return Matrix();

    Matrix expand = Matrix(n, vector<double>(2*n));

    for (int i = 0; i < n; ++i) // припписываем единичную матрицу справа к той, которую обращаем
    {
        for (int j = 0; j < n; ++j)
        {
            expand[i][j] = matrix[i][j];
            expand[i][n+j] = i == j ? 1 : 0;
        }
    }
    
    return compactGauss(expand).first; // решаем n систем которые дают нам столбцы обратной матрицы
}                                                   // first - это матрица из столбцов-решений систем, т.е. это и есть обратная

double determinant(Matrix matrix)
{
    size_t n = matrix.size();
    if (n != matrix.at(0).size())
        return 1./0.; // матрица не квадратная
    Matrix LU = compactGauss(matrix).second;

    double det = 1;

    for (int i = 0; i < n; ++i)
        det *= LU[i][i];
    
    return det;
}

int main()
{
    Matrix A
    {
        {1,2,3,},
        {3,2,1,},
        {2,2,1,},
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

    
    //printMatrix(inverse(A));

    cout << determinant(A) << endl;
}
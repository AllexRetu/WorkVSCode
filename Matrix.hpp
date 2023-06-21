#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using Matrix = std::vector<std::vector<double>>;


void printMatrix(Matrix const & matrix, std::string name)
{
	std::cout << name << ": " << std::endl;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			std::cout << matrix[i][j] << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
}

void printMatrix(Matrix const & matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			std::cout << matrix[i][j] << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
}

void printMatrix(Matrix const & matrix, std::ostream & os)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			os << matrix[i][j] << " ";
		os << '\n';
	}
	os << '\n';
}

std::ostream & operator<<(std::ostream & os, Matrix const & matrix)
{
    printMatrix(matrix, os);
    return os;
}

Matrix product(Matrix const & matrix1, Matrix const & matrix2)
{
    size_t n = matrix2.at(0).size();
    size_t m = matrix1.size();
    size_t p = matrix1.at(0).size();
    if (p != matrix2.size()) // размеры не совместны
        return Matrix();
    Matrix product = Matrix(m, std::vector<double>(n));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < p; ++k)
                product[i][j] += matrix1[i][k]*matrix2[k][j];
    return product;
}

Matrix operator*(Matrix const & matrix1, Matrix const & matrix2)
{
    return product(matrix1, matrix2);
}

std::pair<Matrix, Matrix> compactGauss(Matrix const & A)
{
	size_t m = A.size();
    size_t n = A.at(0).size();
    if (n < m) // система переопределена 
        m = n; // возьмем верхную квадратную подматрицу
	Matrix LU(m, std::vector<double>(n));
	
	for (int k = 0; k < m; ++k)
	{
		for (int i = k; i < m; ++i) // вычисление B - нижнетреугольной
		{
			LU[i][k] = A[i][k];
			for (int i1 = 0; i1 < k; ++i1)
				LU[i][k] -= LU[i][i1]*LU[i1][k];
		}
        if (std::abs(LU[k][k]) <= 1e-12) // матрица системы вырожденная
                return std::pair<Matrix, Matrix>();
		for (int j = k + 1; j < m; ++j) // вычисление C - верхнетреугольной
		{
			LU[k][j] = A[k][j];
			for (int j1 = 0; j1 < k; ++j1)
				LU[k][j] -= LU[k][j1]*LU[j1][j];
			LU[k][j] = LU[k][j]/LU[k][k];
		}
	}

    if (n == m) // LU-разложение без решения системы
        return make_pair(Matrix(), LU);

	Matrix X(m, std::vector<double>(n-m));

    for (int j = m; j < n; ++j) // просчитываем C для всех стобцов правых частей
    {
        for (int i = 0; i < m; ++i)
        {
            LU[i][j] = A[i][j];
			for (int k = 0; k < i; ++k)
				LU[i][j] -= LU[i][k]*LU[k][j];
			LU[i][j] = LU[i][j]/LU[i][i];
        }
    }

	for (int k = 0; k < n-m; ++k) // вычисление решений
    {
        for (int i = m-1; i >= 0; --i)
        {
            X[i][k] = LU[i][m+k];
            for (int j = m-1; j > i; --j)
                X[i][k] -= LU[i][j]*X[j][k];
        }
    }

	return make_pair(X, LU);
}


Matrix proof(Matrix const & matrix) // функция проверяет правильность LU-разложения
{
    size_t n = matrix.size();
    auto T = compactGauss(matrix);
    Matrix L = Matrix(n, std::vector<double>(n,0));

    for (int j = 0; j < n; ++j)
        for (int i = j; i < n; ++i)
            L[i][j] = T.second[i][j];

    Matrix U = Matrix(n, std::vector<double>(n,0));

    for (int i = 0; i < n; ++i)
    {
        U[i][i] = 1;
        for (int j = i + 1; j < n; ++j)
            U[i][j] = T.second[i][j];
    }

    return product(L,U);
}

Matrix inverse(Matrix const & matrix) // считает обратную
{
    size_t n = matrix.size();

    if (n != matrix.at(0).size()) // матрица не квадратная(не хочу такую обращать)
        return Matrix();

    Matrix expand = Matrix(n, std::vector<double>(2*n));

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

double det(Matrix matrix) // считает определитель матрицы
{
    size_t n = matrix.size();
    if (n != matrix.at(0).size())
        return 1./0.; // матрица не квадратная
    Matrix LU = compactGauss(matrix).second;

    if (LU == Matrix())
        return 0;

    double det = 1;

    for (int i = 0; i < n; ++i)
        det *= LU[i][i];
    
    return det;
}

Matrix transpos(Matrix const & matrix) // транспонирование матриц
{
    size_t m = matrix.size();
    size_t n = matrix.at(0).size();

    Matrix transpos = Matrix(n, std::vector<double>(m));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            transpos[j][i] = matrix[i][j];

    return transpos;
}

Matrix join(Matrix const & matrix1, Matrix const & matrix2) // join(A,B) = (A|B)
{
    size_t m1 = matrix1.size();
    size_t m2 = matrix2.size();
    size_t n1 = matrix1.at(0).size();
    size_t n2 = matrix2.at(0).size();

    if (m1 != m2)
        return Matrix();
    
    Matrix joinMatrix = Matrix(m1, std::vector<double>(n1 + n2));
    
    for (int i = 0; i < m1; ++i)
    {
        for (int j = 0; j < n1; ++j)
            joinMatrix[i][j] = matrix1[i][j];
        for (int j = 0; j < n2; ++j)
            joinMatrix[i][j] = matrix2[i][j];
    }

    return joinMatrix;
}
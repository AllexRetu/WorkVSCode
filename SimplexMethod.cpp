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
    size_t cols = matrix2.at(0).size();
    size_t rows = matrix1.size();
    size_t p = matrix1.at(0).size();
    if (p != matrix2.size()) // размеры не совместны
        return Matrix();
    Matrix product = Matrix(rows, vector<double>(cols));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            for (int k = 0; k < p; ++k)
                product[i][j] += matrix1[i][k]*matrix2[k][j];
    return product;
}


int main()
{
    Matrix A
    {
        {1,2,3},
        {3,2,1},
        {2,2,0}
    },
    B
    {
        {1,0},
        {0,3},
        {1,2}
    };

    Matrix C = product(A,B);
    printMatrix(C);
}
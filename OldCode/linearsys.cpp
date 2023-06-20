#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define Row true
#define Col false

template <typename T>
T round(T x, int k)
{
	return round(pow(10,k)*x)*pow(10,-k);
}

template <typename T>
void printMatrix(vector<vector<T>> const & matrix, string name)
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

template <typename T>
void printMatrix(vector<vector<T>> const & matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.at(i).size(); ++j)
			cout << matrix[i][j] << " ";
		cout << '\n';
	}
	cout << '\n';
}

template <typename T>
void printVector(vector<T> const & vec, string name)
{
	cout << name << ": " << endl;
	for (int i = 0; i < vec.size(); ++i)
			cout << vec[i] << " ";
	cout << "\n\n";
}

template <typename T>
vector<vector<T>> roundMatrix(vector<vector<T>> const & A, int k)
{
	vector<vector<T>> B = A;
	for (int i = 0; i < B.size(); ++i)
		for (int j = 0; j < B.at(i).size(); ++j)
			B[i][j] = round(B[i][j], k);
	return B;
}

template <typename T, typename Round>
pair<vector<T>, vector<vector<T>>> compactGauss(vector<vector<T>> const & A, Round const & round, int p)
{
	int n = A.size();
	vector<vector<T>> LU(n, vector<T>(n+1));
	
	for (int k = 0; k < n; ++k)
	{
		for (int i = k; i < n; ++i)
		{
			LU[i][k] = round(A[i][k], p);
			for (int i1 = 0; i1 < k; ++i1)
				LU[i][k] -= round(LU[i][i1]*LU[i1][k], p);
		}
		for (int j = k + 1; j < n + 1; ++j)
		{
			LU[k][j] = round(A[k][j], p);
			for (int j1 = 0; j1 < k; ++j1)
				LU[k][j] -= round(LU[k][j1]*LU[j1][j], p);
			LU[k][j] = round(LU[k][j]/LU[k][k], p);
		}
	}

	vector<T> X(n);
	
	for (int i = n-1; i >= 0; --i)
	{
		X[i] = round(LU[i][n], p);
		for (int j = n-1; j > i; --j)
			X[i] -= round(X[j]*LU[i][j], p);
	}

	return make_pair(X, LU);
}

template <typename T>
void permutation(vector<vector<T>> & matrix, bool row, int n1, int n2)
{
	if (row)
		swap(matrix.at(n1), matrix.at(n2));
	else
		for (int i = 0; i < matrix.size(); ++i)
			swap(matrix.at(i).at(n1), matrix.at(i).at(n2));
}

template <typename T>
pair<int,int> maxElem(vector<vector<T>> const & A, int row)
{
	int im = row,jm = row;
	for (int i = row; i < A.size(); ++i)
		for (int j = row; j < A.at(i).size()-1; ++j)
			if (abs(A[i][j]) > abs(A[im][jm]))
			{
				im = i;
				jm = j;
			}
	return make_pair(im,jm);
}

template <typename T>
pair<int,int> maxElemRow(vector<vector<T>> const & A, int row)
{
	int im = row;
	for (int i = row; i < A.size(); ++i)
		if (abs(A[row][i]) > abs(A[row][im]))
		{
			im = i;
		}
	return make_pair(row,im);
}

template <typename T, typename Round>
vector<T> modGauss(vector<vector<T>> const & A, Round const & round, int p)
{
	int n = A.size();
	vector<vector<T>> B = A;
	vector<int> per(n);
	
	for (int k = 0; k < n; ++k)
	{	
		pair<int,int> maaxElem = maxElemRow(B, k);
		
		//permutation(B, Row, k, maaxElem.first);
		permutation(B, Col, k, maaxElem.second);
		per[k] = maaxElem.second;
		
		if (maaxElem.first != k || maaxElem.second != k)
		{
			cout << "Перестановка ";
			//cout << k << "-ой и " << maaxElem.first << "-ой строки, ";
			cout << k << "-ого и " << maaxElem.second << "-ого столбца" << endl;
			printMatrix(B);
		}
		
		for (int j = n; j >= k; --j)
			B[k][j] = round(B[k][j]/B[k][k], p);
		for (int i = n-1; i >= k+1; --i)
			for (int j = n; j >= k; --j)
				B[i][j] = round(B[i][j] - round(B[i][k]*B[k][j], p), p);
		printMatrix(B);
	}

	for (int k = n-1; k > 0; --k)
	{
		for (int i = k-1; i >= 0; --i)
		{
			B[i][n] = round(B[i][n] - round(B[i][k]*B[k][n], p) ,p);
			B[i][k] = 0;
		}
		printMatrix(B);
	}

	vector<T> X(n);
	
	for (int i = 0; i < n; ++i)
		X[i] = B[i][n];
	
	for (int k = n-1; k >=0; --k)
	{
		T tmp = X[k];
		X[k] = X[per[k]];
		X[per[k]] = tmp;
	}

	return X;
}

int main()
{
	vector<vector<double>> A
	{
	 {1.2345, 3.1415, 1, 7.9375},
	 {2.3456, 5.9690, 0, 14.2836},
	 {3.4567, 2.1828, 4.2, 9.5863}
	};

	cout << "Компактная схема Гаусса:\n\n";
	
	vector<vector<double>> A2, A4, A6;
	A2 = roundMatrix(A, 2);
	A4 = roundMatrix(A, 4);
	A6 = roundMatrix(A, 6);

	vector<double> X2, X4, X6;
	vector<vector<double>> LU2, LU4, LU6;

	auto Z2 = compactGauss(A2, round<double>, 2);
	auto Z4 = compactGauss(A4, round<double>, 4);
	auto Z6 = compactGauss(A6, round<double>, 6);
	
	X2 = Z2.first;
	X4 = Z4.first;
	X6 = Z6.first;
	
	LU2 = Z2.second;
	LU4 = Z4.second;
	LU6 = Z6.second;

	printMatrix(A2, "A2");
	printMatrix(LU2, "LU2");
	printVector(X2, "X2");

	printMatrix(A4, "A4");
	printMatrix(LU4, "LU4");
	printVector(X4, "X4");
	
	printMatrix(A6, "A6");
	printMatrix(LU6, "LU6");
	printVector(X6, "X6");

	//cout << "Метод Гаусса с выбором элемента по матрице:\n\n";
	cout << "Метод Гаусса с выбором элемента по строке:\n\n";

	printMatrix(A2, "A2");
	vector<double> Y2 = modGauss(A2, round<double>, 2);
	printVector(Y2, "Y2");

	printMatrix(A4, "A4");
	vector<double> Y4 = modGauss(A4, round<double>, 4);
	printVector(Y4, "Y4");
}
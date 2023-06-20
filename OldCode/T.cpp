#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template<typename Matrix>
void matrixAddEdge(Matrix & matrix, size_t u, size_t v)
{
	matrix.at(u).at(v) = 1;
	matrix.at(v).at(u) = 1;
}

template<typename Matrix, typename LinContainer>
void transformFromListToMatrix(LinContainer const & list, Matrix & matrix)
{
    for (size_t u = 0; u < size(list); ++u)
    {
        for (auto && v : list[u])
	{
		if (u < v)
		{
                	matrixAddEdge(matrix, u, v);
		}
        }
    }
}

template <typename Matrix>
void print_matrix(Matrix& m)
{
    for (size_t i = 0; i < size(m); ++i)
    {
        for (size_t j = 0; j < size(m[i]); ++j)
        {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

/*template<typename Matrix, typename LinContainer, class FunctionObject>
void transformFromMatrixToList(LinContainer & list, Matrix const & matrix, FunctionObject addEdge)
{
    for (size_t u = 0; u < size(matrix); ++u)
    {
        for (size_t v = 0; v <= u ; ++v)
        {
            addEdge(list, u, v);
        }
    }
}*/

int main()
{
    vector<vector<size_t>> list
    {
        {1,2,3},// 0
        {0},//     1
        {0,3},//   2
        {0,2}//    3
    };

    vector<vector<size_t>> matrix = vector(4, vector(4, size_t()));
    print_matrix(matrix);
    cout << "\n";
    
    transformFromListToMatrix(list, matrix);
    print_matrix(matrix);

    return 0;
}

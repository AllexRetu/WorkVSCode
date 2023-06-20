//B11
#include <iostream>
#include <vector>
using namespace std;


template <typename Matrix, typename Report>
void show_enumerating_edges(Matrix matrix, Report report)
{
	
    size_t k1 = matrix.size();
    size_t k2 = matrix.at(1).size();
    for (size_t j = 0; j < k2; j++)
    {
        for (size_t i = 0, v = size_t(-1); i < k1; i++)
        {
            if (matrix.at(i).at(j) == 1)
            {
                if (v == size_t(-1))
                	v = i;
                else
                {
                	report(v, i);
                	report(i, v);
                }
            }
        }
    }
}

void report(size_t u, size_t v)
{
	cout << u << " - " << v << endl;
}

int main() {
    vector<vector<int>> matrix
    {   
    	{1,0,0,1},
        {0,1,0,0},
        {0,1,1,0},
        {1,0,1,1}
    };
    
    show_enumerating_edges(matrix, report);
}
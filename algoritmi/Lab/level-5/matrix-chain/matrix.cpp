#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <climits>

using namespace std;

constexpr size_t nmax {100};
const int MAX = INT_MAX;

size_t number_of_digits(double n) {
	ostringstream strs;

	strs << n;
	return strs.str().size();
}

void print_matrix(int** M, size_t n, size_t m) {
	size_t max_len_per_column[nmax];

	for (size_t j = 0; j < m; ++j) {
		size_t max_len {};

		for (size_t i = 0; i < n; ++i)
			if (const auto num_length {number_of_digits(M[i][j])}; num_length > max_len)
				max_len = num_length;

		max_len_per_column[j] = max_len;
	}

	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < m; ++j)
			std::cout << (j == 0 ? "\n| " : "") << std::setw(max_len_per_column[j]) << M[i][j] << (j == m - 1 ? " |" : " ");

	std::cout << '\n';
}

int matrix_chain(int* p, int n) {
    int** matrix = new int*[n];
    for (int i=0; i<n; i++)
        matrix[i] = new int[n] {0};

    for (int i=1; i<n; i++)
        matrix[i][i] = 0;

    for (int t=2; t<n; t++) {
        for (int i=1; i<n-t+1; i++) {
            int j = i + t - 1;

            matrix[i][j] = MAX;

            for (int k=i; k<j; k++) {
                int q = matrix[i][k] + matrix[k+1][j] + p[i-1] * p[k] * p[j];
                if (q < matrix[i][j])   
                    matrix[i][j] = q;
            }
        }
    }

    //print_matrix(matrix, n, n);
    return matrix[1][n-1];
}

void runMatrix(ifstream& in, ofstream& out, int n) {
    int* p = new int[n+1];
    int dim, tmp;
    char c;

    // Since we have thath the number of rows is equal to the number of columns we take n-1 times the number of rows and the last time we get the number of columns
    for (int i=0; i<n; i++) {
        in >> c >> dim >> c >> tmp >> c;
        p[i] = dim;
    }
    p[n] = tmp;

    for (int i=0; i<=n; i++)
        cout << p[i] << " ";
    cout << endl;

    out << matrix_chain(p, n+1) << endl;

    delete[] p;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;

    for (int i=0; i<100; i++) {
        in >> n;
        
        runMatrix(in, out, n);
    }
}
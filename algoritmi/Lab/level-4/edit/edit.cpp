#include <iostream>
#include <fstream>

using namespace std;

/**
 * 1. Create a new matrix (n+1 x m+1)
 * 2. Initialize matrix[i][0] = i and matrix[0][j] = j
 * 3. Scan the matrix from 1 to i/j
 * 4. If s1[i-1] == s2[j-1] then matrix[i][j] = matrix[i-1][j-1]
 * 5. else matrix[i][j] = minimum of (matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1])
 * 6. return matrix[n][m]
 */

int** makeMatrix(int n, int m) {
    int** matrix = new int*[n+1];
    for (int i=0; i<=n; i++)
        matrix[i] = new int[m+1];

    for (int i=0; i<=n; i++)
        matrix[i][0] = i;

    for (int j=0; j<=m; j++)
        matrix[0][j] = j;

    return matrix;
}

int edit(int n, int m, string s1, string s2) {
    int** matrix = makeMatrix(n, m);

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (s1[i-1] == s2[j-1]) matrix[i][j] = matrix[i-1][j-1];
            else matrix[i][j] = 1 + min(matrix[i-1][j], min(matrix[i][j-1], matrix[i-1][j-1]));
        }
    }

    return matrix[n][m];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    string s1, s2;

    for (int i=0; i<100; i++) {
        in >> n >> m >> s1 >> s2;

        out << edit(n, m, s1, s2) << endl;
    }
}
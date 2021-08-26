#include <iostream>
#include <fstream>

using namespace std;

int lcs(string s1, string s2, int n, int m) {
    int** matrix = new int* [n+1];
    for(int i=0; i<=n; i++)
        matrix[i] = new int[m+1] {0};

    for(int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (s1[i-1] == s2[j-1])
                matrix[i][j] = matrix[i-1][j-1] + 1;
            else
                matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
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

        out << lcs(s1, s2, n, m) << endl;
    }
}
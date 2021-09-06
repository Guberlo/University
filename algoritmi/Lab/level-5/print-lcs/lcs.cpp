#include <iostream>
#include <fstream>

using namespace std;


char* print_lcs(int n, int m, string s1, string s2) {
    int** matrix = new int*[n+1];
    for (int i=0; i<=n; i++)
        matrix[i] = new int[m+1];

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (s1[i-1] == s2[j-1]) matrix[i][j] = matrix[i-1][j-1] + 1;
            else    matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
        }
    }

    int lcs_length = matrix[n][m];
    char* lcs = new char[lcs_length + 1];
    lcs[lcs_length] = '\0';

    int i = n;
    int j = m;

    while (i>0 && j>0) {
        if (s1[i-1] == s2[j-1]) {
            lcs[--lcs_length] = s1[i-1];
            i--; j--;
        }
        else if (matrix[i-1][j] > matrix[i][j-1])   i--;
        else j--;
    }

    return lcs;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    string s1, s2;

    for (int i=0; i<100; i++) {
        in >> n >> m >> s1 >> s2;

        out << print_lcs(n, m, s1, s2) << endl;
    }
}
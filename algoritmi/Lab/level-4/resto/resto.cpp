#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1001;

vector<int> makeCoinArray(ifstream &in, int n) {
    vector<int> coins;
    int tmp;

    for (int i=0; i<n; i++) {
        in >> tmp;
        coins.push_back(tmp);
    }

    sort(coins.begin(), coins.end());

    return coins;
}

int** initMatrix(int r, int n) {
    int** matrix = new int*[r+1];

    for (int i=0; i<=r; i++) {
        matrix[i] = new int[n];
        fill_n(matrix[i], n, MAX);
    }

    return matrix;
}

int resto(ifstream &in, int r, int n) {
    vector<int> coins = makeCoinArray(in, n);
    int** matrix = initMatrix(r, n);
    int* mins = new int[r+1];
    fill_n(mins, r+1, MAX);

    for (int i=0; i<=r; i++) {
        for (int j=0; j<n; j++) {
            if (i == coins[j])  matrix[i][j] = 1;
            else if (i > coins[j])  matrix[i][j] = mins[i - coins[j]] + 1;

            if (matrix[i][j] < mins[i]) mins[i] = matrix[i][j];
        }
    }

    return mins[r];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int r, n;

    for (int i=0; i<100; i++) {
        in >> r >> n;

        out << resto(in, r, n) << endl;
    }
}
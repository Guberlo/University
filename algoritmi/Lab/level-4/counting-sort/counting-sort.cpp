#include <iostream>
#include <fstream>

using namespace std;

int getMax(int* array, int size) {
    int max = array[0];
    for (int i=0; i<size; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

int getMin(int* array, int size) {
    int min = array[0];
    for (int i=0; i<size; i++)
        if (array[i] < min)
            min = array[i];
    return min;
}

void countingSort(int* A, int size, ofstream &out) {
    int min = getMin(A, size);
    int max = getMax(A, size);
    int range = (max - min)  + 1;
    int* B = new int[size];
    int* C = new int[range] {0};

    for (int i=0; i<size; i++)
        C[A[i] - min]++;

    for (int i=1; i<range; i++)
        C[i] += C[i-1];

    for (int i=size-1; i>=0; i--) {
        int index = C[A[i] - min] - 1;
        B[index] = A[i];
        C[A[i] - min]--;
    }

    for (int i=0; i<range; i++)
        out << C[i] << " ";

    for (int i=0; i<size; i++)
        out << B[i] << " ";

    out << endl;

    delete[] C;
    delete[] B;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;

    for (int i=0; i<100; i++) {
        in >> n;

        int* A = new int[n];
        for (int i=0; i<n; i++) 
            in >> A[i];
        
        countingSort(A, n, out);

        delete[] A;
    }
}
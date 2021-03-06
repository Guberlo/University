#include <iostream>

using namespace std;

const int MAX_DIM = 7;
const int MIN_INT = -1;
const int MAX_INT = 1000;

int getMax(int* array) {
    int max = MIN_INT;

    for (int i=0; i<MAX_DIM; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

int getMin(int* array) {
    int min = MAX_INT;

    for (int i=0; i<MAX_DIM; i++)
        if (array[i] < min)
            min = array[i];
    return min;
}

void countingSort(int* A, int* B, int* C, int m, int k) {
    for (int i=0; i<MAX_DIM; i++)
        C[A[i]-m]++;
    
    int j=0;
    for (int i=0; i<=k-m; i++) {
        for (int h=1; h<=C[i]; h++) {
            B[j] = i+m;
            j++;
        }
    }
}

void printArray(int* array, int dim) {
    for (int i=0; i<dim; i++)
        cout << array[i] << ", ";
    cout << endl;
} 

int main() {
    int A[MAX_DIM] = {34, 42, 53, 46, 36, 48, 43};
    int B[MAX_DIM] = {0};
    int k = getMax(A);
    int m = getMin(A);

    cout << k-m << endl;

    int C[(k-m)+1] = {0};

    countingSort(A, B, C, m, k);

    printArray(B, MAX_DIM);

    return 0;

}
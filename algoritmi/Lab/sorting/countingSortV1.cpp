#include <iostream>

using namespace std;

const int MAX_DIM = 7;
const int MIN_INT = -1;

int getMax(int* A) {
    int max = MIN_INT;

    for (int i=0; i<MAX_DIM; i++) {
        if (A[i] > max)
            max = A[i];
    }

    return max;
}

void countingSort(int* A, int* B, int* C, int k) { 
    for (int i=0; i<MAX_DIM; i++)
        C[A[i]]++;
    
    int j = 0;
    for (int i=0; i<=k; i++) {
        for (int h=1; h<=C[i]; h++) {
            B[j] = i;
            j++;
        }
    }
}

void printArray(int* array) {
    for (int i=0; i<MAX_DIM; i++)
        cout << array[i] << ", ";
    cout << endl;
}

int main() {
    int A[MAX_DIM] = {5,5,7,2,9,66,5};
    int B[MAX_DIM] = {0};
    int k = getMax(A); 
    int C[k + 1] = {0};

    countingSort(A, B, C, k);
    printArray(B);
    
    return 0;
}
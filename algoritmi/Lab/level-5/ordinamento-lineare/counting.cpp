#include <iostream>
#include <fstream>

using namespace std;

template <class T> int getMax(T* array, int n) {
    int max = 0;
    
    for (int i=1; i<n; i++)
        if (array[i] > array[max]) 
            max = i;
    
    return max;
}

template <class T> int getMin(T* array, int n) {
    int min = 0;

    for (int i=1; i<n; i++) 
        if (array[i] < array[min]) 
            min = i;

    return min;
}

template <class T> void countingSort(T* array, int n, ofstream& out, string type) {
    int max = (int) array[getMax(array, n)];
    int min = (int) array[getMin(array, n)];

    if (type == "double") {
        max = (int) (array[getMax(array, n)] * 10);
        min = (int) (array[getMin(array, n)] * 10);
    }

    int range = max - min + 1;
    T* sorted = new T[n];
    int* C = new int[range];
    fill_n(C, range, 0);

    for (int i=0; i<n; i++) {
        if (type == "double")
            C[(int)(array[i]*10) - min]++;
        else
            C[(int)array[i] - min]++;
    }

    for (int i=1; i<range; i++)
        C[i] += C[i-1];

    for (int i=0; i<n; i++) {
        if (type == "double") {
            sorted[C[(int)(array[i] * 10) - min] - 1] = array[i];
            C[(int)(array[i] * 10) - min]--;
        }
        else {
            sorted[C[(int)array[i] - min] - 1] = array[i];
            C[(int)array[i] - min]--;            
        }
    }

    for (int i=0; i<range; i++) 
        out << C[i] << " ";

    for (int i=0; i<n; i++)
        out << sorted[i] << " ";
    out << endl;
}

template <class T> void runCounting(ifstream& in, ofstream& out, int n, T type, string opType) {
    T* array = new T[n];
    
    for (int i=0; i<n; i++)
        in >> array[i];

    countingSort(array, n, out, opType);

    delete[] array;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "int" || type == "bool")
            runCounting(in, out, n, int(), "int");
        else if (type == "char")
            runCounting(in, out, n, char(), "char");
        else
            runCounting(in, out, n, double(), "double");
    }
}
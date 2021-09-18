#include <iostream>
#include <fstream>

using namespace std;

template <class T> int getMax(T* array, int n) {
    int max = 0;
    for (int i=1; i<n; i++)
        if (array[i] > array[max])
            max = i;
    return (int) array[max];
}

template <class T> int getMin(T* array, int n) {
    int min = 0;
    for (int i=1; i<n; i++)
        if (array[i] < array[min])
            min = i;
        
    return (int) array[min];
}

template <class T> T* makeArray(ifstream& in, int n, T type) {
    T* array = new T[n];
    for (int i=0; i<n; i++)
        in >> array[i];

    return array;
}

template <class T> void countingSort(ifstream& in, ofstream& out, int n, T type) {
    T* array = makeArray(in, n, T());
    int max = getMax(array, n);
    int min = getMin(array, n);
    int range = max - min + 1;
    cout << range << endl;
    T* B = new T[n];
    int* C = new int[range];
    for (int i=0; i<range; i++)
        C[i] = 0;

    for (int i=0; i<n; i++)
        C[(int)array[i] - min]++;

    for (int i=1; i<range; i++)
        C[i] += C[i-1];

    for (int i=n-1; i>=0; i--) {
        B[C[(int)array[i] - min] - 1] = array[i];
        C[(int)array[i] - min]--;
    }

    for (int i=0; i<range; i++)
        out << C[i] << " ";
    
    for (int i=0; i<n; i++)
        out << B[i] << " ";
    out << endl;
}

template <class T> void countingSortDouble(ifstream& in, ofstream& out, int n, T type) {
    T* array = makeArray(in, n, T());
    for (int i=0; i<n; i++)
        array[i] = array[i] * 10;
    int max = getMax(array, n);
    int min = getMin(array, n);
    int range = max - min + 1;
    cout << range << endl;
    T* B = new T[n];
    int* C = new int[range];
    for (int i=0; i<range; i++)
        C[i] = 0;

    for (int i=0; i<n; i++)
        C[(int)array[i] - min]++;

    for (int i=0; i<range; i++)
        C[i] += C[i-1];

    for (int i=n; i>=0; i--) {
        B[C[(int)array[i] - min] - 1] = array[i];
        C[(int)array[i] - min]--;
    }

    for (int i=0; i<range; i++)
        out << C[i] << " ";
    
    for (int i=0; i<n; i++)
        out << B[i] / 10.0 << " ";
    out << endl;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "char")
            countingSort(in, out, n, char());
        else if (type == "double")
            countingSortDouble(in, out, n, double());
        else if (type == "bool")
            countingSort(in, out, n, bool());
        else
            countingSort(in, out, n, int());
    }
}
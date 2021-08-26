#include <iostream>
#include <fstream>

using namespace std;

template <class T> class MaxHeap {
    private:
        T* queue;
        int size;
        int heapSize;
        int counter;

        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }
        int parent(int i) { return i >> 1; }

        void swap(int i, int j) { 
            T tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

        void heapify(int i) {
            this->counter++;
            int max = i;
            int l = left(i);
            int r = right(i);

            if (l <= heapSize && queue[l] > queue[max])
                max = l;
            if (r <= heapSize && queue[r] > queue[max])
                max = r;
            if (max != i) {
                swap(max, i);
                heapify(max);
            }
        }

    public:
        MaxHeap(int size) {
            this->size = size;
            this->heapSize = 0;
            this->counter = 0;
            this->queue = new T[size];
        }

        void insert(T k) {
            queue[++heapSize] = k;
            int i = heapSize;

            while(i > 1 && queue[i] > queue[parent(i)]) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

        T extractMax() {
            swap(1, heapSize--);
            if (heapSize > 0)
                heapify(1);
            return queue[heapSize + 1];
        }

        void print(ofstream &out) {
            out << counter << " ";
            for (int i=1; i<=heapSize; i++)
                out << queue[i] << " ";
            out << endl;
        }
};

template <class T> T convert(string k, T type) {
    if (is_same<T, char>::value)
        return k[0];
    return stod(k);
}   

template <class T> void insertMaxHeap(ifstream &in, ofstream& out, int n, T type) {
    MaxHeap<T>* heap = new MaxHeap<T>(n);
    string operation;
    T value;

    for (int i=0; i<n; i++) {
        in >> operation;
        cout << operation << endl;
        if (operation == "extract")
            heap->extractMax();
        else {
            value =convert(operation.substr(2), T());
            heap->insert(value); 
        }
    }
    heap->print(out);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "char")
            insertMaxHeap(in, out, n, char());
        else
            insertMaxHeap(in, out, n, double());
    }
}
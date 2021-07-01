#include <iostream>
#include <fstream>

using namespace std;

template <class T> class MinHeap {
    private:
        T* queue;
        int size;
        int heapSize;

        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }
        int parent(int i) { return i >> 1; }

        void swap(int i, int j) {
            T tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

    public: 
        MinHeap(int size) {
            this->heapSize = 0;
            this->size = size;
            this->queue = new T[size + 1];
        }

        MinHeap<T>* insert(T k) {
            this->queue[++heapSize] = k;
            int i = heapSize;

            while (i>1 && queue[i] < queue[parent(i)]) {
                swap(parent(i), i);
                i = parent(i);
            }
            return this;
        }

        void print(ofstream &out) {
            for (int i=1; i<=heapSize; i++)
                out << queue[i] << " ";
            out << endl;
        }
};

template <class T> void insertMinHeap(ifstream &in, ofstream &out, int n, T type) {
    MinHeap<T>* heap = new MinHeap<T>(n);
    T k;
    for (int i=1; i<=n; i++) {
        in >> k;
        heap->insert(k);
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
            insertMinHeap(in, out, n, char());
        else
            insertMinHeap(in, out, n, double());
    }
}
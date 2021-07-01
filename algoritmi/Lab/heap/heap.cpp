#include <iostream>
#include <fstream>

using namespace std;

template <class T> class MaxHeap {
    private:
        T* queue;
        int heapSize;

        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }
        int parent(int i) { return i >> 1; }

        void swap(int i, int j) {
            T tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

        void heapify(int i) {
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
        MaxHeap(T* queue, int heapSize) {
            this->queue = queue;
            this->heapSize = heapSize;
        }

        void buildMaxHeap() {
            for (int i=heapSize/2; i>0; i--)
                heapify(i);
        }

        void print(ofstream &out) {
            for (int i=1; i<=heapSize; i++)
                out << queue[i] << " ";
            out << endl;
        }

};

template <class T> void createMaxHeap(ifstream &in, ofstream &out, int n, T type) {
    T* array = new T[n + 1];
    for (int i=1; i<=n; i++)
        in >> array[i];

    MaxHeap<T>* heap = new MaxHeap<T>(array, n);
    heap->buildMaxHeap();
    heap->print(out);

    delete heap;
    delete[] array;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "char")
            createMaxHeap(in, out, n, char());
        else 
            createMaxHeap(in, out, n, double());
    }
}
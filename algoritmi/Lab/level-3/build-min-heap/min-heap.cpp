#include <iostream>
#include <fstream>

using namespace std;

template <class T> class MinHeap {
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
            int min = i;
            int l = left(i);
            int r = right(i);

            if (l <= heapSize && queue[l] < queue[min])
                min = l;
            if (r <= heapSize && queue[r] < queue[min])
                min = r;
            if (min != i) {
                swap(min, i);
                heapify(min);
            }
        }

    public: 
        MinHeap(T* queue, int heapSize) {
            this->queue = queue;
            this->heapSize = heapSize;
        }

        void buildMinHeap() {
            for (int i=heapSize/2; i>0; i--)
                heapify(i);
        }

        void print(ofstream &out) {
            for (int i=1; i<=heapSize; i++)
                out << queue[i] << " ";
            out << endl;
        }
};

template <class T> void createMinHeap(ifstream &in, ofstream &out, int n, T type) {
    T* array = new T[n+1];
    for (int i=1; i<=n; i++)
        in >> array[i];
    
    MinHeap<T>* heap = new MinHeap<T>(array, n);
    heap->buildMinHeap();
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
            createMinHeap(in, out, n, char());
        else 
            createMinHeap(in, out, n, double());
    }
}
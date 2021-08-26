/**
 * Esercizio davvero cringe: 
 * chiede il numero delle operazioni di heapify ed 
 * extract max ma vuole solo quelle di heapify
 */

#include <iostream>
#include <fstream>

using namespace std;

template <class T> class MaxHeap {
    private:
        T* queue;
        int size;
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

            if (l <= size && queue[l] > queue[max])
                max = l;
            if (r <= size && queue[r] > queue[max])
                max = r;
            if (max != i) {
                swap(max, i);
                heapify(max);
            }
        }

    public: 
        MaxHeap(T* queue, int size) {
            this->size = size;
            this->counter = 0;
            this->queue = queue;
        }

        void buildHeap() {
            for (int i=size/2; i>0; i--)
                heapify(i);
        }

        T extractMax() {
            swap(1, size--);
            if (size > 0)
                heapify(1);
            return queue[size + 1];
        }

        void print(ofstream &out) {
            out << this->counter << endl;
        }
};

template <class T> void insertMaxHeap(ifstream &in, ofstream &out, int n, T type) {
    T tmp[n + 1];
    for (int i=1; i<=n; i++) {
        in >> tmp[i];
    }

    MaxHeap<T>* heap = new MaxHeap(tmp, n);
    heap->buildHeap();

    for(int i=0; i<n; i++)
        heap->extractMax();

    heap->print(out);

    delete heap;
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
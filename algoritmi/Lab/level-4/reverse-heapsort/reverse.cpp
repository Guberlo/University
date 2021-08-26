#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Heap {
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
            counter++;
            int min = i;
            int l = left(i);
            int r = right(i);

            if (l <= heapSize && queue[l] < queue[min])
                min = l;
            if (r <= heapSize && queue[r] < queue[min])
                min = r;
            if (min != i) {
                swap(i, min);
                heapify(min);
            }
        }

        void extract() {
            swap(1, heapSize--);
            if (heapSize > 0)
                heapify(1);
        }

    public:
        Heap(int size, T* queue) {
            this->size = size;
            this->heapSize = size;
            this->counter = 0;
            this->queue = queue;
        }

        void buildHeap() {
            for (int i=size/2; i>0; i--)
                heapify(i);
        }

        void heapsort() {
            for (int i=0; i<size; i++)
                extract();
        }

        void print(ofstream &out) {
            out << counter << " ";
            for (int i=1; i<=size; i++)
                out << queue[i] << " ";
            out << endl;
        }
};

template <class T> void run(ifstream &in, ofstream &out, int n, T type) {
    T tmp[n+1];

    for (int i=1; i<=n; i++)
        in >> tmp[i];

    Heap<T>* heap = new Heap<T>(n, tmp);
    heap->buildHeap();
    heap->heapsort();
    heap->print(out);

    delete heap;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "char")
            run(in, out, n, char());
        else
            run(in, out, n, double());
    }
}
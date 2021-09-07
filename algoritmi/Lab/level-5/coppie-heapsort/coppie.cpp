#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Couple {
    private:
        T x;
        T y;

    public:
        Couple(T x, T y) {
            this->x = x;
            this->y = y;
        }

        T getX() { return x; }

        T getY() { return y; }

        friend bool operator<(const Couple<T>& a, const Couple<T>& b) {
            // cout << "a: " << a << "\tb: " << b << endl;
            if (a.x < b.x || a.x == b.x && a.y < b.y)
                return true;
            return false;
        }

        friend bool operator>(const Couple<T>& a, const Couple<T>& b) {
            // cout << "a: " << a << "\tb: " << a << endl;
            if (a.x > b.x || a.x == b.x && a.y > b.y)
                return true;
            return false;
        }

        friend bool operator==(const Couple<T>& a, const Couple<T>& b) {
            return a.x == b.x && a.y == b.y;
        };

        friend ostream& operator<<(ostream& os, const Couple& a) {
            os << "(" << a.x << " " << a.y << ")";
            return os;
        }

        Couple<T>& operator= (const Couple& a) {
            this->x = a.x;
            this->y = a.y;

            return *this;
        }

};

template <class T> class Heap {
    private:
        Couple<T>** queue;
        int size; 
        int heapSize;
        int counter;

        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }
        int parent(int i) { return i >> 1; }

        void swap(int i, int j) {
            Couple<T>* tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

        void heapify(int i) {
            counter++;
            int max = i;
            int l = left(i);
            int r = right(i);

            if (l<=heapSize && *queue[l] > *queue[max])
                max = l;
            if (r<=heapSize && *queue[r] > *queue[max])
                max = r;
            if (max != i) {
                swap(i, max);
                heapify(max);
            }
        }

        void extractMax() {
            swap(1, heapSize--);
            if (heapSize > 0)
                heapify(1);
        }

    public:
        Heap(Couple<T>** queue, int size) {
            this->size = size;
            this->heapSize = size;
            this->counter = 0;
            this->queue = queue;
        }

        /**
         * IMPORTANT: after some imprecation I found out that the heap
         * has to be filled via the build-heap method, otherwise the
         * heapify calls won't ever match
         */
        void insert(Couple<T>* value) {
            cout << "INSERT: " << *value << endl;
            queue[++heapSize] = value;
            int i = heapSize;

            while (i>1 && *queue[i] > *queue[parent(i)]) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

        void buildHeap() {
            for (int i=size/2; i>0; i--) {
                heapify(i);
            }
        }

        void heapSort() {
            for (int i=0; i<size; i++)
                extractMax();
        }

        void print(ofstream& out) {
            out << counter << " ";
            for (int i=1; i<=size; i++) 
                out << *queue[i] << " ";
            out << endl;
        }

        void consolePrint() {
            for (int i=1; i<=size; i++) 
                cout << *queue[i] << " ";
            cout << endl;
        }
};

template <class T> void runCouple(ifstream& in, ofstream& out, int n, T type, string opType) {
    Couple<T>** array = new Couple<T>*[n+1];
    string x, y;
    T a, b;

    for (int i=1; i<=n; i++) {
        in >> x >> y;
        // cout << "x: " << x << "\ty: " << y << endl; 
        if (opType == "double") {
            a = stod(x.substr(1));
            b = stod(y.substr(0, y.length() - 1));
        }
        else if (opType == "int") {
            a = stoi(x.substr(1));
            b = stoi(y.substr(0, y.length() - 1));
        }
        else {
            a = x.substr(1)[0];
            b = y.substr(0, y.length() - 1)[0];
        }

        cout << "x: " << x.substr(1) << " -> " << a << "\t" << "y: " << y.substr(0, y.length() - 1) << " -> " << b << endl;

        array[i] = new Couple<T>(a, b);
    }

    Heap<T>* heap = new Heap<T>(array, n);
    heap->buildHeap();
    heap->consolePrint();

    heap->heapSort();

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
            runCouple(in, out, n, char(), "char");
        else if (type == "int" || type == "bool")
            runCouple(in, out, n, int(), "int");
        else
            runCouple(in, out, n, double(), "double");
    }
}
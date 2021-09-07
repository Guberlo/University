#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Triplet {
    private:
        T x;
        T y;
        T z;

    public:
        Triplet<T>(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        T getX() { return x; }

        T getY() { return y; }

        T getZ() { return z; }

        friend bool operator<(const Triplet<T>& a, const Triplet<T>& b) {
            if ( a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z) )
                return true;
            return false;
        }

        friend bool operator>(const Triplet<T>& a, const Triplet<T>& b) {
            if ( a.x > b.x || (a.x == b.x && a.y > b.y) || (a.x == b.x && a.y == b.y && a.z > b.z) )
                return true;
            return false;
        }

        friend bool operator==(const Triplet<T>& a, const Triplet<T>& b) {
            return (a.x == b.x && a.y == b.y && a.z == b.z);
        }

        friend ostream& operator<<(ostream& os, const Triplet<T>& a) {
            return os << "(" << a.x << " " << a.y << " " << a.z << ")";
        }

        Triplet<T>& operator=(const Triplet<T>& a) {
            this->x = a.x;
            this->y = a.y;
            this->z = a.z;
        }
};

template <class T> class Heap {
    private:
        int size;
        int heapSize;
        int counter;
        Triplet<T>** queue;

        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1) | 1; }
        int parent(int i) { return i >> 1; }

        void swap(int i, int j) {
            Triplet<T>* tmp = queue[i];
            queue[i] = queue[j];
            queue[j] = tmp;
        }

        void heapify(int i) {
            counter++;
            int max = i;
            int l = left(i);
            int r = right(i);
            
            if (l <= heapSize && *queue[l] > *queue[max])
                max = l;
            if (r <= heapSize && *queue[r] > *queue[max])
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
        Heap(Triplet<T>** queue, int size) {
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
                extractMax();
        }

        void print(ofstream& out) {
            out << counter << " ";
            for (int i=1; i<=size; i++)
                out << *queue[i] << " ";
            out << endl;
        }

        ~Heap() {
            delete[] queue;
        }
};

template <class T> void runTriplets(ifstream& in, ofstream& out, int n, T type, string opType) {
    Triplet<T>** triplets = new Triplet<T>* [n+1];
    string a, b, c;
    T x, y, z;

    for (int i=1; i<=n; i++) {
        in >> a >> b >> c;

        if (opType == "char") {
            x = a.substr(1)[0];
            y = b[0];
            z = c.substr(0, c.length() - 1)[0];
        }
        else if (opType == "int") {
            x = stoi(a.substr(1));
            y = stoi(b);
            z = stoi(c.substr(0, c.length() - 1));
        }
        else {
            x = stod(a.substr(1));
            y = stod(b);
            z = stod(c.substr(0, c.length() - 1)); 
        }

        cout << "a: " << a << " -> " << x << "   b: " << b << " -> " << y << "   c: " << c << " -> " << z << endl;

        triplets[i] = new Triplet<T>(x, y, z);
    }

    Heap<T>* heap = new Heap<T>(triplets, n);
    heap->buildHeap();
    heap->heapsort();

    heap->print(out);
    heap->~Heap();
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int n;

    for (int i=0; i<100; i++) {
        in >> type >> n;

        if (type == "int" || type == "bool")
            runTriplets(in, out, n, int(), "int");
        else if (type == "char")
            runTriplets(in, out, n, char(), "char");
        else
            runTriplets(in, out, n, double(), "double");
    }
}
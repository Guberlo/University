#include <iostream>
#include <fstream>
#include <math.h>
#include <list>

using namespace std;

template <class T> class HashTable {
    private:
        int size;
        double c;
        list<T>* table;

        int hashMult(T k) {
            double y = k * c;
            return size * ( y - (int) y );
        }

    public:
        HashTable(int size) {
            this->size = size;
            this->c = 0.61803;
            this->table = new list<T>[size];
        }

        void insert(T k) {
            int index = hashMult(k);
            table[index].push_back(k);
        }

        void print(ofstream &out) {
            for (int i=0; i<size; i++) {
                int counter = 0;
                for (auto el : table[i])
                    counter++;
                out << counter << " ";
            }
            out << endl;
        }
};

template <class T> void insertHash(ifstream &in, ofstream &out, int size, int n, T type) {
    HashTable<T>* hashTable = new HashTable<T>(size);
    T value;
    for (int i=0; i<n; i++) {
        in >> value;
        hashTable->insert(value);
    }
    hashTable->print(out);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    string type;
    int size, n;

    for (int i=0; i<100; i++) {
        in >> type >> size >> n;

        if (type == "char")
            insertHash(in, out, size, n, char());
        else
            insertHash(in, out, size, n, double());
    }
}
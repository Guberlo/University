#include <iostream>
#include <fstream>

using namespace std;

class Couple {
    private:
        int x;
        int y;

    public:
        Couple(int x, int y) {
            this->x = x;
            this->y = y;
        }

        int getX() { return x; }

        int getY() { return y; }

        friend ostream& operator<<(ostream& os, const Couple& a) {
            return os << "(" << a.x/10.0 << " " << a.y/10.0 << ")";
        }

        friend bool operator<(const Couple& a, const Couple& b) {
            return a.x < b.x;
        }

        friend bool operator>(const Couple& a, const Couple& b) {
            return a.x > b.x;
        }
};

int getMax(Couple** array, int n) {
    int max = 0;

    for (int i=0; i<n; i++) 
        if (*array[i] > *array[max])
            max = i;

    return array[max]->getX();
}

int getMin(Couple** array, int n) {
    int min = 0;

    for (int i=0; i<n; i++)
        if (*array[i] < *array[min])
            min = i;

    return array[min]->getX();
}

void countingSort(ofstream& out, Couple** array, int n) {
    int max = getMax(array, n);
    int min = getMin(array, n);
    int range = max - min + 1;
    Couple** B = new Couple*[n];
    int* C = new int[range];
    
    for (int i=0; i<range; i++)
        C[i] = 0;

    for (int i=0; i<n; i++)
        C[array[i]->getX() - min]++;

    for (int i=1; i<range; i++)
        C[i] += C[i-1];

    for (int i=n-1; i>=0; i--) {
        B[C[array[i]->getX() - min] - 1] = array[i];
        C[array[i]->getX() - min]--;
    }

    for (int i=0; i<range; i++)
        out << C[i] << " ";

    for (int i=0; i<n; i++) 
        out << *B[i] << " ";
    out << endl;

    for (int i=0; i<n; i++)
        delete B[i];

    delete[] B;
    delete[] C;
}

void runCounting(ifstream& in, ofstream& out, int n) {
    Couple** array = new Couple*[n];
    Couple** B = new Couple*[n];
    char c;
    double x, y;

    for (int i=0; i<n; i++) {
        in >> c >> x >> y >> c;
        array[i] = new Couple(x*10, y*10);
        cout << "x: " << x << " y: " << y << "array[i]: " << *array[i] << endl;
    }

    countingSort(out, array, n);
    
    delete[] array;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;

    for (int i=0; i<100; i++) {
        in >> n;

        runCounting(in, out, n);
    }
}
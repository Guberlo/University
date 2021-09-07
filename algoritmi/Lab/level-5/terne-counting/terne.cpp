#include <iostream>
#include <fstream>

using namespace std;

class Triplet {
    private:
        int x;
        int y;
        int z;

    public:
        Triplet(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        int getX() { return x; }

        int getY() { return y; }

        int getZ() { return z; }

        friend bool operator<(const Triplet& a, const Triplet& b) {
            return a.x < b.x;
        }

        friend bool operator>(const Triplet& a, const Triplet& b) {
            return a.x > b.x;
        }

        friend ostream& operator<<(ostream& os, const Triplet& a) {
            return os << "(" << a.x / 10.0 << " " << a.y / 10.0 << " " << a.z / 10.0 << ")"; 
        }
};

Triplet** makeArray(ifstream& in, int n) {
    Triplet** array = new Triplet*[n];
    string a, b, c;
    double x, y, z;

    for (int i=0; i<n; i++) {
        in >> a >> b >> c;

        cout << "a: " << a << " b: " << b << " c: " << c << endl;

        // Multiply by 10 in order to get an integer
        x = stod(a.substr(1)) * 10;
        y = stod(b) * 10;
        z = stod(c.substr(0, c.length() - 1)) * 10;

        cout <<  "x: " << x << " y: " << y << " z: " << z << endl;

        array[i] = new Triplet(x, y, z);
    }

    return array;
}

int getMin(Triplet** array, int n) {
    int min = 0;

    for (int i=0; i<n; i++)
        if (*array[i] < *array[min])
            min = i;

    return array[min]->getX();
}

int getMax(Triplet** array, int n) {
    int max = 0;

    for (int i=0; i<n; i++)
        if (*array[i] > *array[max])
            max = i;

    return array[max]->getX();
}

void printResult(ofstream& out, Triplet** B, int n, int* C, int range) {
    for (int i=0; i<range; i++)
        out << C[i] << " ";

    for (int i=0; i<n; i++)
        out << *B[i] << " ";
    out << endl;
}

void countingSort(ofstream& out, Triplet** array, int n) {
    int min = getMin(array, n);
    int max = getMax(array, n);
    int range = max - min + 1;
    Triplet** B = new Triplet*[n];
    int* C = new int[range];

    cout << "max: " << max << " min: " << min << endl;

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

    printResult(out, B, n, C, range);

    for (int i=0; i<n; i++)
        delete B[i];
    
    delete[] B;
    delete[] C;
}

void runCounting(ifstream& in, ofstream& out, int n) {
    Triplet** array = makeArray(in, n);

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
#include <iostream>
#include <fstream>

using namespace std;

const int INF = 100000;

template <class T> class Graph {
    private:
        T* nodes;
        int size;
        int** weight;
        int* d;

        int findNode(T key) {
            for (int i=0; i<size; i++)
                if (nodes[i] == key)    return i;
            return -1;
        }

        void relax(int i, int j) {
            if (d[j] > d[i] + weight[i][j]) d[j] = d[i] + weight[i][j];
        }

    public:
        Graph(int dim) {
            this->size = 0;
            nodes = new T[dim];
            d = new int[dim];

            weight = new int*[dim];
            for (int i=0; i<dim; i++) {
                weight[i] = new int[dim];

                for (int j=0; j<dim; j++)
                    weight[i][j] = INF;
            }
        } 

        void addNode(T key) {
            nodes[size++] = key;
        }

        void addEdge(T a, T b, int w) {
            int i = findNode(a);
            int j = findNode(b);

            weight[i][j] = w;
        }

        void initializeSource(int src) {
            for (int i=0; i<size; i++)
                d[i]= INF;
            d[src] = 0;
        }

        bool bellmanFord(T source, T destination) {
            int src = findNode(source);
            int dst = findNode(destination);

            cout << "Initialize src" << endl;
            initializeSource(src);

            cout << "First relax" << endl;
            for (int k=0; k<size-1; k++) {
                for (int i=0; i<size; i++) {
                    for (int j=0; j<size; j++)
                        if (weight[i][j] != INF)
                            relax(i, j);
                }
            }

            cout << "Second relax" << endl;
            for (int i=0; i<size; i++)
                for (int j=0; j<size; j++)
                    if (d[j] != INF && d[j] > d[i] + weight[i][j])
                        return false;
            
            return true;
        }

        int getSP(T dest) {
            return d[findNode(dest)];
        }
};

template <class T> void runBellman(ifstream& in, ofstream& out, int n, int m, T type) {
    Graph<T>* graph = new Graph<T>(n);
    T tmp, a, b, src, dest;
    char c;

    for (int i=0; i<n; i++) {
        in >> tmp;
        cout << "add node: " << tmp << endl;
        graph->addNode(tmp);
    }

    for (int i=0; i<m; i++) {
        in >> c >> a >> b >> tmp >> c;
        cout << "add edge: (" << a << " " << b << " " << tmp << ")" << endl;
        graph->addEdge(a, b, tmp);
    }

    in >> src >> dest;
    cout << "src: " << src << "dst: " << dest << endl;
    if (!graph->bellmanFord(src, dest))
        out << "undef." << endl;
    else {
        if (graph->getSP(dest) == INF)
            out << "inf." << endl;
        else
            out << graph->getSP(dest) << endl;
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    string type;

    for (int i=0; i<100; i++) {
        in >> n >> m >> type;
        if (type == "int")
            runBellman(in, out, n, m, int());
        else
            runBellman(in, out, n, m, double());
    }
}
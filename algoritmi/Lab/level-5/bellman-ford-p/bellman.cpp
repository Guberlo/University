#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const int INF = 10000001;

template <class T> class Graph {
    private:
        T* nodes;
        int size;
        int** weights;
        int* d;

        int findNode(T key) {
            for (int i=0; i<size; i++)
                if (nodes[i] == key)    return i;
            return -1;
        }

        void relax(int i, int j) {
            if (d[j] > d[i] + weights[i][j])
                d[j] = d[i] + weights[i][j];
        }

    public:
        Graph(int size) {
            this->size = size;
            d = new int[size];

            nodes = new T[size];
            for (int i=0; i<size; i++)
                nodes[i] = i;
            
            weights = new int*[size];
            for (int i=0; i<size; i++) {
                weights[i] = new int[size];
                for (int j=0; j<size; j++)
                    weights[i][j] = INF;
            }
        }

        void addNode(T key) {
            nodes[size++] = key;
        }

        void addEdge(T a, T b, int w) {
            int i = findNode(a);
            int j = findNode(b);
            
            weights[i][j] = w;
        }

        void initializeSource(int src) {
            for (int i=0; i<size; i++)
                d[i] = INF;
            d[src] = 0;
        }

        int bellmanFord(T source, T destination, int k) {
            int src = findNode(source);
            int dst = findNode(destination);

            initializeSource(src);

            for (int l=0; l<k; l++) 
                for (int i=0; i<size; i++)
                    for (int j=0; j<size; j++)
                        if (weights[i][j] != INF)
                            relax(i, j);

            return d[dst];
        }
};

void runBellman(ifstream& in, ofstream& out, int n, int m, int k) {
    Graph<int>* graph = new Graph<int>(n);
    int w, a, b, src, dest;
    char c;

    for (int i=0; i<m; i++) {
        in >> c >> a >> b >> w >> c;
        graph->addEdge(a, b, w);
    }

    in >> src >> dest;

    int res = graph->bellmanFord(src, dest, k);

    if (res == INF) out << "inf." << endl;
    else    out << res << endl;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m, k;

    for (int i=0; i<100; i++) {
        in >> n >> m >> k;

        runBellman(in, out, n, m, k);
    }
}
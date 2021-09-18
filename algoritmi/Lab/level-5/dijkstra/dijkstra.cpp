#include <iostream>
#include <fstream>

using namespace std;

const int INF = 1000000;

template <class T> class Graph {
    private:
        T* nodes;
        int size;
        int** weights;
        int* d;
        bool* relaxed;

        int findNode(T key) {
            for (int i=0; i<size; i++)
                if (nodes[i] == key)    return i;
            return -1;
        }

        void relax(int i, int j) {
            if (d[j] < d[i] + weights[i][j])    
                d[j] = d[i] + weights[i][j];
        }

        void initializeSource(int src) {
            for (int i=0; i<size; i++)
                d[i] = INF;
            d[src] = 0;
        }

    public:
        Graph(int dim) {
            size = 0;
            nodes = new T[dim];
            d = new int[dim];

            relaxed = new bool[dim];
            for (int i=0; i<dim; i++)
                relaxed[i] = false;

            weights = new int*[dim];
            for (int i=0; i<dim; i++) {
                weights[i] = new int[dim];
                for (int j=0; j<dim; j++)
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

        int dijkstra(T source, T destination) {
            int src = findNode(source);
            int dest = findNode(destination);

            initializeSource(src);

            int extracted = src;

            for (int i=0; i<size; i++) {
                relaxed[extracted] = true;
                for (int j=0; j<size; j++) 
                    if (d[j] > d[extracted] + weights[extracted][j])
                        d[j] = d[extracted] + weights[extracted][j];

                int min = INF;
                for (int j=0; j<size; j++) {
                    if (d[j] < min && !relaxed[j]) {
                        extracted = j;
                        min = d[j];
                    }
                }
            }

            return d[dest];
        }

        ~Graph() {
            for (int i=0; i<size; i++)
                delete weights[i];
            delete[] weights;

            delete[] d;
            delete[] nodes;
            delete[] relaxed;
        }
};

template <class T> void runDijkstra(ifstream& in, ofstream& out, int n, int m, T type) {
    Graph<T>* graph = new Graph<T>(n);
    T tmp, a, b, src, dest;
    char c;

    for (int i=0; i<n; i++) {
        in >> tmp;
        graph->addNode(tmp);
    }

    for (int i=0; i<m; i++) {
        in >> c >> a >> b >> tmp >> c;
        graph->addEdge(a, b, tmp);
    }

    in >> src >> dest;

    int res = graph->dijkstra(src, dest);

    if (res < INF)
        out << res << endl;
    else
        out << "inf." << endl;

    delete graph;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    string type;

    for (int i=0; i<100; i++) {
        in >> n >> m >> type;

        if (type == "int")
            runDijkstra(in, out, n, m, int());
        else
            runDijkstra(in, out, n, m, double());
    }
}
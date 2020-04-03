#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#define WHITE 0
#define GRAY 1
#define BLACK 2;

using namespace std;

template <class H> class Vector{
private:
  H* nodes;
  int n, length;

public:
  Vector(){
    length = 200;
    n = 0;
    nodes = new H[length];
  }

  void addNode(H key){
    nodes[n++] = key;
  }

  int findIndex(H key){
    for(int i=0; i<n; i++){
      if(nodes[i] == key) return i;
    }
    return -1;
  }

  H findKey(int i) { return nodes[i]; }
};

template <class H> class Graph{
private:
  Vector<H>* nodes;
  int n;
  int** mat;
  int* color;
  int forwardEdge;

public:
  Graph(int n){
    this->n = n;
    nodes = new Vector<H>();
    mat = new int*[n];
    for(int i=0; i<n; i++)  mat[i] = new int[n];

    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++)
        mat[i][j] = 0;
    }

    color = new int[n];
    forwardEdge = 0;
  }

  Graph<H>* addNode(H key){
    nodes->addNode(key);
    return this;
  }

  Graph<H>* addEdge(H x, H y){
    int i = nodes->findIndex(x);
    int j = nodes->findIndex(y);

    mat[i][j] = 1;
    return this;
  }

  int DFSVisit(int i){
    color[i] = GRAY;
    for(int j=0; j<n; j++){
      if(mat[i][j]){
        if(!color[j]) DFSVisit(j);
        if(color[j] == GRAY)  forwardEdge++;
      }
    }
    color[i] = BLACK;
    return forwardEdge;
  }

  int DFS(ofstream& out){
    int has_cycle = 0;

    for(int i=0; i<n; i++)  color[i] = WHITE;

    for(int i=0; i<n; i++){
      if(color[i] == WHITE) has_cycle = DFSVisit(i);
    }

    out << has_cycle << endl;
  }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");


    while(!in.eof()){
        int n; in >> n; //number of nodes
        int ne; in >> ne; //number of edges;

        string type; in >> type;

        if(type == "int"){
            Graph<int>* g = new Graph<int>(n);
            int val, x, y;

            for(int i=0; i<n; i++){
                in >> val;
                g->addNode(val);
            }

            for(int i=0; i<ne; i++){
                string k; in >> k;
                string l; in >> l;

                stringstream buffer1(k.substr(1));
                stringstream buffer2(l.substr(0, l.size()-1));
                buffer1 >> x;
                buffer2 >> y;
                g->addEdge(x, y);
            }

            g->DFS(out);
        }//end int
                if(type == "char"){
            Graph<char>* g = new Graph<char>(n);
            char val, x, y;

            for(int i=0; i<n; i++){
                in >> val;
                g->addNode(val);
            }

            for(int i=0; i<ne; i++){
                string k; in >> k;
                string l; in >> l;

                stringstream buffer1(k.substr(1));
                stringstream buffer2(l.substr(0, l.size()-1));
                buffer1 >> x;
                buffer2 >> y;
                g->addEdge(x, y);
            }

            g->DFS(out);
        }//end int
                if(type == "double"){
            Graph<double>* g = new Graph<double>(n);
            double val, x, y;

            for(int i=0; i<n; i++){
                in >> val;
                g->addNode(val);
            }

            for(int i=0; i<ne; i++){
                string k; in >> k;
                string l; in >> l;

                stringstream buffer1(k.substr(1));
                stringstream buffer2(l.substr(0, l.size()-1));
                buffer1 >> x;
                buffer2 >> y;
                g->addEdge(x, y);
            }

            g->DFS(out);
        }//end int
    }
}

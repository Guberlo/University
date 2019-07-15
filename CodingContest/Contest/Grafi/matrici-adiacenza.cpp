#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

template <class H> class Vector{
private:
  H* nodes;
  int n;
  int lenght;

public:
  Vector(int length){
    this->lenght = length;
    n = 0;
    nodes = new H[length];
  }

  void addNode(H node){
    nodes[n] = node;
    n++;
    sort(nodes, nodes+n);
  }

  H findKey(int i){
    return nodes[i];
  }

  int findIndex(H node){
    for(int i=0; i<n ; i++){
      if(nodes[i] == node)
      return i;
    }
    return -1;
  }
};

template <class H> class Graph{
private:
  Vector<H>* nodes;
  int n; //number of nodes
  int **mat;

public:
  Graph(int n){
    nodes = new Vector<H>(n);
    mat = new int*[n];
    for(int i=0; i<n; i++)
      mat[i] = new int[n];

    //inizializzo gli edge a 0
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++)
      mat[i][j] = 0;
    }

    this->n = n;
  }

  Graph<H>* addNode(H key){
    nodes->addNode(key);
    return this;
  }

  Graph<H>* addEdge(H x, H y){
    int i = findIndex(x);
    int j = findIndex(y);

    mat[i][j] = 1;
    return this;
  }

  void print(ofstream &out){
    for(int i=0; i<n; i++){
      out << "(";
      H key = findKey(i);
      out << key;
      for(int j=0; j<n; j++){
        if(mat[i][j] == 1){
          H y = findKey(j);
          out << " " << y;
        }
      }
      out << ") ";
    }
  }

  void printMat(){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        cout << mat[i][j] << " ";
      }
      cout << endl;
    }
  }

};//end Grafi


int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    int n; in >> n; //number of nodes
    int e; in >> e; //number of edges

    string type; in >> type;

    if(type == "int"){
      Graph<int>* g = new Graph<int>(n);
      int node, x, y;
      for(int i=0; i<n; i++){
        input >> node;
        g->addNode(node);
      }
    }
  }
}

#include <iostream>
using namespace std;

template<class H> class NodeSet {
private:
    H** v;
    int len, n;
public:
    NodeSet(int len=100) {
        this->len = len;
        n = 0;
        v = new H*[len];
        for(int i=0; i<len; i++) v[i] = NULL;
    }
    int insert(H x) {
        if(n>=len) return -1;
        v[n] = new H(x);
        n++;
        return n-1;
    }
    int findIndex(H x) {
        for(int i=0; i<n; i++)
            if(*v[i]==x) return i;
        return -1;
    }
    H* findKey(int i) {
        if(i<0 || i>=n) return NULL;
        return v[i];
    }
    int search(H x) {
        if(findIndex(x)==-1) return 0;
        return 1;
    }
    int size() {return n;}
};

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -1

template <class H> class Stack {
private:
    H **v;
    int top;
    int len;
public:
    Stack(int len = 100) {
        this->len = len;
        top = 0;
        v = new H*[len];
    }
    int isEmpty() { return top == 0; }
    void push(H x) { v[top++] = new H(x); }
    H* pop() {
        if(isEmpty()) return NULL;
        return v[--top];
    }
};


template <class H> class Queue {
private:
    H **v;
    int head, tail;
    int len;
public:
    Queue(int len = 100) {
        this->len = len;
        head = tail = 0;
        v = new H*[len];
    }
    int isEmpty() { return head==tail; }
    void enqueue(H x) { v[tail++] = new H(x); }
    H* dequeue() {
        if(isEmpty()) return NULL;
        return v[head++];
    }
};

template<class H> class Graph {
private:
    NodeSet<H> *key;
    int nedges;
    bool** m;
    int *color, *p, *d, *f;
    int t;
    Stack<H> *s;
public:
    Graph(int n=100) {
        key = new NodeSet<H>(n);
        m = new bool*[n];
        for(int i=0; i<n; i++) {
            m[i] = new bool[n];
            for(int j=0; j<n; j++) m[i][j] = 0;
        }
        nedges = 0;
        color = new int[n];
        p = new int[n];
        d = new int[n];
        f = new int[n];
        s = new Stack<H>(n);
        for(int i=0; i<n; i++) d[i] = f[i] = INF;
    }
    int insertNode(H x) {
        if(key->search(x)) return -1;
        return key->insert(x);
    }
    int insertEdge(H x, H y) {
        int i = key->findIndex(x);
        int j = key->findIndex(y);
        if(i==-1 || j==-1) return 0;
        m[i][j] = 1;
        //m[j][i] = 1; //per un grafo non orientato
        nedges++;
        return 1;
    }
    int findKey(H x) { return key->search(x);}
    int findEdges(H x, H y) {
        int i = key->findIndex(x);
        int j = key->findIndex(y);
        if(i==-1 || j==-1) return 0;
        return m[i][j];
    }
    void print() {
        for(int i=0; i<key->size(); i++) {
            cout << "[" << *key->findKey(i) << "] --> ";
            for(int j=0; j<key->size(); j++) {
                if(m[i][j]) cout << *key->findKey(j) << " --> ";
            }
            cout << "||" << endl;
        }
    }

    void bfs(H s) {
        //inizializzazione
        for(int i=0; i<key->size(); i++) {
            color[i] = WHITE;
            p[i] = -1;
            d[i] = INF;
        }
        //ciclo principale
        int i = key->findIndex(s);
        Queue<int>* q = new Queue<int>(key->size());
        q->enqueue(i);
        color[i] = GRAY;
        d[i] = 0;
        while(!q->isEmpty()) {
            i = *q->dequeue();
            for(int j=0; j<key->size(); j++) {
                if(m[i][j] && color[j]==WHITE) {
                    color[j]=GRAY;
                    q->enqueue(j);
                    d[j] = d[i]+1;
                    p[j] = i;
                }
            }
            color[i] = BLACK;
        }
    }

    int getDistance(H x, H y) {
        int i = key->findIndex(x);
        int j = key->findIndex(y);
        if(i==-1 || j==-1) return INF;
        if(d[i]!=0) bfs(x);
        return d[j];
    }

    void printPath(int j) {
        if(p[j]!=-1) {
            printPath(p[j]);
            cout << " --> ";
        }
        cout << *key->findKey(j);
    }


    void getPath(H x, H y) {
        int i = key->findIndex(x);
        int j = key->findIndex(y);
        if(i==-1 || j==-1) cout << "Cammino non esistente";
        if(d[i]!=0) bfs(x);
        if(d[j]==-1) cout << "Cammino non esistente";
        else printPath(j);
        cout << endl;
    }

    /* void dfs_visit(int i){
      color[i] = GRAY;
      d[i] = t++;

      for(int j=0; j<key->size(); j++){
        if(m[i][j] && color[j] == WHITE){
          p[j] = i;
          dfs_visit(j);
        }
      }

      color[i] = BLACK;
      f[i] = t++;
    }*/

    int dfs_visit(int i){
      int cycle = 0;
      color[i] = GRAY;
      d[i] = t++;

      for(int j=0; j<key->size(); j++){
        if(m[i][j] && color[j] == GRAY) cycle = 1;
        if(m[i][j] && color[j] == WHITE){
          p[j] = i;
          cycle |= dfs_visit(j);
        }
      }

      color[i] = BLACK;
      f[i] = t++;
      s->push(*key->findKey(i));
      return cycle;
    }

    int dfs(int flag = 0){
      for(int i=0; i<key->size(); i++) {
          color[i] = WHITE;
          p[i] = -1;
      }
      t = 0;
      int cycle = 0;
      while(!s->isEmpty())  s->pop();
      //ciclo principale
      for(int i=0; i<key->size(); i++){
        if(color[i] == WHITE){
          cycle |= dfs_visit(i);
        }
      }
      if(flag) {
        cout << "Tempi di inizio visita:" << endl;
        for(int i=0; i<key->size(); i++)
          cout << " [" <<key->findKey(i) << "] = " << d[i] << " - " << f[i] << endl;
      }
      return cycle;
    }

    void topological_order(){
      if(!dfs()){
        while(!s->isEmpty()){
          char C = *s->pop();
          cout << C << " ";
        }
        cout << endl;
      }
      else cout << "Ordinamento topologico non possibile" << endl;
    }

    void transpose(){
      int n = key->size();
      for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
          int tmp = m[i][j];
          m[i][j] = m[j][i];
          m[j][i] = tmp;
        }
      }
    }

    int components(){
      dfs();
      transpose();

      for(int i=0; i<key->size(); i++) {
          color[i] = WHITE;
          p[i] = -1;
      }
      t = 0;
      int cc = 0;
      int j=0;
      int ord[key->size()];
      while(!s->isEmpty()){
        char C = *s->pop();
        int i = key->findIndex(C);
        ord[j++] = i;

      }

      while(!s->isEmpty()) s->pop();


      for(int i=0;  i<key->size(); i++){
        if(color[i] == WHITE) {
          dfs_visit(i);
          cc++;
        }
        if(!s->isEmpty()) {
          cout << "{";
          while(!s->isEmpty()) {
            char C = *s->pop();
            cout << C;
            if(!s->isEmpty()) cout << ",";
          }
          cout << "}";
        }
      }

      cout << endl;
      transpose();
      return cc;
    }
};

void bogosort(int *v, int n){ // E' UNA MERDA NON USARLO
  int it = 0;
  while(1){
    int ordered = 1;
    for(int i=0; i<n; i++) if(v[i-1] > v[i]) ordered = 0;
    if(ordered) return;
    it++;
    for(int i=0; i<n; i++){
      int j = rand()%n;
      int tmp = v[i];
      v[i] = v[j];
      v[j] = tmp;
    }
  }
}

int main() {
  /*int v[] = {6,8,2};
  for(int i=0; i<3; i++)  cout << v[i] << " ";
  cout << endl;
  int it= bogosort(v, 3);
  for(int i=0; i<3; i++)  cout << v[i] << " ";
  cout << endl;
  cout << it << endl;*/
    Graph<char> *g = new Graph<char>(10);
    g->insertNode('A');
    g->insertNode('B');
    g->insertNode('C');
    g->insertNode('D');
    g->insertNode('E');
    g->insertNode('F');
    g->insertNode('G');
    g->insertEdge('A', 'B');
    g->insertEdge('C', 'D');
    g->insertEdge('C', 'E');
    g->insertEdge('D', 'G');
    g->insertEdge('D', 'F');
    g->insertEdge('E', 'F');
    g->insertEdge('E', 'B');
    g->insertEdge('F', 'A');
    g->insertEdge('F', 'B');
    g->insertEdge('B', 'A');
    g->print();
    int cc = g->components();
    cout << "Il grafo contiene " << cc << " componenti fortemente connesse" << endl;

    /*int cycle = g->dfs(1);
    if(cycle) cout << "Il grafo presenta dei cicli" << endl;
    else cout << "Il grafo è aciclico" << endl;
    g->topological_order();*/
}

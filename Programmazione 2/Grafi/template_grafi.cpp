#include <iostream>

using namespace std;

template <class T> struct Nodo
{
  T valore;
  Nodo<T>* succ;
};

template <class T> class Lista
{
public:
Lista() {testa = NULL;}
~Lista();
void print();
void inserisci(T val);
Nodo<T>* GetTesta() {return testa;}
Nodo<T>* search(int val);
private:
  Nodo<T>* testa;
};

template <class T> Lista<T>::~Lista()
{
  Nodo<T>* iter = testa;

  while(iter != NULL)
  {
    Nodo<T>* temp = iter->succ;
    delete iter;
    iter = temp;
  }
}

template <class T> void Lista<T>::print()
{
  Nodo<T>* iter = testa;

  while(iter != NULL)
  {
    cout << " " << iter->valore << "\t";
    iter = iter->succ;
  }
}


template <class T> void Lista<T>::inserisci(T val)
{
  Nodo<T>* nuovo = new Nodo<T>;

  nuovo->valore = val;
  nuovo->succ = testa;
  testa = nuovo;
}

template <class T> Nodo<T>* Lista<T>::search(int indice)
{
  Nodo<T>* p;

  for(p = testa; p!= NULL; p = p->succ)
    if(p->valore == indice) return p;
  return NULL;
}

template <class H> class LGraph
{
private:
  int len, n, m;
  int t;
  H **K;
  Lista<int> **Adj;

  int findIndex(H x)
  {
    for(int i = 0;i < n; i++)
      if(*K[i] == x) return i;
    return -1;
  }

public:
  LGraph(int len)
  {
    this->len = len;
    n = m = 0;
    K = new H*[len];
    for(int i=0; i<len; i++) K[i] = NULL;
    Adj = new Lista<int>*[len];
    for(int i=0; i<len; i++)
      Adj[i] = new Lista<int>();
  }
  LGraph<H>* addNode(H k)
  {
    if(n==len) return this;
    if(findIndex(k) >= 0) return this;
    K[n] = new H(k);
    n++; return this;
  }

  LGraph<H>* addEdge(H x, H y)
  {
    int i = findIndex(x);
    int j = findIndex(y);

    if(i < 0 || j < 0) return this;
    if(!Adj[i]->search(j))
    {
      Adj[i]->inserisci(j);
      m++;
    }
    return this;
  }

  void print()
  {
    for(int i=0; i<n; i++)
    {
      cout << "(" << i << ", " << *K[i] << ")" << ": ";
      Adj[i]->print();
      cout << endl;
    }
  }
};

int main()
{
  LGraph<char>* Gr = new LGraph<char>(9);
  Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3')->addNode('4');
  Gr->addNode('5')->addNode('6')->addNode('7')->addNode('8');

  Gr->addEdge('0', '8')->addEdge('0', '1')->addEdge('1', '8');
  Gr->addEdge('2', '4')->addEdge('3', '5')->addEdge('3', '6')->addEdge('3', '7');
  Gr->addEdge('4', '3')->addEdge('4', '0')->addEdge('5', '6');
  Gr->addEdge('5', '3')->addEdge('6', '5')->addEdge('8', '2');

  Gr->print();
  return 0;
}

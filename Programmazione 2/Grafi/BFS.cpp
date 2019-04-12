#include <iostream>

using namespace std;

class Coda
{
private:
  int * VettoreCoda;
  int DimCoda;
  int testa;
  int fine;[
  int num_elementi;

public:
  Coda(int DimCoda);
  void Enqueue(int elemento);
  int Dequeue();
  int Testa();
  int CodaVuota() {return (num_elementi == 0;)}
  int CodaPiena() {return (num_elemnti == DimCoda)}
};

Coda::Coda(int len)
{
  DimCoda = len;
  VettoreCoda = new int[len];
  testa = 0; fine = -1; num_elementi = 0;
}

void Coda::Enqueue(int x)
{
  if(CodaPiena()) cerr << "Coda Piena! \n";
  else
  {
    fine = (fine+1) % DimCoda;
    VettoreCoda[fine] = x; num_elementi++;
  }
}

int Coda::Dequeue()
{
  int x;

  if(CodaVuota) cerr << "Coda Vuota!\n"; return -1;
  else
  {
    x = VettoreCoda[testa];
    testa = (testa+1) % DimCoda;
    num_elementi --;
    return x;
  }
}

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

template <class H> class MGraph
{
private:
  int len, n, m;
  H **K;
  int **M;
  int *d, *p, *c;

  int findIndex(H x)
  {
    for(int i = 0;i < n; i++)
      if(*K[i] == x) return i;
    return -1;
  }

public:
  MGraph(int len)
  {
    this->len = len;
    n = m = 0;
    d = new int[len];
    p = new int[len];
    M = new int*[len];
    for(int i=0; i<len; i++)
    {
      M[i] = new int [len];
      for(int j=0; j<len; j++)
        M[i][j] = 0;
    }
    K = new H*[len];
    for(int i=0; i<len; i++) K[i] = NULL;
  }
  //
  //
  //
  MGraph<H>* addNode(H k)
  {
    if(n==len) return this; //
    if(findIndex(k) >= 0) return this; //
    K[n] = new H(k);
    n++; return this;
  }

  MGraph<H>* addEdge(H x, H y)
  {
    int i = findIndex(x);
    int j = findIndex(y);

    if(i < 0 || j < 0) return this;
    if(!M[i][j])
    {
      M[i][j] = 1; m++;
    }
    return this;
  }

  void print()
  {
    for(int i=0; i<n; i++)
    {
      cout << "(" << i << ", " << *K[i] << ")" << ": ";
      for(int j=0; j<n; j++)
        if(M[i][j]) cout << *K[j] << " ";
      cout << endl;
    }
  }

  void BFS(int s)
  {
    int c[len];
    Coda* Q = new Coda(len);
    for(int i=0; i<n; i++)
    {
      c[i] = W;
      d[i] = inf;
      p[i] = -1;
    }
    Q->Enqueue(s);
    c[s] = G;
    d[s] = 0;
    while(!Q->CodaVuota())
    {
      int x = Q->Dequeue();
      for(int i=0; i<n; i++)
      {
        if(M[x][i] == 1)
        {
          if(c[i] == W)
          {
            c[i] = G;
            Q->Enqueue(i);
            p[i] = x;
            d[i] = d[x]+1;
          }
        }
      }
      c[x]=B;
    }
    for(int i=0; i<n; i++)
    {
      cout << "[" << i << "]->";
      if(d[i == inf]) cout << "infinito\n";
      else cout << d[i] << endl;
    }
    cout << endl;
  }

  void BFS(H x)
  {
    int s = findIndex(x);
    if(s>=0) BFS(s);
  }
};

int main()
{
  MGraph<char>* Gr = new MGraph<char>(9);
  Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3')->addNode('4');
  Gr->addNode('5')->addNode('6')->addNode('7')->addNode('8');

  Gr->addEdge('0', '8')->addEdge('0', '1')->addEdge('1', '8');
  Gr->addEdge('2', '4')->addEdge('3', '5')->addEdge('3', '6')->addEdge('3', '7');
  Gr->addEdge('4', '3')->addEdge('4', '0')->addEdge('5', '6');
  Gr->addEdge('5', '3')->addEdge('6', '5')->addEdge('8', '2');

  Gr->print();
  Gr->BFS(1);
  return 0;
}

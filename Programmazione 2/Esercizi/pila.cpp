#include <iostream>

using namespace std;

class Nodo
{
public:
  Nodo(int x) {val = x; succ = NULL; }
  ~Nodo() {};
  int GetVal() {return val;}
  Nodo* GetSucc {return succ;}
  void SetVal(int x) {val = x;}
  void SetSucc(Nodo* p) {succ = p;}

private:
  int val;
  Nodo* succ;
};

class Pila
{
public:
  Pila() {p = NULL;}
  ~Pila();
  bool PilaVuota() {return !p;}
  int PrimoElemento() {if(p) return p->GetVal();
                       else return -1;}
  void print();
  void Push(int x);
  int Pop();

private:
  Nodo* p;
  void CancellaNodo();
};

void Pila::print()
{
  Nodo* nodo = p;

  if(nodo == NULL) cout << "Lista vuota!!" << endl;

  while(nodo != NULL)
  {
    cout << nodo->GetVal() << ", " << endl;
    nodo = nodo->GetSucc();
  }
}

void Pila::CancellaNodo()
{
  Nodo* nodo;

  if(p)
  {
    nodo = p;
    p = p->GetSucc();
    delete nodo;
  }
}

void Pila::Push(int x)
{
  Nodo* nodo = new Nodo(x);

  if(p) nodo->SetSucc(p);
  p = nodo;
}

int Pop()
{
  int e = PrimoElemento();
  CancellaNodo();
  return e;
}

Pila::~Pila()
{
  Nodo* nodo;

  while(p != NULL)
  {
    nodo = p;
    p = p->GetSucc();
    delete nodo;
  }
}

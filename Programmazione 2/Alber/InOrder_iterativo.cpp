#include <iostream>

using namespace std;

struct Nodo
{
  int val;
  Nodo* left;
  Nodo* right;
  Nodo* padre;
};

class Albero
{
private:
  Nodo* radice;
  void InOrder();
public:
  albero() : radoce(NULL) {};
  void Insert(int val);
  void InOrder();
  void stampa();

};

struct iostream{
  Nodo* elemento;
  item* succ;
};

class pila
{
private:
  item* p;
  void CancellaNodo();
public:
  pila() {p=NULL;}
  bool pilavuota() {return !p;}
  Nodo* PrimoElemento() {if p(!=NULL) return p->elemento;}
  void Push(Nodo* x);
  Nodo* Pop();
  void StampaPila();
}

void Pila::Push(Nodo*x)
{
  item* aux = new item;
  aux->elemento = x;
  if(p) aux->succ = p;
  else aux->succ = NULL;
  p=aux;
}

void Pila::CancellaNodo()
{
  item* pnodo;

  if(p)
  {
    pnodo = p;
    p = p->succ;
    delete pnodo;
  }
}

Nodo* Pila::Pop()
{
  Nodo* e;
  e=PrimoElemento();
  CancellaNodo();
  return e;
}

void albero::InOrder()
{
  Pila stack;
  Nodo* current = radice;
  bool done = false;

  while(!done)
  {
    if(current)
    {
      stack.Push(current);
      current = current->left;
    }
    else if(stack.pilavuota()) done = true;
    else
    {
      current = stack.Pop();
      cout << current->val << "/t";
      current = current->right;
    }
  }
}

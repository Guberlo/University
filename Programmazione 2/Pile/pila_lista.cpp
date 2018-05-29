#include <iostream>

using namespace std;

class Nodo
{
  public:
    Nodo(int x) {valore = x; succ = NULL;}
    ~Nodo(){}
    int get_valore() {return valore;}
    void Assegna(int x) {valore=x;}
    Nodo* Successivo() {return succ;}
    void AssegnaSuccessivo(Nodo* p) {succ=p;}
  private:
    int valore;
    Nodo* succ;
};

class Pila{
  public:
    Pila() {p=NULL;}
    ~Pila();
    bool PilaVuota() {return !p;}
    int PrimoElemento() {if(p!=NULL) return p->get_valore();
                          else return -1;}
    int Pop();
    void Push(int x);
    void print();
  private:
    Nodo* p;
    void CancellaNodo();
};

void Pila::print()
{
  Nodo* pnodo = p;

  if(pnodo == NULL) cout << "Lista vuota!" << endl;
  while(pnodo != NULL)
  {
    cout << pnodo->get_valore() << endl;
    pnodo=pnodo->Successivo();
  }
}

void Pila::Push(int x)
{
  Nodo* aux = new Nodo(x);
  if(p) aux->AssegnaSuccessivo(p);
  p=aux;
}

void Pila::CancellaNodo()
{
  Nodo* pnodo;

  if(p)
  {
    pnodo = p;
    p = p->Successivo();
    delete pnodo;
  }
}

int Pila::Pop()
{
  int e = PrimoElemento();
  CancellaNodo();
  return e;
}

Pila::~Pila()
{
  Nodo* pnodo;

  while(p!=0)
  {
    pnodo = p;
    p = p->Successivo();
    delete pnodo;
  }
}

int main()
{
  Pila p;

  p.Push(4);
  p.Push(5);
  p.Push(7);
  p.print();

  while(!p.PilaVuota())
  {
    cout << p.PrimoElemento() << endl;
    p.Pop();
  }
  cout << endl;
  p.~Pila();
  p.print();
}

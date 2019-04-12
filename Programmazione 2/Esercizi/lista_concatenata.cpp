#include <iostream>

using namespace std;

struct Nodo
{
  int val;
  Nodo* seg;
  Nodo* prec;
};

class ListaDoppia
{
public:
  Lista() {testa = NULL;}
  ~Lista();
  void Inserimento(int x);
  void Print();
  Nodo* GetTesta() {return testa;}

private:
  Nodo* testa;
};

Lista::~Lista()
{
  Nodo* aux = testa;

  while(aux != NULL)
  {
    Nodo* p = aux->succ;
    delete aux;
    aux = p;
  }
}

void Lista::Print()
{
  Nodo * iter = testa;

  while(iter != NULL)
  {
    cout << " " << iter->val << " \t Successivo: ";
    if(iter->succ != NULL)
      cout << iter->succ->val;
    else cout << "NULL!"
    cout << "\t Precedente: ";
    if(iter->prec != NULL)
      cout << iter->prec->val;
    else cout << "NULL!" << endl;
    iter = iter->succ;
  }
}

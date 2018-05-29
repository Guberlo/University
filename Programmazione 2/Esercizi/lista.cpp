#include <iostream>

using namespace std;

struct Nodo
{
  int val;
  Nodo* ptr;
};

class Lista
{
private:
Nodo* testa;

public:
Lista() {testa = NULL;}
~Lista();
void inserimento_testa(int val);
void inserimento_in_mezzo(Nodo* prec, Nodo* seg, int val);
void stampa();
};

void Lista::stampa()
{
  Nodo* aux = testa;

  while(aux != NULL)
  {
    cout << " " << aux->val << endl;
    aux = aux->ptr;
  }
}

void Lista::inserimento_testa(int valore)
{
  Nodo* nuovo = new Nodo;
  nuovo->val = valore;

  nuovo->succ = testa;
  testa = nuovo;
}

void Lista::inserimento_in_mezzo(Nodo* prec, Nodo* seg, int valore)
{
  Nodo* nuovo = new Nodo;

  nuovo->val = valore;

  prec->succ = nuovo;
  nuovo->succ = seg;
}

Lista::~Lista()
{
  Nodo* aux = testa;

  while(aux != NULL)
  {
    Nodo* temp = iter->succ;
    delete iter;
    iter = temp;
  }
}

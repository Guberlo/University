#ifndef  LISTA_H
#define LISTA_H

using namespace std;

struct Nodo
{
  int val;
  Nodo* succ;
};

class Lista
{
  private:
    Nodo* testa;

  public:
    Lista() {testa = NULL;} //default constructor
    ~Lista(); //default destructor
    void ins_testa(int num);
    void ins_coda(int num);
    void ins_tra(int num, Nodo* prec, Nodo* seg);
    void stampa();
    Nodo* get_Testa() {return this->testa;}
};

Lista::~Lista()
{
  Nodo* iter = this->testa;

  while(iter->succ != NULL)
  {
    Nodo* temp = iter->succ;
    delete iter;
    iter = temp;
  }
}

void Lista::ins_testa(int num)
{
  Nodo* nuovo = new Nodo;

  nuovo->val = num;
  nuovo->succ = this->testa;
  this->testa = nuovo;
}

void Lista::ins_coda(int num)
{
  Nodo* nuovo = new Nodo;
  nuovo->val = num;

  Nodo* iter = this->testa;

  if(this->testa == NULL) // Se nella lista non esiste nessun elemento la testa sarà uguale alla coda
  {
    nuovo->succ = NULL;
    this->testa = nuovo;
  }
  else
  {
    while(iter->succ != NULL)
      iter = iter->succ;
    nuovo->succ = NULL;
    iter->succ = nuovo;
  }
}

void Lista::ins_tra(int num, Nodo* prec, Nodo* seg)
{
  Nodo* nuovo = new Nodo;
  nuovo->val = num;

  prec->succ = nuovo;
  nuovo->succ = seg;
}

void Lista::stampa()
{
  Nodo* iter = this->testa;

  cout << "[ ";
  while(iter != NULL)
  {
    cout << iter->val << " ";
    iter = iter->succ;
  }
  cout << "]" << endl;
}

#endif

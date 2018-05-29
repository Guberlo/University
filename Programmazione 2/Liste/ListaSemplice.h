#include <iostream>
#include "list.h"

using namespace std;

struct Nodo
{
  int val;
  Nodo* succ_ptr;
}

class ListaSemplice
{
  public:
    ListaSemplice() {testa=NULL;}
    ~ListaSemplice();
    int getVal();
    ListaSemplice* getTesta() {return testa;}
    void setVal(int valore);
    void setSucc(Nodo* ptr);
  private:
    Nodo* testa;
};

ListaSemplice::ListaSemplice(int valore)
{
  val = valore;
  succ_ptr = NULL;
}

ListaSemplice::ListaSemplice(int valore, Nodo* ptr)
{
  val = valore;
  succ_ptr = ptr;
}

void ListaSemplice::setVal(int valore)
{
  Nodo* nuovo_nodo= new Nodo;
  nuovo_nodo->val = valore;
  testa = nuovo_nodo;
}

ListaSemplice::ListaSemplice()
{

}

#include <iostream>

using namespace std;

template <class T> struct Nodo
{
  T val;
  Nodo<T>* succ_ptr;
};

template <class T> class ListaSemplice
{
  public:
    ListaSemplice() {testa=NULL;}
    ~ListaSemplice();
    void print();
    void inserimento_testa(T x);
    void inserimento_mezzo(Nodo<T>* prec, Nodo<T>* succ, T x);
    Nodo<T>* getTesta() { return testa;}
  private:
    Nodo<T>* testa;
};

template <class T> ListaSemplice <T>::~ListaSemplice()
{
  Nodo<T>* counter = testa;

  while(counter != NULL)
  {
    Nodo<T>* temp = counter->succ_ptr;
    delete counter;
    counter=temp;
  }
}

template <class T> void ListaSemplice<T>::print()
{
  Nodo<T>* counter = testa;

  while(counter != NULL)
  {
    cout << " " << counter->val << endl;
    counter = counter->succ_ptr;
  }
}

template <class T> void ListaSemplice<T>::inserimento_testa(T x)
{
  Nodo<T>* new_node = new Nodo<T>;
  new_node->val = x;
  new_node->succ_ptr = testa;
  testa = new_node;
}

template <class T> void ListaSemplice<T>::inserimento_mezzo(Nodo<T>* prec, Nodo<T>* succ, T x)
{
  Nodo<T>* new_node = new Nodo<T>;
  new_node->val = x;
  new_node->succ_ptr = succ;
  prec->succ_ptr = new_node;
}

int main()
{
  ListaSemplice<char> obj;
  Nodo<char>* p;

  obj.inserimento_testa('a');
  obj.inserimento_testa('b');
  obj.inserimento_testa('c');

  obj.print();

  cout << endl << endl;


  p=obj.getTesta();

  while((p!=NULL) && (p->val!='b'))
    p=p->succ_ptr;
  if(p!=NULL)
    obj.inserimento_mezzo(p, p->succ_ptr, 'k');

  obj.print();

  return 0;
}

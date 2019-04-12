#include <iostream>

using namespace std;

template <class H> class Nodo
{
private:
  H* key;
  Nodo<H>* succ;
public:
  Nodo(H k)
  {
  key = new H(k);
  succ = NULL;
  }
  void set_key(H* in) {key = in;}
  void set_succ(Nodo<H>* next) {succ = next;}
  Nodo<H>* get_succ() {return succ;}
};

template <class H> class LList
{
private:
  Nodo<H>* head;

public:
  LList() : head(NULL) {};
  LList<H>* ins(H x);
  LList<H>* canc(H x);
  H* search(H x);
  void prin();
  //quelle che mi servono ALMENO


  Nodo<H>* get_head() {return head;}
  void set_head(Nodo<H>* in) {head = in;}
};

template <class H> LList<H>* LList<H> :: ins(H x)
{
  Nodo<H>* aux = new Nodo(H x);

  if(head == NULL) head = aux;
  else if(head->get_key() > x)
    aux->set_succ(head); head = aux;
  else
  {
    Nodo<H>* iter = get_head();
    Nodo<H>* preiter = iter;
    while((iter != NULL) && (x>*iter->get_key()))
    {
      preiter = iter;
      iter = iter->get_succ();
    }
    if(iter != NULL)
    {
      aux->set_succ(iter);
      preiter->set_succ(aux);
    }
    else preiter->set_succ(aux);
  }
  return this;
}

template <class H> void LList<H> :: print()
{
  Nodo<H>* iter = get_head();

  while(iter != NULL)
  {
    cout << *iter->get_key() << " \t";
    iter = iter->get_succ();
  }
  cout << endl;
}

template <class H> LList<H>* LList<H> :: canc(H x)
{
  Nodo<H>* iter = get_head();
  if(head)
  {
    if(*head->get_key() == x)
      set_head(head->get_succ());
      delete iter;
  }
  else
  {
    Nodo<H>* aux = get_head();

    while((iter != NULL) && (iter->get_key() != x))
    {
      aux = iter;
      iter = iter->get_succ();
    }
    if(iter)
    aux->set_succ(iter->get_succ());
    delete iter;
  }
}

template <class H> H* LList<H> :: search(H x)
{
  Nodo<H>* iter = get_head();

  while((iter != NULL) && (iter->get_key() != x))
  {
    iter = iter->get_succ();
  }

  if(iter)  return iter->get_key();
  else return NULL;
}

template <class H> class NodoTree
{
private:
  H* key;
  NodoTree<H>* left; NodoTree<H>* right; NodoTree<H>* padre;
public:
  NodoTree(H k)
  {
    key = new H(k);
    left=right=padre=NULL;
  }
  void set_key(H* in) {key=in;}
  H* get_key() {return key;}
  NodoTree<H>* get_left() {return left;}
  NodoTree<H>* get_right() {return right;}
  NodoTree<H>* get_padre() {return padre;}
  NodoTree<H>* set_left(NodoTree<H>* left) {this->left = left;}
  NodoTree<H>* set_right(NodoTree<H>* right) {this->right = right;}
  NodoTree<H>* set_padre(NodoTree<H>* padre) {this->padre = padre;}
};

template <class H> class BST
{
private:
  NodoTree<H>* root;
  int altezza;
  void inorder(NodoTree<H>*);
  NodoTree<H>* _min(NodoTree<H>* p)
  {
    NodoTree<H>* x = p;

    while(x->get_left() != NULL) x = x->get_left(); return x;
  }

  NodoTree<H>* _search(H x)
  {
    NodoTree<H>* iter = root;
    while ((iter != NULL) && (iter->get_key() != x)) {
      if(*(iter->get_key()) > x) iter = iter->get_left();
      else iter = iter->get_right();
    }
    return iter;
  }

  void trapianta(NodoTree<H>* u, NodoTree<H>* v)
  {
    if(u->get_padre() == NULL) root = v;
    else if(u == u->get_padre()->get_left())
      u->get_padre()->set_left(v);
      else u->get_padre()->set_right();
      if(v != NULL) v->set_padre(u->get_padre());
  }

public:
  BST() : root(NULL), altezza(0) {};
  BST<H>* canc(H x);
  BST<H>* ins(H x);
  H* search(H x);
  void print();
  NodoTree<H>* get_root() {return root;}
  int get_altezza() {return altezza;}
  void set_altezza(int x) {altezza = x;}
  H* minimum();
  H* successor(H x);
  int calcola_altezza(NodoTree<H>* nodo)
}

template <class H> BST<H>* BST<H> :: ins(H val)
{
  NodoTree<H>* nuovo = new NodoTree<H>(val);
  NodoTree<H>* x = root;
  NodoTree<H>* y = NULL;

  while(x != NULL)
  {
    y=x;
    if(*x->get_key() <= val) x = x->get_right();
    else x = x->get_left();
  }
  nuovo->set_padre(y);
  if(y == NULL) root = nuovo;
  else if (val < *y->get_key()) y->set_left(nuovo);
  else y->set_right(nuovo);
  return this;
}

template <class H> void BST<H> :: inorder(NodoTree<H>* p)
{
  if(p != NULL)
  {
    inorder(p->get_left());
    cout << *p->get_key() << "\t";
    inorder(p->get_right());
  }
}

int main()
{

}

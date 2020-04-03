#include <iostream>
#define massimo(a,b) a>b ? b:a;
using namespace std;

template <class T> class Node{
private:
  T* key;
  Node<T> *parent, *left, *right;

public:
  Node(T* key){
    parent = NULL;
    left = NULL;
    right = NULL;
    this->key = key;
  }

  void setKey(T* key) { this->key = key;}
  void setLeft(Node<T>* left) { this->left = left;}
  void setRight(Node<T>* right) { this->right = right;}
  void setParent(Node<T>* parent) { this->parent = parent;}

  T* getKey() { return key;}
  Node<T>* getLeft() { return left;}
  Node<T>* getRight() { return right;}
  Node<T>* getParent() { return parent;}
};

template <class H> class BST{
private:
  int n; //numero di nodi
  Node<H>* root, *current;
  Node<H>* _search(H x){
      Node<H>* tmp = root;

      while(tmp && *(tmp->getKey()) != x){
        if(x < *(tmp->getKey())) tmp = tmp->getLeft();
        else tmp = tmp->getRight();
      }
      return tmp;
  }

  Node<H>* _rsearch(H x, Node<H>* r){
    if(!r) return NULL;
    if(*(r->getKey()) == x) return r;
    if(x < *(r->getKey())) return _rsearch(x, r->getLeft());
    return _rsearch(x, r->getRight());
  }

  void _inOrder(Node<H>* r){
    if(r){
      _inOrder(r->getLeft());
      cout << *(r->getKey()) << " ";
      _inOrder(r->getRight());
    }
  }

  void _preOrder(Node<H>* r){
    if(r){
      cout << *(r->getKey()) << " ";
      _preOrder(r->getLeft());
      _preOrder(r->getRight());
    }
  }

  void _postOrder(Node<H>* r){
    if(r){
      _postOrder(r->getLeft());
      _postOrder(r->getRight());
      cout << *(r->getKey()) << " ";

    }
  }

  Node<H>* _rmin(Node<H>* r){
    if(!r || !r->getLeft()) return r;
    return _rmin(r->getLeft());
  }

  Node<H>* _rmax(Node<H>* r){
    if(!r || !r->getRight()) return r;
    return _rmax(r->getRight());
  }

  Node<H>* _successore(Node<H>* y){
    if(!y) return NULL;
    H x = *(y->getKey());
    if(y->getRight()){
      y = _rmin(y->getRight());
      return y;
    }
    else{
      do y = y->getParent();
      while(y && *(y->getKey()) < x);
      if(y) return y;
      return NULL;
    }
  }

  Node<H>* _predecessore(Node<H>* y){
    if(!y) return NULL;
    H x = *(y->getKey());
    if(y->getLeft()){
      y = _rmax(y->getLeft());
      return y;
    }
    else{
      do y = y->getParent();
      while(y && *(y->getKey()) > x);
      if(y) return y;
      return NULL;
    }
  }

  Node<H>* _canc(Node<H>* y, H x){
    Node<H>* tmp = _rsearch(y, x);
    if(tmp){
      if(tmp->getLeft() && tmp->getRight()){
        //caso 3
        Node<H>* s = _successore(tmp);
        tmp->setKey(s->getKey());
        _canc(s, *s->getKey());
      }
      else{
        Node<H>* child = tmp->getLeft();
        if(!child)  child = tmp->getRight();
        Node<H>* p = tmp->getParent();
        if(p){
          if(x<*(p->getKey()))  p->setLeft(child);
          else p->setRight(child);
        }
        else  root = child;
        if(child) child->setParent(p);
      }
    }
  }

  int _altezza(Node<H>* y){
    if(!y)  return -1;
    int max = _altezza(y->getLeft());
    int r = _altezza(y->getRight());
    if(max < r) max = r;
    return max+1;
    //return massimo(_altezza(y->getLeft()), _altezza(y->getRight()))+1;
  }

  int _prof(Node<H>* y, H x){
    if(!y)  return -1;
    if(*y->getKey() == x) return 0;
    int r;
    if(x < *y->getKey()) r = _prof(y->getLeft(), x);
    else r = _prof(y->getRight(), x);
    if(r > -1) return r+1;
    return -1;
  }

  int _rrank(Node<H>* y, H x){
    if(!y)  return 0;
    if(*y->getKey() < x)
      return (_rrank(y->getLeft(), x) + _rrank(y->getRight(), x) + 1);
    else
      return (_rrank(y->getLeft(), x));
  }

  int _peso(Node<H>* y){
    if(!y)  return 0;
    return (_peso(y->getLeft()) + _peso(y->getRight()) +1 );
  }

  int _foglie(Node<H>* y){
    if(!y)  return 0;
    if(y->getLeft() || y->getRight()) return _foglie(y->getLeft()) + _foglie(y->getRight());
    else return 1;
  }

public:
  BST(){
    root = current = NULL;
    n = 0;
  }

  int search(H x) {
    return (_search(x) != NULL);
  }

  BST<H>* insert(H x) {
    Node<H>* tmp = root;
    Node<H>* p = NULL;

    while(tmp){
      p = tmp;
      if(x < *(tmp->getKey())) tmp = tmp->getLeft();
      else tmp = tmp->getRight();
    }
    Node<H>* y = new Node<H>(new H(x));
    y->setParent(p);
    if(!p) root = y;
    else{
      if(x<=*(p->getKey())) p->setLeft(y);
      else p->setRight(y);
    }
    n++;
    return this;
  }

  void inOrder() { _inOrder(root);}
  void preOrder() {_preOrder(root);}
  void postOrder() {_postOrder(root);}

  H* min(){
    //Node<H>* y = _rmin(root);
    //return y ? y->getKey() : NULL;
    if(!root) return NULL;
    Node<H>* tmp = root;
    while(tmp->getLeft()) tmp = tmp->getLeft();
    return tmp->getKey();
  }

  H* max(){
    //Node<H>* y = _rmax(root)
    //return _rmax(root) ? _rmax(root)->getKey() : NULL;
    if(!root) return NULL;
    Node<H>* tmp = root;
    while(tmp->getRight()) tmp = tmp->getRight();
    return tmp->getKey();
  }

  H* predecessore(H x){
    Node<H>* y = _rsearch(x, root);
    y = _predecessore(y);
    if(y) return y->getKey();
    return NULL;
  }

  H* successore(H x){
    Node<H>* y = _rsearch(x, root);
    y = _successore(y);
    if(y) return y->getKey();
    return NULL;
  }

  void reset() {current = _rmin(root);}
  int hasNext() {return (current != NULL);}
  H* next() {
    if(!hasNext())  return NULL;
    H* tmp = current->getKey();
    current = _successore(current);
    return tmp;
  }

  int altezza(){
    return _altezza(root);
  }

  int altezza(H x){
    Node<H>* tmp = _rsearch(x, root);
    return _altezza(tmp);
  }

  int prof(H x){
    return _prof(root, x);
  }

  int rank(H x){
    Node<H>* tmp = _rsearch(x, root);
    int i = -1;
    if(tmp){
      i++;
      tmp = _predecessore(tmp);
      while(tmp){
        tmp = _predecessore(tmp);
        i++;
      }
    }
    return i;
  }

  int rrank(H x){
    return _rrank(root ,x);
  }

  int peso(){
    return _peso(root);
  }

  int peso(H x){
    Node<H>* tmp = _rsearch(x, root);
    return _peso(tmp);
  }

  int foglie(){
    return  _foglie(root);
  }
};

int main(){
  BST<int>* t = new BST<int>();
  t->insert(17)->insert(7)->insert(3)->insert(11);
  t->insert(19)->insert(13)->insert(8);
  cout << "(17)" << t->search(17) << endl;
  cout << "(13)" << t->search(13) << endl;

  t->inOrder();
  cout << endl;
  t->preOrder();
  cout << endl;
  t->postOrder();
  cout << "min: "<< *(t->min()) << endl;
  cout <<"max: " << *(t->max()) << endl;
  //cout << *(t->successore(8)) << endl;
  //cout << *(t->successore(13)) << endl;
  //cout << *(t->successore(13)) << endl;
  cout << *(t->successore(7)) << endl;
  cout << *(t->predecessore(7)) << endl;

  cout << t->foglie();
}

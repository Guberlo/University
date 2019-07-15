#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
inline int massimo(int a, int b) {return a>b?a:b;}
using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H> *parent, *left, *right;

public:
  Node(H key){
    this->key = new H(key);
    parent=right=left=NULL;
  }

  //setters
  void setKey(H key){this->key = new H(key);}
  void setParent(Node<H>* parent){this->parent = parent;}
  void setLeft(Node<H>* left){this->left = left;}
  void setRight(Node<H>* right){this->right = right;}

  //getters
  H getKey(){return *key;}
  Node<H>* getParent(){return parent;}
  Node<H>* getLeft(){return left;}
  Node<H>* getRight(){return right;}
};

template <class H> class BST{
private:
  Node<H>* root;

  Node<H>* _rmin(Node<H>* y){
    if(!y || !y->getLeft()) return y;
    return _rmin(y->getLeft());
  }

  Node<H>* _rsearch(Node<H>* y, H x){
    if(!y)  return NULL;
    if(y->getKey() == x)  return y;
    if(x < y->getKey()) return _rsearch(y->getLeft(), x);
    return _rsearch(y->getRight(), x);
  }

  Node<H>* _successore(Node<H>* y){
    if(!y)  return NULL;
    H x = y->getKey();
    if(y->getRight()){
      y = _rmin(y->getRight());
      return y;
    }
    else{
      do y = y->getParent();
      while(y && y->getKey() < x);
      if(y) return y;
      return NULL;
    }
  }

  void _canc(Node<H>* y, H x){
    Node<H>* tmp = _rsearch(y, x);
    if(!tmp)  return;

    Node<H>* p = tmp->getParent();
    if(!tmp->getRight() || !tmp->getLeft()){
      Node<H>* child = tmp->getRight();
      if(!child)  child = tmp->getLeft();
      if(!p)  root = child;
      else{
        if(tmp == p->getLeft()) p->setLeft(child);
        else p->setRight(child);
      }
      if(child) child->setParent(p);
    }
    else{
      Node<H>* s = _successore(tmp);
      if(s){
        tmp->setKey(s->getKey());
        _canc(tmp->getRight(), s->getKey());
      }
    }
  }

  int _livello(Node<H>* y, H x){
    if(!y)  return -1;
    if(y->getKey() == x) return 0;
    if(y->getKey() > x) return (_livello(y->getLeft(), x) +1);
    return (_livello(y->getRight(), x) +1);
  }

public:
  BST():root(NULL){};

  BST* insert(H x){
    Node<H>* tmp = root;
    Node<H>* p = NULL;

    while(tmp){
      p = tmp;
      if(tmp->getKey() < x )  tmp = tmp->getRight();
      else tmp = tmp->getLeft();
    }
    Node<H>* y = new Node<H>(x);
    y->setParent(p);
    if(!p)  root = y;
    else{
      if(p->getKey() < x) p->setRight(y);
      else p->setLeft(y);
    }
    return this;
  }

  void canc(H x){
    _canc(root, x);
  }

  int livello(H x){
    return _livello(root, x);
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type;
    in >> type;
    int op;
    in >> op;
    int nl;
    in >> nl;

    if(type == "int"){
      BST<int>* b = new BST<int>();
      int val;
      for(int i=0; i<op; i++){
          string s;
          in >> s;

          if(s[0] == 'i'){
            stringstream buffer(s.substr(4, s.size()));
            buffer >> val;
            b->insert(val);
          }

          if(s[0] == 'c'){
            stringstream buffer(s.substr(5, s.size()));
            buffer >> val;
            b->canc(val);
          }
      }

      for(int i=0; i< nl; i++){
        int l;
        in >> l;
        out << b->livello(l) << " ";
      }
      out << endl;
    }

    if(type == "double"){
      BST<double>* b = new BST<double>();
      double val;
      for(int i=0; i<op; i++){
          string s;
          in >> s;

          if(s[0] == 'i'){
            stringstream buffer(s.substr(4, s.size()));
            buffer >> val;
            b->insert(val);
          }

          if(s[0] == 'c'){
            stringstream buffer(s.substr(5, s.size()));
            buffer >> val;
            b->canc(val);
          }
      }

      for(int i=0; i< nl; i++){
        double l;
        in >> l;
        out << b->livello(l) << " ";
      }
      out << endl;
    }
  }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H> *parent, *left, *right;

public:
  Node(H key){
    this->key = new H(key);
    parent = left = right = NULL;
  }

  void setKey(H key){this->key = new H(key);}
  void setParent(Node<H>* parent){this->parent = parent;}
  void setLeft(Node<H>* left){this->left = left;}
  void setRight(Node<H>* right){this->right = right;}

  H getKey(){return *key;}
  Node<H>* getParent(){return parent;}
  Node<H>* getLeft(){return left;}
  Node<H>* getRight(){return right;}
};

template <class H> class BST{
private:
  Node<H>* root;

  Node<H>* _rsearch(H x, Node<H>* y){
    if(!y)  return NULL;
    if(y->getKey() == x)  return y;
    if(x < y->getKey()) return _rsearch(x, y->getLeft());
    return _rsearch(x, y->getRight());
  }

  void _canc(H x, Node<H>* y){
    Node<H>* tmp = _rsearch(x, y);
    if(!tmp)  return;
    Node<H>* p = tmp->getParent();
    if(!tmp->getLeft() || !tmp->getRight()){
      Node<H>* child = tmp->getLeft();
      if(!child)  child = tmp->getRight();
      if(!p)  root = child;
      else{
        if(tmp == p->getLeft()) p->setLeft(child);
        else p->setRight(child);
      }
      if(child) child->setParent(p);
    }
    else{
      Node<H>* s = _successore(tmp);
      tmp->setKey(s->getKey());
      _canc(s->getKey(), tmp->getRight());
    }
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

  Node<H>* _rmin(Node<H>* y){
    if(!y || !y->getLeft()) return y;
    return _rmin(y->getLeft());
  }

  int _foglie(Node<H>* y){
    if(!y)  return 0;
    if(y->getLeft() || y->getRight()) return _foglie(y->getLeft()) + _foglie(y->getRight());
    else return 1;
  }

  int _peso(Node<H>* y){
    if(!y)  return 0;
    return ((_peso(y->getLeft()) + (_peso(y->getRight()) +1 )));
  }

public:
  BST() : root(NULL){};

  BST<H>* insert(H x){
    Node<H>* tmp = root;
    Node<H>* p = NULL;

    while(tmp){
      p = tmp;
      if(tmp->getKey() < x) tmp = tmp->getRight();
      else tmp = tmp->getLeft();
    }
    Node<H>* y = new Node<H>(x);
    y->setParent(p);
    if(!p)  root = y;
    else{
      if(x < p->getKey()) p->setLeft(y);
      else p->setRight(y);
    }
    return this;
  }

  void canc(H x){
    _canc(x, root);
  }

  int foglie(){
    return _foglie(root);
  }

  int peso(H x){
    Node<H>* tmp = _rsearch(x, root);
    return _peso(tmp);
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type;
    in >> type;

    int nop;
    in >> nop;

    if(type == "int"){
      BST<int> *b = new BST<int>();
      int val;

      for(int i=0; i<nop; i++){
        string query;
        in >> query;

        if(query[0] == 'i'){
          stringstream buffer(query.substr(4, query.size()));
          buffer >> val;
          b->insert(val);
        }

        if(query[0] == 'c'){
          stringstream buffer(query.substr(5, query.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      in >> val;
      out << b->peso(val) << endl;
    }
    if(type == "double"){
      BST<double> *b = new BST<double>();
      double val;

      for(int i=0; i<nop; i++){
        string query;
        in >> query;

        if(query[0] == 'i'){
          stringstream buffer(query.substr(4, query.size()));
          buffer >> val;
          b->insert(val);
        }

        if(query[0] == 'c'){
          stringstream buffer(query.substr(5, query.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      out << b->foglie() << endl;
    }

  }
}

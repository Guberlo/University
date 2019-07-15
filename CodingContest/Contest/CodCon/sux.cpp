#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H> *parent, *left, *right;

public:
  Node(H key) {
    this->key = new H(key);
    parent = left = right = NULL;
  }

  //setters
  void setKey(H key){this->key = new H(key);}
  void setLeft(Node<H>* left){this->left = left;}
  void setRight(Node<H>* right){this->right = right;}
  void setParent(Node<H>* parent){this->parent = parent;}

  //getters
  H getKey(){return *key;}
  Node<H>* getLeft(){return left;}
  Node<H>* getRight(){return right;}
  Node<H>* getParent(){return parent;}
};

template <class H> class BST{
private:
  Node<H>* root;

  Node<H>* _rsearch(Node<H>* y, H x){
    if(!y)  return NULL;
    if(y->getKey() == x)  return y;
    if(x < y->getKey()) return _rsearch(y->getLeft(), x);
    return _rsearch(y->getRight(), x);
  }

  void _canc(Node<H>* r, H x){
    Node<H>* tmp = _rsearch(r, x);
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
      _canc(tmp->getRight(), s->getKey());
    }
  }

  Node<H>* _rmin(Node<H>* y){
    if(!y || !y->getLeft()) return y;
    return _rmin(y->getLeft());
  }

  Node<H>* _rmax(Node<H>* y){
    if(!y || !y->getRight())  return y;
    return _rmax(y->getRight());
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

  Node<H>* _predecessore(Node<H>* y){
    if(!y)  return NULL;
    H x = y->getKey();
    if(y->getLeft()){
      y = _rmax(y->getLeft());
      return y;
    }
    else{
      do y = y->getParent();
      while(y && y->getKey() > x);
      if(y) return y;
      return NULL;
    }
  }

public:
  BST():root(NULL){};

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
      if(p->getKey() < x) p->setRight(y);
      else p->setLeft(y);
    }
    return this;
  }

  void canc(H x){
    _canc(root, x);
  }

  H* successore(H x){
    Node<H>* y = _rsearch(root, x);
    if(y){
      y = _successore(y);
      if(y) return new H(y->getKey());
    }
    return NULL;
  }

  H* predecessore(H x){
    Node<H>* y = _rsearch(root, x);
    if(y){
      y = _predecessore(y);
      if(y) return new H(y->getKey());
    }
    return NULL;
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

    int nps;
    in >> nps;

    if(type == "int"){
      BST<int> *b = new BST<int>();
      int val;
      int* predecessore;

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

      for(int i=0; i<nps; i++){
        in >> val;
        predecessore = b->predecessore(val);
        if(predecessore) out << *predecessore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end type int
    if(type == "double"){
      BST<double> *b = new BST<double>();
      double val;
      double* predecessore;

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

      for(int i=0; i<nps; i++){
        in >> val;
        predecessore = b->predecessore(val);
        if(predecessore) out << *predecessore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end type int
  }//end in.eof
}// end main

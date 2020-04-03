#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

  Node<H>* _rsearch(Node<H>* y, H x){
    if(!y)  return NULL;
    if(y->getKey() == x)  return y;
    if(x < y->getKey()) return _rsearch(y->getLeft(), x);
    return _rsearch(y->getRight(), x);
  }

  Node<H>* _rmin(Node<H>* y){
    if(!y || !y->getLeft()) return y;
    return _rmin(y->getLeft());
  }

  Node<H>* _rmax(Node<H>* y){
    if(!y || !y->getRight())  return y;
    return _rmax(y->getRight());
  }

  Node<H>* _successore(Node<H>* r){
    if(!r)  return NULL;
    H x = r->getKey();
    if(r->getRight()){
      r = _rmin(r->getRight());
      return r;
    }
    else{
      do r = r->getParent();
      while(r && r->getKey() < x);
      if(r) return r;
      return NULL;
    }
  }

  Node<H>* _predecessore(Node<H>* r){
    if(!r)  return NULL;
    H x = r->getKey();
    if(r->getLeft()){
      r = _rmax(r->getLeft());
      return r;
    }
    else{
      do r = r->getParent();
      while(r && r->getKey() > x);
      if(r) return r;
      return NULL;
    }
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

  H* min(){
    Node<H>* y = _rmin(root);
    return y ? new H(y->getKey()) : NULL;
  }

  H* max(){
    Node<H>* y = _rmax(root);
    return y ? new H(y->getKey()) : NULL;
  }

  int search(H x){
    return (_search(root, x) != NULL);
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
      for(int i=0; i<nps; i++){
        in >> val;
        predecessore = b->predecessore(val);
        if(predecessore)  out << *predecessore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end int
    if(type == "double"){
      BST<double> *b = new BST<double>();
      double val;
      double* predecessore;
      for(int i=0; i<op; i++){
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
      for(int i=0; i<nps; i++){
        in >> val;
        predecessore = b->predecessore(val);
        if(predecessore)  out << *predecessore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end int
  }//end in.eof()
}//end main

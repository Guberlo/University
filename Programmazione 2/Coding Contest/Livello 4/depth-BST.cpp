#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H>* parent, *left, *right;

public:
  Node(H key){
    this->key = new H(key);
    parent = right = left = NULL;
  }

  void setKey(H key) {this->key = new H(key);}
  void setParent(Node<H>* parent) {this->parent = parent;}
  void setRight(Node<H>* right) {this->right = right;}
  void setLeft(Node<H>* left) {this->left = left;}

  H getKey() {return *key;}
  Node<H>* getParent() {return parent;}
  Node<H>* getLeft() {return left;}
  Node<H>* getRight() {return right;}
};

template <class H> class BST{
private:
  Node<H>* root;

  Node<H>* _rmin(Node<H>* y){
    if(!y || !y->getLeft()) return y;
    return _rmin(y->getLeft());
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

  Node<H>* _rsearch(Node<H>* y, H x){
    if(!y)  return NULL;
    if(y->getKey() == x)  return y;
    if(x < y->getKey()) return _rsearch(y->getLeft(), x);
    return _rsearch(y->getRight(), x);
  }

  void _canc(Node<H>* y, H x){
    Node<H>* tmp = _rsearch(y, x);
    if(!tmp)  return;
    Node<H>* p = tmp->getParent();
    if(!tmp->getLeft() || !tmp->getRight()){
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
      tmp->setKey(s->getKey());
      _canc(tmp->getRight(), s->getKey());
    }
  }

  int _depth(Node<H>* y, H x){
    if(!y)  return -1;
    if(y->getKey() == x)  return 0;
    int r;
    if(x < y->getKey()) r = _depth(y->getLeft(), x);
    else r = _depth(y->getRight(), x);
    if(r > -1)  return r+1;
    return -1;
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
    _canc(root, x);
  }

  int depth(H x){
    return _depth(root, x);
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type;
    in >> type;

    int n;
    in >> n;

    if(type == "int"){
      BST<int>* b = new BST<int>();
      int val;

      for(int i=0; i<n; i++){
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
      in >> val;
      out << b->depth(val) << endl;
    }
    if(type == "double"){
      BST<double>* b = new BST<double>();
      double val;

      for(int i=0; i<n; i++){
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
      in >> val;
      out << b->depth(val) << endl;
    }
  }
}

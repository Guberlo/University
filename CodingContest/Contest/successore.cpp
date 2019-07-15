#include<iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

inline int massimo(int a, int b) {return a>b?a:b;}

template <class H> class Node{
private:
  H* key;
  Node<H>* parent, *left, *right;

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

  Node<H>* _rsearch(Node<H>*r, H x){
    if(!r)  return NULL;
    if(r->getKey() == x)  return r;
    if(x < r->getKey()) return _rsearch(r->getLeft(), x);
    return _rsearch(r->getRight(), x);
  }

  Node<H>* _rmin(Node<H>* r){
    if(!r || !r->getLeft()) return r;
    return _rmin(r->getLeft());
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

  void _canc(Node<H>* r, H x){
    Node<H>* tmp = _rsearch(r,x);
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

  int _altezza(Node<H>* y){
    if(!y)  return -1;
    int max = _altezza(y->getLeft());
    int r = _altezza(y->getRight());
    return massimo(max,r)+1;
  }

  void _inorder(Node<H>* y){
    if(y){
      _inorder(y->getLeft());
      cout << y->getKey() << " ";
      _inorder(y->getRight());
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
      if(x < p->getKey()) p->setLeft(y);
      else p->setRight(y);
    }
    return this;
  }

  void canc(H x){
    _canc(root, x);
  }

  int altezza(){
    return _altezza(root)+1;
  }

  void inorder(){
    _inorder(root);
  }
};

int main(){
  ifstream in ("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type;
    in >> type;
    int n;
    in >> n;

    if(type == "int"){
      BST<int> *b = new BST<int>();
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
      out << b->altezza() << endl;
    }//end int
    if(type == "double"){
      BST<double> *b = new BST<double>();
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
      out << b->altezza() << endl;
    }//end int
  }
}

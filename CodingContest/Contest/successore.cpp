#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class H> class Node{
private:
  H key;
  Node<H> *parent, *left, *right;

public:
  Node(H key){
    this->key = key;
    parent = left = right = NULL;
  }

  //setters
  void setKey(H key){
    this->key = key;
  }
  void setParent(Node<H>* parent){
    this->parent = parent;
  }
  void setLeft(Node<H>* left){
    this->left = left;
  }
  void setRight(Node<H>* right){
    this->right = right;
  }

  //getters

  H getKey(){return key;}
  Node<H>* getParent(){return parent;}
  Node<H>* getLeft(){return left;}
  Node<H>* getRight(){return right;}
};

template <class H> class BST{
private:
  Node<H>* root;
  int n;

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

  void _canc(Node<H>* r, H x) {
    Node<H>* tmp = _rsearch(r, x);
    if(!tmp)  return;
    //caso 3
    if(tmp->getLeft() && tmp->getRight()){
      Node<H>* s = _successore(tmp);
      tmp->setKey(s->getKey());
      _canc(tmp->getRight(), s->getKey());
      n--;
    }
    else{
      Node<H>* child = tmp->getLeft();
      if(!tmp)  tmp = tmp->getRight();
      Node<H>* p = tmp->getParent();
      if(p){
        if(x < p->getKey()) p->setLeft(child);
        else  p->setRight(child);
      }
      else  root = tmp;
      if(child) child->setParent(p);
      n--;
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

  void _inOrder(Node<H>* r){
    if(r){
      _inOrder(r->getLeft());
      cout << r->getKey() << " ";
      _inOrder(r->getRight());
    }
  }
public:
  BST():root(NULL), n(0){};

  BST<H>* insert(H x){
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
    n++;
    return this;
  }

  void canc(H x){
    _canc(root, x);
  }

  H* successore(H x){
    Node<H>* y = _rsearch(root, x);
    y = _successore(y);
    if(y) return new H(y->getKey());
    return NULL;
  }

  H* min(){
    Node<H>* y = _rmin(root);
    return (y ? new H(y->getKey()) : NULL);
  }

  int search(H x){
    return (_rsearch(root, x) != NULL);
  }

  void inOrder(){
    _inOrder(root);
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

    int ns;
    in >> ns;

    if(type == "int"){
      BST<int> *b = new BST<int>();
      int val;
      int* successore;
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
      for(int i=0; i<ns; i++){
        int x;
        in >> x;
        successore = b->successore(x);
        if(successore)  out << *successore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end int

    if(type == "double"){
      BST<double> *b = new BST<double>();
      double val;
      double* successore;
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
      for(int i=0; i<ns; i++){
        double x;
        in >> x;
        successore = b->successore(x);
        if(successore)  out << *successore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end double

    if(type == "bool"){
      BST<bool> *b = new BST<bool>();
      bool val;
      bool* successore;
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
      for(int i=0; i<ns; i++){
        bool x;
        in >> x;
        successore = b->successore(x);
        if(successore)  out << *successore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end bool

    if(type == "char"){
      BST<char> *b = new BST<char>();
      char val;
      char* successore;
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
      for(int i=0; i<ns; i++){
        char x;
        in >> x;
        successore = b->successore(x);
        if(successore)  out << *successore << " ";
        else out << "-1 ";
      }
      out << endl;
    }//end char
  }//end in.eof()

}

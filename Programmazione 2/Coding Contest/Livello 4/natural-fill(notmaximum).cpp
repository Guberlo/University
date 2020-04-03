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

  void _postorder(Node<H>* y, ofstream& out){
    if(y){
      _postorder(y->getLeft(), out);
      _postorder(y->getRight(), out);
      out << y->getKey() << " ";
    }
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

  void naturalFill(H* arr){
    Node<H>* y = _rmin(root);
    int i=0;
    while(y){
      y->setKey(arr[i]);
      y = _successore(y);
      i++;
    }
  }

  void print(ofstream& out){
    _postorder(root, out);
    out << endl;
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
      int* arr = new int[n];
      for(int i=0; i<n; i++){
        in >> val;
        b->insert(val);
      }

      for(int i=0; i<n; i++)  in >> arr[i];
      b->naturalFill(arr);
      b->print(out);
    }
    if(type == "double"){
      BST<double>* b = new BST<double>();
      double val;
      double* arr = new double[n];
      for(int i=0; i<n; i++){
        in >> val;
        b->insert(val);
      }

      for(int i=0; i<n; i++)  in >> arr[i];
      b->naturalFill(arr);
      b->print(out);
    }
  }
}

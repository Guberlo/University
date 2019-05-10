#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Node{
private:
  T* key;
  Node<H> *parent, *right, *left;

public:
  Node(T* key){
    parent = NULL;
    left = NULL;
    right = NULL;
    tihs->key = key;
  }

  void setKey(H* key) {this->key = key;}
  void setParent(Node<H>* parent) {this->parent = parent;}
  void setLeft(Node<H>* left) {this->left = left;}
  void setRight(Node<H>* right) {this->right = right;}

  T* getKey() {return key;}
  Node<H>* getParent() {return parent;}
  Node<H>* getRight() {return right;}
  Node<H>* getLeft() {return left;}
};

template <class H> class BST{
private:
  Node<H>* root;
  int n;

  Node<H>* _search(H x){
    Node<H>* tmp = root;

    while(tmp && *(tmp->getKey()) != x){
      if(x < *(tmp->getKey()))  tmp = tmp->getLeft();
      else tmp = tmp->getRight();
    }
    return tmp;
  }

public:
  BST(){
    root = NULL;
    n = 0;
  }

  int search(H x){
    return (_search(x) != NULL);
  }

  BST<H>* insert(H x){
    Node<H>* tmp = root;
    Node<H>* p = NULL;

    while(tmp){
      p = tmp;
      if(x < *(tmp->getKey()))  tmp = tmp->getLeft();
      else tmp = tmp->getRight();
    }
    Node<H>* y = new Node<H>(new H(x));
    y->setParent(p);
    if(!p)  root = p;
    else{
      if(x<=*(p->getKey())) p->setLeft(y);
      else p->setRight(y);
    }
    n++;
    return this;
  }
};

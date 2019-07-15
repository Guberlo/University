#include <iostream>

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

  Node<H>* _rsearch(Node<H>* r, H x){
    if(!r)  return NULL;
    if(r->getKey() == x)  return r;
    if(x < r-getKey())  return _rsearch(r->getLeft(), x);
    return _rsearch(r->getRight(), x);
  }

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

  void _canc(Node<H>* y, H x){
    Node<H>* tmp = _rsearch(y, x);
    if(!tmp)  return NULL;
    Node<H>* p = tmp->getParent();
    if(!tmp->getLeft() || !tmp->getRight()){
      Node<H>* child = tmp->getLeft();
      if(!child)  child = tmp->getRight();
      if(!p)  root = child;
      else{
        if(tmp == p->getLeft()) p->setLeft(child);
        else  p->setRight(child);
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
    if(max < r) max = r;
    return max+1;
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

  int _foglie(Node<H>* y){
    if(!y)  return 0;
    if(y->getLeft() || y->getRight()) return (_foglie(y->getLeft()) + _foglie(y->getRight()));
  }

  int _peso(Node<H>* y){
    if(!y)  return 0;
    return (_peso(y->getLeft()) + _peso(y->getRight()) + 1);
  }


public:
  BST():root(NULL){};

  int depth(){
    return _depth(root);
  }

  int depth(H x){
    Node<H>* tmp = _rsearch(root, x);
    if(tmp) return _depth(tmp);
  }

  int peso(){
    return peso(root);
  }

  int foglie(){
    return _foglie(root);
  }
}

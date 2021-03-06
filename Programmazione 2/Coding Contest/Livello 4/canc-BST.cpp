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

  //setters
  void setKey(H key){this->key = new H(key);}
  void setParent(Node<H>* parent){this->parent = parent;}
  void setLeft(Node<H>* left){this->left = left;}
  void setRight(Node<H>* right){this->right = right;}

  //getters
  H getKey(){return *key;}
  Node<H>* getParent(){return parent;}
  Node<H>* getRight(){return right;}
  Node<H>* getLeft(){return left;}
};

template <class H> class BST{
private:
  Node<H>* root;

  Node<H>* _rsearch(Node<H>* r, H x){
    if(!r)  return NULL;
    if(r->getKey() == x)  return r;
    if(x < r->getKey())  return _rsearch(r->getLeft(), x);
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

  void _preOrder(Node<H>* r, ofstream& out){
    if(r){
      out << r->getKey() << " ";
      _preOrder(r->getLeft(), out);
      _preOrder(r->getRight(), out);
    }
  }

  void _postOrder(Node<H>* r, ofstream& out){
    if(r){
      _postOrder(r->getLeft(), out);
      _postOrder(r->getRight(), out);
      out << r->getKey() << " ";
    }
  }

  void _inOrder(Node<H>* r, ofstream& out){
    if(r){
      _inOrder(r->getLeft(), out);
      out << r->getKey() << " ";
      _inOrder(r->getRight(), out);
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

  void inOrder(ofstream& out){
    _inOrder(root, out);
  }

  void postOrder(ofstream& out){
    _postOrder(root, out);
  }

  void preOrder(ofstream& out){
    _preOrder(root, out);
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
    string print;
    in >> print;

    if(type == "int"){
      BST<int>* b = new BST<int>();
      int val;
      for(int i=0; i<n; i++){
        string s;
        in >> s;
        if(s[0] == 'i'){
          stringstream buffer(s.substr(4,s.size()));
          buffer >> val;
          b->insert(val);
        }
        if(s[0] == 'c'){
          stringstream buffer(s.substr(5,s.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      if(print == "preorder"){b->preOrder(out); out << endl;}
      if(print == "postorder"){b->postOrder(out); out << endl;}
      if(print == "inorder"){b->inOrder(out); out << endl;}
    }//end int
    if(type == "double"){
      BST<double>* b = new BST<double>();
      double val;
      for(int i=0; i<n; i++){
        string s;
        in >> s;
        if(s[0] == 'i'){
          stringstream buffer(s.substr(4,s.size()));
          buffer >> val;
          b->insert(val);
        }
        if(s[0] == 'c'){
          stringstream buffer(s.substr(5,s.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      if(print == "preorder"){b->preOrder(out); out << endl;}
      if(print == "postorder"){b->postOrder(out); out << endl;}
      if(print == "inorder"){b->inOrder(out); out << endl;}
    }//end double
    if(type == "char"){
      BST<char>* b = new BST<char>();
      char val;
      for(int i=0; i<n; i++){
        string s;
        in >> s;
        if(s[0] == 'i'){
          stringstream buffer(s.substr(4,s.size()));
          buffer >> val;
          b->insert(val);
        }
        if(s[0] == 'c'){
          stringstream buffer(s.substr(5,s.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      if(print == "preorder"){b->preOrder(out); out << endl;}
      if(print == "postorder"){b->postOrder(out); out << endl;}
      if(print == "inorder"){b->inOrder(out); out << endl;}
    }//end char
    if(type == "bool"){
      BST<bool>* b = new BST<bool>();
      bool val;
      for(int i=0; i<n; i++){
        string s;
        in >> s;
        if(s[0] == 'i'){
          stringstream buffer(s.substr(4,s.size()));
          buffer >> val;
          b->insert(val);
        }
        if(s[0] == 'c'){
          stringstream buffer(s.substr(5,s.size()));
          buffer >> val;
          b->canc(val);
        }
      }
      if(print == "preorder"){b->preOrder(out); out << endl;}
      if(print == "postorder"){b->postOrder(out); out << endl;}
      if(print == "inorder"){b->inOrder(out); out << endl;}
    }//end bool
  }//end in.eof
}//end  main

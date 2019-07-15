#include <iostream>
#include <fstream>

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
  void setKey(H key) {this->key = new H(key);}
  void setParent(Node<H>* parent) {this->parent = parent;}
  void setLeft(Node<H>* left) {this->left = left;}
  void setRight(Node<H>* right) {this->right = right;}

  //getters
  H getKey() {return *key;}
  Node<H>* getParent() {return parent;}
  Node<H>* getLeft() {return left;}
  Node<H>* getRight() {return right;}

};

template <class H> class BST{
private:
  Node<H>* root;

  void _preOrder(Node<H>* r, ofstream& out){
    if(r){
      out << r->getKey() << " ";
      _preOrder(r->getLeft(), out);
      _preOrder(r->getRight(), out);
    }
  }

  void _inOrder(Node<H>* r, ofstream& out){
    if(r){
      _inOrder(r->getLeft(), out);
      out << r->getKey() << " ";
      _inOrder(r->getRight(),out);
    }
  }

    void _postOrder(Node<H>* r, ofstream& out){
      if(r){
        _postOrder(r->getLeft(), out);
        _postOrder(r->getRight(), out);
        out << r->getKey() << " ";
    }
  }
public:
  BST() : root(NULL) {};

  void preOrder(ofstream& out){
    _preOrder(root, out);
    out << endl;
  }

  void postOrder(ofstream& out){
    _postOrder(root, out);
    out << endl;
  }

  void inOrder(ofstream& out){
    _inOrder(root, out);
    out << endl;
  }

  BST<H>* insert(H key){
    Node<H>* tmp = root;
    Node<H>* p = NULL;

    while(tmp){
      p = tmp;
      if(tmp->getKey() < key) tmp = tmp->getRight();
      else tmp = tmp->getLeft();
    }

    Node<H>* y = new Node<H>(key);
    if(!p) root = y;
    else{
      if(key < p->getKey()) p->setLeft(y);
      else p->setRight(y);
    }
    return this;
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type; in >> type;
    int n; in >> n;
    string print; in >> print;

    if(type == "int" || type == "bool"){
      BST<int> *b = new BST<int>();
      int val;

      for(int i=0; i<n; i++){
        in >> val;
        b->insert(val);
      }

      if(print == "preorder") b->preOrder(out);
      if(print == "postorder") b->postOrder(out);
      if(print == "inorder")  b->inOrder(out);
    }
    if(type == "double"){
      BST<double> *b = new BST<double>();
      double val;

      for(int i=0; i<n; i++){
        in >> val;
        b->insert(val);
      }

      if(print == "preorder") b->preOrder(out);
      if(print == "postorder") b->postOrder(out);
      if(print == "inorder")  b->inOrder(out);
    }
    if(type == "char"){
      BST<char> *b = new BST<char>();
      char val;

      for(int i=0; i<n; i++){
        in >> val;
        b->insert(val);
      }

      if(print == "preorder") b->preOrder(out);
      if(print == "postorder") b->postOrder(out);
      if(print == "inorder")  b->inOrder(out);
    }
  }
}

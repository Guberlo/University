#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <class H> class Node{
  private:
    Node<H>* next;
    H val;

  public:
    Node(H x) : val(x){next = NULL;}

    Node<H>* getNext(){return next;}

    H getVal(){return val;}

    void setNext(Node<H>* node){next = node;}
};

template <class H> class Stack{
  private:
    Node<H>* head;

  public:
    Stack(){head = NULL;}

    void Push(H x){
      Node<H>* node = new Node<H>*(x);

      node->setNext(head);
      head = node;
    }

    void Pop(){
      if(head != NULL){
        Node<H>* node = head->getNext();
        delete head;
        head = node;
      }
    }

  void print(ofstream &out){
    Node<H>* node = head;

    while(node != NULL){
      out << node->getVal() << " ";
      node = node->getNext();
      }
      out << endl;
  }

  ~Pila(){
    Node<H>* node = head;
    Node<H>* tmp;

    while(node != NULL){
      tmp = node->getNext();
      delete node;
      node = tmp;
    }
  }
};

int main(){
  ifstream("input.txt");
  ofstream("output.txt");

  while(!input.eof()){
    string type;
    in >> type;

    int n;
    in >> n;

    if(type == "int"){
      Stack<int>* s = new Stack<int>;

      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;
        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer(tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
    if(type == "char"){
      Stack<char>* s = new Stack<char>;

      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;
        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer(tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
    if(type == "bool"){
      Stack<bool>* s = new Stack<bool>;

      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;
        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer(tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
    if(type == "double"){
      Stack<double>* s = new Stack<double>;

      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;
        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer(tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
  }//end while
}//end main

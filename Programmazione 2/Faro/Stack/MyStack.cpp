#include <iostream>

using namespace std;

template <class H> class Node{
private:
  Node<H>* next;
  H key;

public:
  Node(H x) : key(x) {};
  Node(H x, Node<H>* n) : key(x), next(n) {};

  //setters
  void setNext(Node<H>* next) {this->next = next;}

  //getters
  H getKey() {return key;}
  Node<H>* getNext() {return next;}
};

template <class T> class Stack{
private:
  Node<T>* head;

public:
  Stack() {head = NULL;}

  Stack<T>* push(T x){
    Node<T>* node = new Node<T>(x);

    node->setNext(head);
    head = node;
    return this;
  }

  Stack<T>* pop(){
    Node<T>* node = head;
    head = head->getNext();
    delete node;
    return this;
  }

  void print(){
    Node<T>* tmp = head;

    while(tmp){
      cout << tmp->getKey() << " ";
      tmp = tmp->getNext();
    }
    cout << endl;
  }
};

int main(){
  Stack<int>* s = new Stack<int>();
  s->push(3)->push(10)->push(224);
  s->print();
  s->pop();
  s->print();
}

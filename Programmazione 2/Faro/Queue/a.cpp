#include <iostream>
const int LEN = 100;
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
  int n;

public:
  Stack() {head = NULL;}

  Stack<T>* push(T x){
    Node<T>* node = new Node<T>(x);

    node->setNext(head);
    head = node;
    n++;
    return this;
  }

  T* pop(){
    if(head){
      Node<T>* node = head;
      head = head->getNext();
      T* x = new int(node->getKey());
      delete node;
      n--;
      return x;
    }
    return NULL;
  }

  void print(){
    Node<T>* tmp = head;

    while(tmp){
      cout << tmp->getKey() << " ";
      tmp = tmp->getNext();
    }
    cout << endl;
  }

  int getSize() {return n;}
};

template <class T> class MyQueue{
private:
  Stack<T> *s1, *s2;

  void travaso(){
    while(s1->pop()){
      s2->push(*(s1->pop()));
    }
  }

public:
  MyQueue(){
    s1 = new Stack<T>();
    s2 = new Stack<T>();
  }

  MyQueue<T>* enqueue(T x){
    s1->push(x);
    return this;
  }

  T* dequeue(){
    if(s2->getSize() == 0){
      cout <<"travaso" << endl;
      travaso();
      cout << "travaso completato" << endl;
    }
    return s2->pop();
  }

  void print(){
    travaso();
    s2->print();
  }
};

int main(){
  MyQueue<int>* q = new MyQueue<int>();
  q->enqueue(12)->enqueue(23);
  cout << *q->dequeue() << " ";
}

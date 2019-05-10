#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Node{
private:
  Node<H>* next;
  H key;

public:
  Node(H key){
    next = NULL;
    this->key = key;
  }

  Node(Node<H>* next, H key){
    this->next = next;
    this->key = key;
  }

  void setKey(H key) { this->key = key;}

  void setNext(Node<H>* next) { this->next = next;}

  Node<H>* getNext() {  return next;}

  H getKey() { return key;}
};

template <class T> class Queue{
private:
  Node<T> *head;

public:
  Queue():head(NULL) {};

  Queue<T>* enqueue(T x){
    Node <T>* node = new Node<T>(x);

    if(head == NULL) head = node;
    else{
      Node<T>* tmp = head;
      while(tmp->getNext() != NULL)
        tmp = tmp->getNext();
      tmp->setNext(node);
    }
  }

  void dequeue(){
      Node<T>* node = head;
      head = head->getNext();
      delete node;
  }

  void print(){
    Node<T>* tmp = head;
    while(tmp != NULL){
      cout << tmp->getKey() << " ";
      tmp = tmp->getNext();
    }
    cout << endl;
  }

};

int main(){
  Queue<int>* q = new Queue<int>();

  q->enqueue(3);
  q->enqueue(10);
  q->enqueue(1324);
  q->dequeue();
  q->dequeue();
  q->dequeue();

  q->print();
}

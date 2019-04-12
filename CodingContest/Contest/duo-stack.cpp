#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Node{
  private:
    Node<H>* next;
    H val;

  public:
    Node(H x) : val(x){next = NULL;}
    H getVal(){return val;}
    Node<H>* getNext(){return next;}
    void setNext(Node<H>* node){node = next;}
};

template <class H> class Stack{
  private:
    Node<H>* head;

  public:
    Stack(){head = NULL;}

    void push(H x){
      Node<H>* node = new Node<H>(x);

      node->setNext(head);
      head = node;
    }

    void pop() {
      Node<H>* node = head;
      head = head->getNext();
      delete node;
    }

    void print(ofstream &out){
      Node<H>* node = head;

      while(node != NULL){
        out << node->getVal() << " ";
        node = node->getNext();
      }
      out << endl;
    }

    ~Stack(){
      Node<H>* node = head;
      Node<H>* tmp;

      while(node != NULL){
        tmp = node->getNext();
        delete node;
        node = tmp;
      }
    }
};

template <class H> class Queue{
  private:
    Stack<H>* s, Stack<H>* s1;
};

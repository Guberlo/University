#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

template <class H> class Queue{
  private:
    Node<H>* head;

  public:
    Queue(){head = NULL;}
    void push(H x){
      Node<H>* node = new Node<H>(x);

      if(head == NULL)  head = node;
      else{
        Node<H>* tmp = head;
        while(tmp->getNext() != NULL)
          tmp->getNext();
        tmp->setNext(node);
      }
    }

    void pop(){
      Node<H>* node = head;
      head = head->getNext();
      delete node;
      }
    }

    void print(ofstream &out){
      Nodo<H>* node = head;

      while(node != NULL){
        out << node->getVal() << " ";
        node = node->getNext();
      }
      out << endl;
    }

    ~Queue(){
      Node<H>* node = head;
      Node<H>* tmp;
      while(node != NULL){
        tmp = node->getNext();
        delete node;
        node = tmp;
      }
    }
};

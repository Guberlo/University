#include <iostream>

using namespace std;

template <class H> Node{
private:
  Node<T>* next, *prev;
  H* key;

public:
  Node(){
    key = NULL;
    next = NULL;
    prev = NULL;
  }

  Node(H key, Node<T>* next = NULL, Node<T>* prev = NULL){
    *(this->key) = key;
    this->next = next;
    this->prev = prev;
  }

  //getters
  H& getKey() const {return *key;}
  Node<T>* getNext() const {return next;}
  Node<T>* getPrev() const {return prev;}

  //setters
  void setKey(H x) {key = new H(x);}
  void setNext(Node<T>* node) {next = node;}
  void setPrev(Node<T>* node) {prev = node;}
};

template <class T> class DLinkedList{
private:
  Node<T>* header, tailer, current;
  int n;
  Node<T>* _search(H x){
    Node<T>* temp = header->getNext();
    while(temp != tailer){
      if(temp->getKey() == x) return temp;
      temp = temp->getNext();
    }
    return NULL;
  }

public:
  DLinkedList(){
    header = new Node<T>();
    tailer = new Node<T>();
    n = 0;
    header->setNext(tailer);
    tailer->setPrev(header);
  }

  void insert(T x){
    Node<T>* temp = header->getNext();
    while(temp != tailer && temp->getKey() < x) temp = temp->getNext();
    Node<T>* node = new Node<T>(x, temp, temp->getPrev());
    temp->getPrev()->setNext(node);
    temp->setPrev(node);
    n++;
  }

  void canc(T x){
    Node<T>* node = _search(x);
    if(node){
      node->getPrev()->setNext(node->getNext());
      node->getNext()->setPrev(node->getPrev());
      n--;
    }
  }

  int getSize() {return n;}
  int search(T x) {return (_search(x) != NULL);}

  //iterator
  void reset() {current = header->getNext();}
  int hasNext() {return current != tailer;}

  T* next(){
    if(hasNext()){
      current = current->getNext();
      return &(current->getPrev()->getKey());
    }
    return NULL;
  }
};

template <class T>
ostream& operator<<(ostream& out, const DLinkedList& l){
  DLinkedList<T> t = l;
  t.reset();
  while(t.hasNext())  out << *(t.next()) << endl;
  return out; 
}

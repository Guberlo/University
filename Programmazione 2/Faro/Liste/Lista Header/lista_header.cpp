#include <iostream>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H>* next, *prev;

public:
  Node(){
    key = NULL;
    next = NULL;
    prev = NULL;
  }
  Node(H key, Node<H>* next = NULL, Node<H>* prev = NULL){
    this->key = new H(key);
    this->next = next;
    this->prev = prev;
  }

  void setKey(H key){
    *(this->key) = key;
  }
  void setNext(Node<H>* node){
    this->next = node;
  }
  void setPrev(Node<H>* node){
    this->prev = node;
  }
  H& getKey(){ //utilizzo la reference per poter modificare gli oggetti
    return *key;
  }
  Node<H>* getNext(){
    return next;
  }
  Node<H>* getPrev(){
    return prev;
  }
};

template <class T> class DLinkedList{
private:
  Node<T>* header, *tailer, *current;
  int n;

  Node<T>*_search(T x){
    Node<T>* temp = header->getNext();
    while(temp != tailer){
      if(temp->getKey() == x)  return temp;
      temp = temp->getNext();
    }
    return NULL;
  }

public:
  DLinkedList(){
    n = 0;
    header = new Node<T>();
    tailer = new Node<T>();
    header->setNext(tailer);
    tailer->setPrev(header);
  }

  DLinkedList* insert(T x){
    Node<T>* temp = header->getNext();
    while(temp != tailer && temp->getKey()<x) temp = temp->getNext();
    Node<T>* node = new Node<T>(x,temp,temp->getPrev());
    temp->getPrev()->setNext(node);
    temp->setPrev(node);
    n++;
    return this;
  }

  void canc(T x){
    Node<T>* node = _search(x);
    if(node){
      node->getPrev()->setNext(node->getNext());
      node->getNext()->setPrev(node->getPrev());
      n--;
    }
  }

  int search(T x){
    return (_search(x)!=NULL);
  }

  //iteratore
  void reset() {
    current = header->getNext();
  }

  int hasNext(){
    return current!=tailer;
  }

  T* next() {
    if(hasNext()){
      current = current->getNext();
      return &(current->getPrev()->getKey()); //& se voglio una il valore o new T se voglio una copia
    }
    return NULL;
  }
};

ostream& operator<<(ostream &out, const DLinkedList<int>& l){
  DLinkedList<int> t = l;
  t.reset();
  while(t.hasNext()) out << *(t.next()) << " ";
  return out;
}

int main(){
  DLinkedList<int> *l = new DLinkedList<int>();
  l->insert(4)->insert(11)->insert(7);
  cout << *l << endl;
  l->insert(6)->insert(3);
  l->insert(13);
  cout << *l << endl;
  /*l->canc(13);
  l->canc(4);
  l->canc(6);
  l->canc(11);
  l->canc(3);
  l->canc(7);
  l->canc(9);
  cout << *l << endl;*/

  l->reset();
  while(l->hasNext()){
    int *t = l->next();
    *t = (*t) * 2;
  }
  cout << *l << endl;

  return 0;
}

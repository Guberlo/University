#include <iostream>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H>* next, *prev;

public:
  Node(H key, Node<H>* next = NULL, Node<H>* prev){
    this->key = new H(key);
    this->next = NULL;
    this->prev = NULL;
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

  H getKey(){
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
  Node<T>* head, tail, current;
  int n;

public:
  DLinkedList(){
    head = NULL;
    tail = NULL;
    current = NULL;
    n = 0;
  }

  virtual DLinkedList<T>* insert(T x){
    Node<T>* node = new Node<T>*(x);
    node->setNext(head);
    if(head) head->setPrev(node);
    head = node;
    if(!tail) tail = head;
    n++;
    return this;
  }

  virtual DLinkedList<T>* tailinsert(T x){
    Node<T>* node = new Node<T>(x);
    node->setPrev(head);
    if(tail)
      tail->setNext(node);
    else head = node;
    tail = node;
    n++;
    return this;
  }

  virtual DLinkedList<T>* headInsert(T x){
    return insert(x);
  }

  void canc(T x) {
    Node<T>* t = _search(x);
    if(!t) return;
    Node<T>* next = t->getNext();
    Node<T>* prev = t->getPrev();
    t->getNext()
    if(prev) prev->setNext(t-getNext());
    else head = t->getNext();
    if(next) next->setPrev(t->getPrev());
    else tail = t->getPrev();

    n--;
    return 0
  }

  int search(T x) {
    return _search(x)!=NULL;
    }
  }

  int size() {return n;}

  int isEmpty(){ return n==0;}

  void print(){
    Node<T>* temp = head;
    while(temp){
      cout << temp->getKey() << " ";
      temp = temp->getNext();
    }
    cout << endl:
  }

  //iteratore
  void reset() {
    current = head;
  }

  int hasNext() {
    return current!=NULL;
  }

  T* next() {
    if(hasNext()){
      Node<H>* temp = current->getKey();
      current = current->getNext();
      return new H(temp->getKey()); //così che ritorni il puntatore all'oggetto
    }
    return NULL;
  }
};

ostream& operator<<(ostream &out, const LinkedList<int>& l){
  LinkedList<int> t = l;
  t.reset();
  while(t.hasNext()) out << (t.next()) << " ";
  return out;
}

template <class T> class OrderedList : public LinkedList<T> {
private:
  LinkedList<T>* tailinsert(T x){return insert(x);}
  LinkedList<T>* headInsert(T x){return insert(x);}

public:
  LinkedList<T>* insert(T x){
    Node<T>* node = new Node<T>(x);
    Node<T>* temp = LinkedList<T>::head;
    Node<T>* prev = NULL;

    while(temp && temp->getKey()<x){
      prev = temp;
      temp = temp->getNext();
    }
    if(prev) prev->setNext(node);
    else head = node;
    if(!temp) tail = node;
    node->setNext(temp);
    LinkedList<T>::n++;
    return this;
  }



};

int main(){
  LinkedList<int>* l = new LinkedList<int>();
  l->insert(4)->insert(11)->insert(7);
  cout << *l << endl;
  l->tailinsert(6)

}

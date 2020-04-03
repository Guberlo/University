#include <iostream>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H>* next;

public:
  Node(H key, Node<H>* next = NULL){
    this->key = new H(key);
    this->next = NULL;
  }

  void setKey(H key){
    *(this->key) = key;
  }

  void setNext(Node<H>* node){
    this->next = node;
  }

  H getKey(){
    return *key;
  }

  Node<H>* getNext(){
    return next;
  }
};

template <class T> class LinkedList{
private:
  Node<T>* head, tail, current;
  int n;

public:
  LinkedList(){
    head = NULL;
    tail = NULL;
    current = NULL;
    n = 0;
  }

  virtual LinkedList<T>* insert(T x){
    Node<T>* node = new Node<T>*(x);
    node->setNext(head);
    head = node;
    if(!tail) tail = head;
    n++;
    return this;
  }

  virtual LinkedList<T>* tailinsert(T x){
    Node<T>* node = new Node<T>(x);
    if(tail) tail->setNext(node);
    else head = node;
    tail = node;
    n++;
    return this;
  }

  virtual LinkedList<T>* headInsert(T x){
    return insert(x);
  }

  void canc(T x) {
    Node<T>* temp = head;
    Node<T>* prev = NULL;
    while(temp && temp->getKey() != x){
      prev = temp;
      temp = temp->getNext();
    }
    if(!t) return;
    if(prev)  prev->setNext(temp->setNext();
    else head = t->getNext();
    if(temp == tail) tail = prev;
    n--;
    return 0
  }

  int search(T x) {
    Node<T>* temp = head;
    while(temp){
      if(temp->getKey() == x) return 1;
      temp = temp>getNext();
    }
    return 0;
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

  #include <iostream>

using namespace std;

template <class H> class Node{
private:
  H* key;
  Node<H>* next, *prev;

public:
  Node(){
    this->key = NULL;
    this->next = NULL;
    this->prev = NULL;
  }

  Node(H key, Node<H>* next=NULL, Node<H>* prev=NULL){
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
  H& getKey() const { //utilizzo la reference per poter modificare gli oggetti
    return *key;
  }
  Node<H>* getNext() const{
    return next;
  }
  Node<H>* getPrev() const{
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

  Node<T>* getHeader()const {return header;}

  Node<T>* getTailer()const {return tailer;}

public:
  DLinkedList(){
    n = 0;
    header = new Node<T>();
    tailer = new Node<T>();
    header->setNext(tailer);
    tailer->setPrev(header);
  }

  DLinkedList(const DLinkedList<T>& l){
    header = new Node<T>();
    tailer = new Node<T>();
    header->setNext(tailer);
    tailer->setPrev(header);
    n = 0;
    Node<T>* temp = l.getHeader();
    temp = temp->getNext();
    while(temp != l.getTailer()){
      insert(temp->getKey());
      temp = temp->getNext();
    }
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

  int getSize(){
    return n;
  }

  void update(){
    *this = DLinkedList< DLinkedList<int> >(*this); // questo permette di modificare l'oggetto realmente dopo l'inserimento(un riordinamento della lista di liste), in quanto se inseriamo un elemento nella lista e l'ordine verrà mutato nell'oggetto reale non risulterà
  }

  //iteratore
  void reset() {
    current = header->getNext();
  }

  int hasNext(){
    return (current!=tailer);
  }

  T* next() {
    if(hasNext()){
      current = current->getNext();
      return &(current->getPrev()->getKey()); //& se voglio una il valore o new T se voglio una copia
    }
    return NULL;
  }
};

template <class K>
ostream& operator<<(ostream &out, const DLinkedList<K>& l){
  DLinkedList<K> t = l;
  t.reset();
  while(t.hasNext()) out << *(t.next()) << " ";
  return out;
}

template <class K>
int operator<(const DLinkedList<K>& l1, const DLinkedList<K>& l2 ){
  DLinkedList<K> t1 = l1;
  DLinkedList<K> t2 = l2;

  return t1.getSize() < t2.getSize();
}

template <class K>
int operator==(const DLinkedList<K>& l1, const DLinkedList<K>& l2 ){
  DLinkedList<K> t1 = l1;
  DLinkedList<K> t2 = l2;

  return t1.getSize() == t2.getSize();
}

int main(){

}

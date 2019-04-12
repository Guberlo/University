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

class Monomio{
private:
  double coeff;
  int exp;

public:
  Monomio(double coeff, int exp){
    this->coeff = coeff;
    this->exp = exp;
  }

  void setCoeff(double x){coeff = x;}
  void setExp(int x){exp = x;}
  double getCoeff() const{return coeff;}
int getExp() const{return exp;}

};

ostream &operator<<(ostream& out, Monomio& m){
  if(m.getCoeff() == 0) return out;
  if(m.getCoeff() != 1 && m.getCoeff()!=-1) out << m.getCoeff();
  if(m.getCoeff() == -1) out << "-";
  if(m.getExp() > 0){
    out << "x";
    if(m.getExp() > 1) out << "^" << m.getExp();
  }
  else if(m.getCoeff() == 1 || m.getCoeff() == -1) out << 1;
  return out;
}

int operator<(const Monomio& a, const Monomio& b){
  return (a.getExp() < b.getExp());
}

int operator==(const Monomio& a, const Monomio& b){
  return (a.getExp() == b.getExp());
}

int operator>(const Monomio& a, const Monomio& b){
  return (a.getExp() > b.getExp());
}

class Polinomio{
private:
  DLinkedList< Monomio > *l;
  Monomio* search(int exp){
    l->reset();
    while(l->hasNext()){
      Monomio* m = l->next();
      if(m->getExp() == exp) return m;
    }
    return NULL;
  }
public:
  Polinomio(){
    l = new DLinkedList<Monomio>();
  }

  Polinomio(double coeff, int exp){
    Monomio m(coeff,exp);
    l = new DLinkedList<Monomio>();
    l->insert(m);
  }

  Polinomio(Monomio m){
    l = new DLinkedList<Monomio>();
    l->insert(m);
  }

  void add(Monomio m){
    Monomio* q = search(m.getExp());
    if(q){
      q->setCoeff(q->getCoeff() + m.getCoeff());
      if(q->getCoeff() == 0) l->canc(*q);
    }
    l->insert(m);
  }

  void add(Polinomio p){
    p.reset();
    while(p.hasNext()){
      Monomio* m = p.next();
      add(*m);
    }
  }

  void mult(Polinomio p){
    Polinomio *r = new Polinomio();
    reset();
    while(hasNext()){
      Monomio* m = next();
      p.reset();
      while(p.hasNext()){
        Monomio* q = p.next();
        Monomio* t = new Monomio(m->getCoeff() * q->getCoeff(),m->getExp() + q->getExp());
        r->add(*t);
      }
    }
    *this = *r;
  }

  //iteratore
  void reset() const {return l->reset();}
  int hasNext() {return l->hasNext();}
  Monomio* next() {return l->next();}
};

ostream& operator<<(ostream& out, const Polinomio &pol){
  Polinomio p = pol;
  p.reset();
  if(p.hasNext()) out << *p.next();
  while(p.hasNext()){
    Monomio* m = p.next();
    if(m->getCoeff()>0)  out << "+";
    out << *m;
  }
  return out;
}

Polinomio& operator+(const Polinomio& ap, const Polinomio& bp){
  Polinomio *c = new Polinomio();
  Polinomio a = ap;
  Polinomio b = bp;
  a.reset();
  while(a.hasNext()){
    Monomio* m = a.next();
    c->add(*m);
  }
  b.reset();
  while(b.hasNext()){
    Monomio* m = b.next();
    c->add(*m);
  }
  return *c;
}

int main(){
  Monomio m(3,7);
  cout << m << endl;
  Monomio m1(2,7);


  Polinomio p(Monomio(2,4));
  cout << p << endl;
}

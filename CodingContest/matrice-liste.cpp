#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Nodo{
  private:
    Nodo<H>* prev, next;
    H* key;

  public:
    Nodo(H* key){
      this->key = key;
      prev = next = NULL;
    }

    Nodo(H key){
      this->key = new H(key);
      prev = next = NULL;
    }

    //setters
    void setNext(Nodo<H>* next){
      this->next = next;
    }

    void setPrev(Nodo<H>* prev){
      this->prev = prev;
    }

    void setKey(H key){
      this-> key = new H(key);
    }
    //end setters

    //getters
    Nodo<H>* getPrev(){
      return prev;
    }

    Nodo<H>* getSucc(){
      return succ;
    }

    H* getKey(){
      return key;
    }
};

template <class H> class Lista{
  private:
    Nodo<H>* head, current;
    int count;
    int n;

  public:
    Lista(int n){
      H* tmp = NULL;
      Nodo<H>* head = new Nodo<H>(tmp);
      current = head;
      this->n = n;
      count = 0;
    }

    Lista<H>* Tins(H key){
      Nodo<H>* nodo = new Nodo<H>(key);
      count ++;

      Nodo<H>* tmp = head->getNext();
      Nodo<H>* prev =  head;
      //while(tmp->getNext())
      while(tmp){
        prev = tmp;
        tmp = tmp->getNext();
      }
      prev->setNext(nodo);
      nodo->setPrev(prev);
      return this;
    }

    Lista<H>* Tins(H* key){
      Nodo<H>* nodo = new Nodo<H>(key);
      count ++;

      Nodo<H>* tmp = head->getNext(); //perché inizializzo head a null
      Nodo<H>* prev =  head;
      //while(tmp->getNext())
      while(tmp){
        prev = tmp;
        tmp = tmp->getNext();
      }
      prev->setNext(nodo);
      nodo->setPrev(prev);
      return this;
    }

    H* getVal(int n){
      int i=0;
      Nodo<H>* tmp = head->getNext();

      while(tmp){
        if(i==n) return tmp->getKey();
        tmp = tmp->getNext();
        i++;
      }
      return NULL;
    }

    H* getNextVal(){
      current = current->getNext();
      return current->getKey();
    }

    int getCount(){
      return count;
    }

    void print(){
      Nodo<H>* tmp = head->getNext();

      while(tmp){
        cout << *(tmp->getKey()) << " ";
        tmp = tmp->getNext();
      }
    }

    bool hasNext(){
      return current->getNext != NULL;
    }
};

template <class H> ListaMatr{
  
};

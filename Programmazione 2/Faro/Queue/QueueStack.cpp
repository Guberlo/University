#include <iostream>
using namespace std;
const int LEN = 100;

template <class T> class Stack{
private:
  int top;
  int len;
  T** s;

public:
  Stack(int len = LEN){
    this->len = len;
    top = 0;
    s = new T*[len];
  }

  Stack<T>* push(T x){
    if(top < len) s[top++] = new T(x);
    return this;
  }

  T* pop(){
    return (top > 0 ? s[--top]:NULL);
  }

  int getSize() {return top;}
};

template <class T> class MyQueue{
private:
  Stack<T> *s1, *s2;

  void travaso(){
    while(s1->pop() != NULL)
      s2->push(*(s1->pop()));
  }

public:
  MyQueue(int len = LEN){
    s1 = new Stack<T>(len);
    s2 = new Stack<T>(len);
  }

  MyQueue<T>* enqueue(T x){
    s1->push(x);
    return this;
  }

  T* dequeue(){
    if(s2->getSize() == 0){
      cout <<"travaso" << endl;
      travaso();
      cout << "travaso completato" << endl;
    }
    return s2->pop();
    /*T* x = s1->pop();
    while(x){
      s2->push(*x);
      x = s1->pop();
    }
    s2->pop();
    x = s2->pop();
    while(x){
      s1->push(*x);
      x = s2->pop();
    }
    return this;*/
  }

  void print(){
    while(s2->getSize()){
      cout << *s2->pop() << " ";
    }
    cout << endl;
  }
};


int main(){
  Stack<int>* s = new Stack<int>();
  MyQueue<int>* q = new MyQueue<int>();
  s->push(24);
  cout << *s->pop() << endl;
  q->enqueue(12)->enqueue(14)->enqueue(39);
  q->print();

}

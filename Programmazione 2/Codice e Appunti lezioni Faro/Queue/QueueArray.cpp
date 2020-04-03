#include <iostream>
using namespace std;
const int LEN = 100;
template <class T> class Queue{
private:
  int head, tail;
  int len, n;
  T **q;

public:
  Queue(int len = LEN){
    head = tail = 0;
    n = 0;
    this->len = len;
    q = new T*[len];
  }

  Queue<T>* enqueue(T x){
    if(n<len){
      q[tail] = new T(x);
      tail = (tail+1)%len; //quando raggiunge la lunghezza massima torna a 0
      n++;
    }
    return this;
  }

  T* dequeue(){
    if(n > 0){
      T* tmp = q[head];
      head = (head+1)%len;
      n--;
      return tmp;
    }
    return NULL;
  }
};

int main(){
  Queue<int> q* = new Queue<int>();
  q->enqueue(5)->enqueue(3)->enqueue(1);
  int* e = q->dequeue();
  cout << *e << endl;
  e = q->dequeue();
  cout << *e << endl;
}

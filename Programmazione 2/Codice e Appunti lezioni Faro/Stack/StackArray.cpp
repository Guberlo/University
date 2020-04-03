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
    return top > 0 ? s[--top]:NULL;
  }

  int getSize() {return top;}
};

int main(){
  Stack<int> *s = new Stack<int>();
  s->push(5)->push(3)->push(1);
  int *e = s->pop();
  cout << *e;

}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class H> class Queue{
private:
  H** vector;
  int tail, head, n;
  int len;

public:
  Queue(){
    len = 200;
    tail = head = n = 0;
    vector = new H*[len];
  }

  Queue<H>* enqueue(H x){
    if(n>200) return this;
    vector[tail] = new H(x);
    tail = (tail+1)%len;
    n++;
    return this;
  }

  H* dequeue(){
    if(n == 0)  return NULL;
    H* x = vector[head];
    head = (head+1)%len;
    n--;
    return x;
  }

  void print(ofstream &out){
    for(int i=head; i<tail; i++)
      out << *vector[i] << " ";
    out << endl;
  }
};

template <class H> class Stack{
private:
  H** vector;
  int top, n, len;

public:
  Stack(){
    len = 200;
    top = n = 0;
    vector = new H*[len];
  }

  Stack<H>* push(H x){
    if(n >= len)  return this;
    vector[top++] = new H(x);
    n++;
    return this;
  }

  H* pop(){
    if(n == 0)  return NULL;
    top--;
    n--;
    H* x = vector[top];
    return x;
  }

  int size(){ return n; }

  Queue<H>* travasa(Queue<H>* q){
    H * x = pop();

    while(x){
      q->enqueue(*x);
      x = pop();
    }
    return q;
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    string type; in >> type;
    int n; in >> n;

    if(type == "int" || type == "bool"){
      Queue<int>* q = new Queue<int>();
      Stack<int>* t = new Stack<int>();
      int val;

      for(int i=0; i<n; i++){
        string s; in >> s;
        if(s[0] == 'd') q->dequeue();
        else if(s == "pop")  t->pop();
        else if(s[0] == 'e'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
        else if(s[0] == 'p' && s[1] == ':'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          t->push(val);
        }
        else if(s == "travasa") t->travasa(q);
      }
      q->print(out);
    }//end int
    if(type == "char"){
      Queue<char>* q = new Queue<char>();
      Stack<char>* t = new Stack<char>();
      char val;

      for(int i=0; i<n; i++){
        string s; in >> s;
        if(s[0] == 'd') q->dequeue();
        else if(s == "pop")  t->pop();
        else if(s[0] == 'e'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
        else if(s[0] == 'p' && s[1] == ':'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          t->push(val);
        }
        else if(s == "travasa") t->travasa(q);
      }
      q->print(out);
    }//end char
    if(type == "double"){
      Queue<double>* q = new Queue<double>();
      Stack<double>* t = new Stack<double>();
      double val;

      for(int i=0; i<n; i++){
        string s; in >> s;
        if(s[0] == 'd') q->dequeue();
        else if(s == "pop")  t->pop();
        else if(s[0] == 'e'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
        else if(s[0] == 'p' && s[1] == ':'){
          stringstream buffer(s.substr(2, s.size()));
          buffer >> val;
          t->push(val);
        }
        else if(s == "travasa") t->travasa(q);
      }
      q->print(out);
    }
  }
}

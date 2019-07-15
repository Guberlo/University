#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class H> class Stack{
private:
  H* vector;
  int top;
  int n;

public:
  Stack(){
    vector = new H[200];
    top = n = 0;
  }

  void push(H x){
    if(n >= 200)  return;
    vector[top++] = x;
    n++;
  }

  H* pop(){
    if(top <= 0)  return NULL;
    top--;
    H* x = new H(vector[top]);
    n--;
    return x;
  }
};

template <class H> class Queue{
private:
  Stack<H>* s1;
  Stack<H>* s2;

public:
  Queue(){
    s1 = new Stack<H>();
    s2 = new Stack<H>();
  }

  Queue<H>* enqueue(H x){
    s1->push(x);
    return this;
  }

  Queue<H>* dequeue(){
    H* x = s1->pop();

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
    return this;
  }

  void print(ofstream& out){
    H* x = s1->pop();
    while(x){
      s2->push(*x);
      x = s1->pop();
    }

    x = s2->pop();
    while(x){
      out << *x << " ";
      x = s2->pop();
    }
    out << endl;
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
      int val;

      for(int i=0; i<n; i++){
        string s; in >> s;

        if(s[0] == 'd') q->dequeue();
        else{
          stringstream buffer(s.substr(1, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
      }
      q->print(out);
    }//end int
    if(type == "double"){
      Queue<double>* q = new Queue<double>();
      double val;

      for(int i=0; i<n; i++){
        string s; in >> s;

        if(s[0] == 'd') q->dequeue();
        else{
          stringstream buffer(s.substr(1, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
      }
      q->print(out);
    }//end double
    if(type == "char"){
      Queue<char>* q = new Queue<char>();
      char val;

      for(int i=0; i<n; i++){
        string s; in >> s;

        if(s[0] == 'd') q->dequeue();
        else{
          stringstream buffer(s.substr(1, s.size()));
          buffer >> val;
          q->enqueue(val);
        }
      }
      q->print(out);
    }//end char
  }//end eof
}//end main


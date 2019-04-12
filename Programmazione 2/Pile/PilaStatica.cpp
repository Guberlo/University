#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class H> class Stack{
  H** val;
  int top,n;
  int length;

  Stack(){
    val = new H*[200];
    top = n = 0;
    length = 200;
  }

  Stack<H>* Push(H x){
    if(top >= length) return this;
    val[top] = new H(x);
    top++;
    n++;
    return this;
  }

  H* Pop(){
    if(top < 0) return NULL;
    H* x = val[top];
    top--;
    n--;
    return x;
  }

  void print(ofstream &out){
    for(int i=top; i>=0; i--)
      out << *v[i] << " ";
    out << endl;
  }
};

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!input.eof()){
    string type;
    in >> type;

    int n;
    in >> n;

    if(type == "int"){
      Stack<int> *s = new Stack<int>();
      int x;
      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;

        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer (tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
    if(type == "char"){
      Stack<char> *s = new Stack<char>();
      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;

        if(tmp == "pop") s->Pop();
        else{
          s->Push(tmp[1]);
        }
        s->print();
      }
    }
    if(type == "bool"){
      Stack<bool> *s = new Stack<bool>();
      bool x;
      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;

        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer (tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
    if(type == "double"){
      Stack<char> *s = new Stack<char>();
      double x;
      for(int i=0; i<n; i++){
        string tmp;
        in >> tmp;

        if(tmp == "pop") s->Pop();
        else{
          stringstream buffer(tmp.substr(1));
          buffer >> x;
          s->Push(x);
        }
        s->print();
      }
    }
  }//end while
}

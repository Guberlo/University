#include <iostream>

using namespace std;

const int PilaDIM=100;

class PilaDIM
{
    public:
      Pila();
      void push(int ele);
      int pop();
      void print();
      bool full();
      bool empty();
    private:
      int cima;
      int pila[PilaDIM];
};

Pila::Pila() : cima(-1) {};

bool Pila::full()
{
  if(cima==PilaDIM-1)
    return true;
  else return false;
}

bool Pila::empty()
{
  if(cima==-1)
    return true;
  return false;
}

void Pila::push(int ele)
{
  if(full())  cout << "Pila piena!!" << endl;
  else  pila[++cima] = ele;
}

int Pila::pop()
{
  if(empty()) cout << "Pila vuota!!" << endl; exit(1);
  else  int x = pila[cima--]; return x;
}

void Pila::print()
{
  if(empty()) cout << "Pila vuota!!" << endl;
  else
  {
    for(int i = cima; i>=0; i--)
      cout << "Posizione " << i << ": " << Vpila[i] << endl;
  }
}

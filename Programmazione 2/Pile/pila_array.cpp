#include <iostream>

using namespace std;

const int PilaDIM=100;
class Pila
{
    public:
      Pila();
      void Push(int ele);
      int Pop();
      void print();
      int PilaPiena();
      int PilaVuota();

    private:
      int Vpila[PilaDIM];
      int cima;
};

Pila::Pila() : cima(-1) {}; //setto la cima a -1 per poter utilizzare l'indice 0 come primo elemento

int Pila::PilaPiena()
{
  if(cima == PilaDIM-1)
    return 1;
  else return 0;
}

int Pila::PilaVuota()
{
  if(cima == -1)
    return 1;
  else return 0;
}

void Pila::Push(int ele)
{
  if(PilaPiena()) cout << "Stack overflow" << endl;
  else
  {
      cima++;
      Vpila[cima]=ele;
  }
}

int Pila::Pop()
{
  int x;

  if(PilaVuota()) cout << "Stack underflow" << endl; exit(1);
  else
  {
    x=Vpila[cima];
    cima--;
    return x;
  }
}

void Pila::print()
{

  if(PilaVuota()) cout << "Pila vuota" << endl;

  else
  {
    for(int i=cima; i>=0; i--)
    {
      cout << "Posizione " << i << ": " << Vpila[i] << endl;
    }
  }
}

int main()
{
  Pila p;

  p.print();
  p.Push(3);
  p.Push(2);
  p.Pop();
  p.print();

  return 0;
}

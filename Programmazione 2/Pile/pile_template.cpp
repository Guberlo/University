#include <iostream>

using namespace std;

const int PilaDIM=100;

enum stato_pila {OK,PIENA, VUOTA};

template <class T> class Pila
{
    public:
      Pila(int lung);
      ~Pila() {delete[] tabella;}
      void Push(T ele);
      T Pop();
      void print();
      int num_elementi(){return cima+1;}
      int leggi_lunghezza() {return lunghezza;}

    private:
      T* tabella;
      int cima;
      int lunghezza;
      stato_pila stato;

};

template <class T> Pila <T> :: Pila(int lung)
{
  lunghezza = lung;
  cima = -1;
  tabella = new T[lunghezza];
  stato = VUOTA;
}

template <class T> void Pila<T> :: Push(T x)
{
  if(stato != PIENA) tabella[++cima] = x;
  else cout << "Pila piena!" << endl;

  if(cima == lunghezza-1) stato = PIENA;
  else  stato = OK;
}

template <class T> T Pila<T>::Pop()
{
  T elem=0;

  if(stato!=VUOTA) elem = tabella[cima--];
  else
    cout << "Pila vuota!" << endl;
  if(cima == -1) stato = VUOTA;
  else stato = OK;
  return elem;
}

template <class T> void Pila<T>::print()
{
  if(stato == VUOTA) cout << "Pila vuota!" << endl;
  else
  {
    for(int i=cima; i>=0; i--)
    {
      cout << "Posizione " << i << ": " << tabella[i] << endl;
    }
  }
}

int main()
{
  Pila <int> stack(6);
  Pila <char> stack2(10);

  stack.Push(1);
  stack.Push(2);
  stack.Push(3);

  cout << "Numero di elementi stack: " << stack.num_elementi() << endl;
  stack.print();

  cout << "Estrarre il primo: " << stack.Pop() << endl;
  cout << "Estrarre il secondo: " << stack.Pop() << endl;
  cout << "Estrarre il terzo: " << stack.Pop() << endl;
  cout << "Numero di elementi stack: " << stack.num_elementi() << endl;
  cout << "Estrarre il quarto: " << stack.Pop() << endl;

  stack2.Push('a');
  stack2.Push('b');
  stack2.Push('c');

  stack2.print();

  cout << "Estrarre il primo: " << stack2.Pop() << endl;
  cout << "Estrarre il secondo: " << stack2.Pop() << endl;
  cout << "Estrarre il terzo: " << stack2.Pop() << endl;
  cout << "Numero di elementi stack: " << stack2.num_elementi() << endl;
  cout << "Estrarre il quarto: " << stack2.Pop() << endl;
}

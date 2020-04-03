
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class H> class Nodo
{
protected:
  Nodo<H>* succ;
  H val;

public:
  Nodo(H valore) : val(valore)
  {
    this->succ = NULL;
  }
  H getVal(){return this->val;}
  void setSucc(Nodo<H>* nodo){this->succ = nodo;}
  Nodo<H>* getSucc(){return this->succ;}
};

template <class H> class Pila
{
protected:
  Nodo<H>* testa;

public:
  Pila(){this->testa = NULL;}
  ~Pila()
  {
    Nodo<H>* iter = testa;
    Nodo<H>* tmp;

    while(iter != NULL)
    {
      tmp = iter->getSucc();
      delete iter;
      iter = tmp;
    }
  }

  void Push(H x)
  {
    Nodo<H>* nuovo = new Nodo<H>(x);
    nuovo->setSucc(this->testa);
    testa = nuovo;
  }

  void Pop()
  {
    if(testa != NULL)
    {
      Nodo<H>* tmp = testa;
      testa = testa->getSucc();
      delete tmp;
    }
  }

  void print(ofstream &out)
  {
    Nodo<H>* iter = testa;

    while(iter != NULL)
    {
      out << iter->getVal() << " ";
      iter = iter->getSucc();
    }
    out << endl;
  }
};

int main()
{
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof())
  {
    string tipo; in >> tipo;
    int n; in >> n;

    if(tipo == "int")
    {
      Pila<int>* t = new Pila<int>();
      for(int i=0; i<n; i++)
      {
        string tmp; in >> tmp;

        if(tmp == "pop")
          t->Pop();
        else
        {
        string _value = tmp.substr(1, tmp.length());
        int val = stoi(_value);
        t->Push(val);
        }
      }

      t->print(out);
      delete t;
    }

    else if(tipo == "char")
    {
      Pila<char>* t = new Pila<char>();
      for(int i=0; i<n; i++)
      {
        string tmp; in >> tmp;

        if(tmp == "pop")
          t->Pop();
        else
        {
        string x = tmp.substr(1, tmp.length());
        t->Push(x[0]);
        }
      }

      t->print(out);
      delete t;
    }
    else if(tipo == "bool")
        {
          Pila<bool>* t = new Pila<bool>();
          for(int i=0; i<n; i++)
          {
            string tmp; in >> tmp;

            if(tmp == "pop")
              t->Pop();
            else
            {
            string _value = tmp.substr(1, tmp.length());
            bool val = stoi(_value);
            t->Push(val);
            }
          }

          t->print(out);
          delete t;
        }

        else if(tipo == "double")
        {
          Pila<double>* t = new Pila<double>();
          for(int i=0; i<n; i++)
          {
            string tmp; in >> tmp;

            if(tmp == "pop")
              t->Pop();
            else
            {
            string _value = tmp.substr(1, tmp.length());
            double val = stod(_value);
            t->Push(val);
            }
          }

          t->print(out);
          delete t;
        }


  }

  return 0;
}

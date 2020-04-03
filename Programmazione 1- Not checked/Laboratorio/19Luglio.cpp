#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <string>

using namespace std;

class A
{
protected:
  int n;

public:
  A(int _n) : n(_n) {};
  virtual const int f(int x) = 0;

  virtual ostream &put(ostream &os) const
  {
    return os << "Class " << typeid(*this).name() << ": n = " << n << " ";
  }

  A operator++(int)
  {
    A temp = *this;
    ++*this;
    return temp;
  }
};

ostream &operator << (ostream &left, const A &obj)
{
  return obj.put(left);
}



class B : public A
{
private:
  int m;

public:
  B(int _n) : A(_n)
  {
    m = 3*(n%7);
  }

  const int fatt(int n)
  {
    return (n == 1 || n == 0) ? 1 : fatt(n - 1) * n;
  }

  const int f(int z)
  {
    if(n<z) return fatt(n);
    else return fatt(m);
  }

  ostream &put(ostream &os) const
  {
    A::put(os);
    return os << "{ m = " << m << " ";
  }
};

template <class T> class C : public A
{
private:
  T x;

public:
  C(int _n) : A(_n)
  {
    x = typeid(x) == typeid(int) ? g(n) : sin(n);
  }

  const T g(T k)
  {
    return pow(k, 2);
  }

  int const f(int z)
  {
    return g(n+x+z);
  }

  ostream &put(ostream &os) const
  {
    if(typeid(x) == typeid(int))
      return os << "Class C <int>: n = " << n << " {x = " << x << "} ";
    else
      return os << "Class C <double>: n = " << n << " {x = " << x << "} ";

  }
};


int main()
{
  const int DIM = 50;
  A* vett[DIM];
  srand(328832748);
  for(int i=0; i<DIM; i++) {
    int n=1+rand()%100;
    switch(rand()%3) {
      case 0: vett[i]= new B(n); break;
      case 1: vett[i]= new C<double>(n);break;
      case 2: vett[i]= new C<int>(n); break;
    }
  }

  cout << "Punto I" << endl;

  for(int i=0; i<DIM; i++)
    cout << i << ") " << *vett[i] << endl;

  cout << "Punto II: " ;

  int max = -1;
  int sum = 0;
  for(int i=0; i<DIM; i++)
  {
    max = max>(vett[i]->f(5)) ? max : (vett[i]->f(5));
    if(typeid(*vett[i]) == typeid(C<double>))
      sum+=((C<double>*)vett[i])->g(5);
  }
  cout << "max = " << max <<", sum = " << sum << endl;

  cout << (*vett[0])++;

  return 0;
}

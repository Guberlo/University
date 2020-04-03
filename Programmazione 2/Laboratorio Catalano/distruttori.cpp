#include <iostream>

using namespace std;

class C1 {
public:
  C1 (int n);
  ~C1();
private:
  int* pi, l;
};

C1::C1(int n) : l(n)
{
    cout << "Assegno " << l << " nuovi interi.\n";
    pi=new int[l];
}

C1::~C1()
{
  cout << "Elimino " << l << " interi.\n";
  delete [] pi;
}

class C2 : public C1
{
public:
  C2(int n);
  ~C2();
private:
  char *pc; int l;
};

C2::C2(int n) : C1(n), l(n)
{
  cout << "Assegno " << l << " nuovi caratteri.\n ";
  pc=new char[l];
}

C2::~C2()
{
  cout << "Elimino " << l << " caratteri.\n";
  delete [] pc;
}

int main()
{
  C2 a(50), b(100);
  return 0;
}

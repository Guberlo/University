#ifndef RETTANGOLO_H
#define RETTANGOLO_H
#include <iostream>

using namespace std;

class rettangolo
{
    public:
      double area();
      void modifica(double, double);
      void stampa();
    private:
      double altezza;
      double base;
};

double rettangolo::area()
{
  return base*altezza;
}

void rettangolo::modifica(double Alt, double Base)
{
  altezza=Alt;
  base=Base;
}

void rettangolo::stampa()
{
  cout << "La base è: " << base << endl;
  cout << "L'altezza è: " << altezza << endl;
}
#endif

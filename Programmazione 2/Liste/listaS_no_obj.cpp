#include <iostream>
#include "list.h"

using namespace std;

void printL(ListaSemplice* _ptr)
{
  ListaSemplice* testa = _ptr;

  while(testa!=NULL)
  {
    cout << " " << testa->num << endl;
    testa = testa->ptr;
  }
}

int main()
{
  ListaSemplice* primo =NULL;

  primo = new ListaSemplice(3, primo);
  primo = new ListaSemplice(2, primo);
  primo = new ListaSemplice(1, primo);

  printL(primo);
  return 0;

}

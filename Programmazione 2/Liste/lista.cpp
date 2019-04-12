#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
  Lista obj;
  Nodo* p;

  obj.ins_testa(24);
  obj.stampa();
  obj.ins_testa(53);
  obj.stampa();
  obj.ins_testa(121);
  obj.stampa();
  obj.ins_coda(12);
  obj.stampa();

  p = obj.get_Testa();
  while((p!=NULL) && (p->val!=53)) p = p->succ;
  if(p!=NULL)
    obj.ins_tra(200,p,p->succ);
  obj.stampa();

  return 0;
}

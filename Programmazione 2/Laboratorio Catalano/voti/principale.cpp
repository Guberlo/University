#include <iostream>
#include "voti.h"
using namespace std;

int main()
{
  Voti voti;
  bool flag=1;
  cout << "Inserisci i voti e quando hai finito un numero negativo" << endl;

  do {
    double voto;
    cout << "-- "; cin >> voto;
    if(voto<0) flag=0;
    else voti.inserisci(voto);
  } while(flag);
  double media=media_voti();
  cout << "La media dei voti è: " << media << endl;
  return 0;
}

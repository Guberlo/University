#include <iostream>
#include "voti.h"

Voti::Voti()
{
  n=0;
  for(int i=0;i<MAX;i++)
  voti[i]=0;
}

void Voti::inserisci(double voto)
{
  voti[n++]=voto;
}

double Voti::media_voti()
{
  double somma=0;
  for(int i=0;i<n;i++) somma+=voti[i];
  return (somma/n);
}

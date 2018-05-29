#ifndef VOTI_H
#define VOTI_H

#define MAX 100

 class Voti
 {
    public:
      Voti();
      void inserisci(double);
      double media_voti();
    private:
      double voti[MAX];
      int n;
 };

#endif

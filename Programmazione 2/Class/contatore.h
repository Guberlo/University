#ifndef CONTATORE_H
#define CONTATORE_H value

class contatore
{
  public:
    contatore() {conto=1;}
    void increamenta() {conto++;}
    int legge_conto() {return conto;}
  private:
    int conto;
};

#endif

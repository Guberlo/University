#include <iostream>

using namespace std;

struct Nodo{
  int valore;
  Nodo* succ;
};

class Lista{
    public:
      Lista(){testa=NULL;}
      //~Lista();
      void stampa();
      void ins_testa(int val);
      void inserisci(Nodo* prec, Nodo* seguente, int val);
      Nodo* RivelaTesta() {return testa;}
    private:
      Nodo* testa;
};

void Lista ::  stampa(){
  Nodo* iter=testa;
  while(iter!=NULL){
    cout << " " << iter->valore << endl;
    iter=iter->succ;
  }
}

void Lista :: ins_testa(int val){
  Nodo* nuovo= new Nodo;

  nuovo->valore=val;
  nuovo->succ=testa;
  testa=nuovo;
}

void Lista :: inserisci(Nodo*precedente, Nodo* seguente, int val){
  Nodo* nuovo=new Nodo;

  nuovo->valore=val;
  nuovo->succ=seguente;
  precedente->succ=nuovo;
}

Lista :: ~Lista(){
  Nodo* iter=testa;
  while(iter!=NULL){
    Nodo *temp=iter->succ; //creo una copia del successivo
    delete iter; //cancello elemento corrente
    iter=temp; // mi sposto al successivo
  }
}

int main(){
  Lista lista;
  Nodo* p;

  lista.ins_testa(20);
  lista.ins_testa(10);
  lista.ins_testa(5);
  lista.stampa();
  p.RivelaTesta();
  while((p!=NULL) && (p->valore!=10)) p=p->succ; //mettere prima NULL altrimenti potrebbe dare problemi
  if(p!=NULL) lista.inserisci(p,p->succ,15);
  lista.stampa();
}

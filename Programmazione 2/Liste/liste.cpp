#include <iostream>

using namespace std;

struct Elemento {
        int valore;
        Elemento* succ;
};

struct lista{
  Elemento* testa;
  

};

void inserisci(lista& L, int val){
        Elemento* nuovo= new Elemento;
        nuovo->valore=val;
        nuovo->succ=L.testa;
        L.testa=nuovo;
}

class Elemento {
    public:
        int valore;
        Elemento* succ;

Elemento (Elemento* n, int d) : succ(n), valore(d) {
}                                                       //assegno a dato il valore di d e a succ n
};

void print(lista L){
        //Elemento* primo=p;
        while(L.testa!=NULL) {
                cout << " " << L.testa->valore << endl;
                L.testa=L.testa->succ;
        }
}

int main(){
        //Elemento* testa=NULL;
        lista L;
        L.testa=NULL;

        /*testa=new Elemento(testa,1); //creo un elemento che punta a null
           testa=new Elemento(testa,2); //creo un elemento che punta alla precedente testa
           testa=new Elemento(testa,3);// idem
         */
        inserisci(L.testa,1);
        inserisci(L.testa,2);
        inserisci(L.testa,3);
        print(L.testa);
        return 0;
}

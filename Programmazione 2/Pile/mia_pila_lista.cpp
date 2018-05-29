#include <iostream>

using namespace std;

/* PASSO 1:
CREARE UNA CLASSE NODO CONTENENTE:
  -COSTRUTTORE (ASSEGNA VALORE E SETTA SUCC A NULL)
  -DISTRUTTORE DEFAULT
  -METODO GET_VALORE (RETURN VALORE)
  -METODO SET_VALORE (VALORE = X)
  -METODO GET_SUCC (RETURN SUCC)
  -METODO SET_SUCC (SUCC = P)*/

class Nodo
{
    public:
      Nodo(int x) {valore = x; succ = NULL;}
      ~Nodo() {}
      int get_valore() {return valore;}
      void set_valore(int x) {valore = x;}
      Nodo* get_succ() {return succ;}
      void set_succ(Nodo* p) {succ = p;}
    private:
      int valore;
      Nodo* succ;
};

/*PASSO 2:
CREARE UNA CLASSE PILA CONTENENTE:
  -COSTRUTTORE CHE SETTA INDIRIZZO A NULL (p = NULL)
  -DISTRUTTORE CANCELLA OGNI "NODO"
  -METODO PILAVUOTA CHE COMUNICA SE LA PILA E' VUOTA (return !p)
  -METODO PRIMO ELEMENTO CHE RITORNA IL PRIMO ELEMENTO DELLA PILA SE P != NULL RETURN P->GETVALORE
  -METODO POP CHE ESTRAE ELEMENTO NELLA POSIZIONE CORRENTE
  -METODO PUSH CHE INSERISCE ELEMENTO NELLA POSIZIONE CORRENTE
  -METODO PRINT CHE STAMPA LA PILA
  -METODO PRIVATE CANCELLA Nodo
  */

 class Pila
 {
    public:
      Pila() {p = NULL;}
      ~Pila();
      bool PilaVuota() {return !p;}
      int PrimoElemento() {if(p != NULL) return p->get_valore();
                            else return -1;}
      int Pop();
      void Push(int x);
      void Print();
    private:
      Nodo* p;
      void CancellaNodo();
 };

 void Pila::Print()
 {
   Nodo* pnodo = p;

   if(pnodo == NULL) cout << "Lista vuota!" << endl;

   while(pnodo != NULL)
   {
     cout << pnodo->get_valore() << endl;
     pnodo = pnodo->get_succ();
   }
 }

 void Pila::Push(int x)
 {
   Nodo* n = new Nodo(x);

   if(p) n->set_succ(p);
   p = n;
 }

 int Pila::Pop()
 {
   
 }

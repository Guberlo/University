#include <iostream>
#include "stdlib.h"
#include <math.h>
#include <limits>
#include <time.h>
using namespace std;
int INT_MAX = std::numeric_limits<int>::max();
/*
    Esercizio 2:
        Scrivere un metodo che prenda in input un vettore di interi e restituisca un bool
        che indichi se esistono due numeri "più vicini" (cioè differenza in valore assoluto
        minima) la cui somma è un multiplo di 7.
 */

bool multi7(int *A,int n){
        int a,b=0;
        int minDif=INT_MAX;
        for(int i=0; i<n-1; i++) {
                for(int j=i+1; j<n; j++) {
                        int dif=abs(A[i]-A[j]);
                        if(minDif<dif)
                                minDif=dif;
                        a=i;
                        b=j;
                }
        }
        if((A[a]+A[b])%7==0) {
                cout << "Trovato! Somma A["<<a<<"]+A["<<b<<"]";
                return true;
        }
        else{
                cout<< "Non è stato trovata nessuna somma tale.."<<endl;
                return false;
        }
}

void random(int *vett, int dim){
        for(int i=0; i<dim; i++) {
                vett[i]=rand()%100;
        }
}

void print_array(int *vett,int n){
        for(int i=0; i<n; i++) {
                cout << vett[i]<<", ";
        }
        cout << endl;
}

int main(){
        srand(time(0));
        int n;
        cout << "Inserisci dimensione array: ";
        cin>>n;
        int *ptr=new int[n];

        random(ptr,n);
        print_array(ptr,n);
        bool found=multi7(ptr,n);
        cout << found<<endl;

        return 0;
}

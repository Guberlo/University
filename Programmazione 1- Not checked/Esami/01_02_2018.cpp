#include <cstdlib>
#include <iostream>
#include <cctype>
#include <iomanip>

#define N 5
#define K 6

using namespace std;

int santone(bool M[][N]){
        int i, j;

        i=j=N/2;

        int cont = 0;
        int r;
        //Un if all'interno del while con la negazione delle
        //condizioni in or e un break OK equivalente
        while(j>=0 && j<N && i>=0 && i<N) {
                cout << "santone(): " << i << "," << j << endl;

                if(M[i][j]) {
                        M[i][j]=false;
                        cont++;
                }

                r = rand()%4; // 0,1,2,3
                if(r==0)
                        i++;
                else if(r==1)
                        i--;
                else if(r==2)
                        j++;
                else if(r==3)
                        j--;
        }
        return cont;
}

/*
 * Doppio ciclo for, il primo sull'indice di colonna, il secondo sull'indice di riga.
 * 1.Calcola e conserva le lunghezze di tutte le stringa della j-esima colonna (-1 se la stringa e' NULL)
 * 2.Doppio ciclo for che confronta le lunghezze memorizzate nello array
 */
int metodo1(string *A[N][K]){
        int a[N]={0}; //a[i] conserva il numero di vocali della stringa i della colonna ...
        int count;
        for(int j=0; j<K; j++) {
                for(int i=0; i<N; i++) {
                        if(A[i][j]!=NULL) {
                                count=0;
                                for(unsigned int c=0; c<A[i][j]->length(); c++)
                                        switch((*A[i][j])[c]) { // oppure un if con condizioni in OR..
                                        case 'a':
                                        case 'e':
                                        case 'i':
                                        case 'o':
                                        case 'u':
                                                count++;
                                                break;
                                        }//end switch
                                a[i]=count;
                        }//end if
                        else
                                a[i]=-1; // A[i][j]==NULL
                }//end for(i)
                 //a[] contiene il numero di vocali di tutte le stringhe nella colonna j-esima, -1 se null
                for(int k=0; k<N-1; k++)
                        for(int l=k+1; l<N; l++)
                                if(a[k]==a[l] && a[k]!=-1) {
                                        cout << "metodo1(): Found " << *A[l][j] << " and " << *A[k][j] << endl << flush;
                                        return true;
                                }
        }//end for (j)
        return false;
}

/*
 * Doppio ciclo for, il primo sull'indice di colonna (j), il secondo sull'indice di riga (i)
 * confronta la i-esima stringa della colonna j-esima con le rimanenti K-i stringhe
 *  della j-esima colonna
 */
int metodo2(string *A[N][K]){
        int count1;
        int count2;
        for(int j=0; j<K; j++) { // indice di colonna
                for(int i=0; i<N-1; i++) { // indice di riga
                        if(A[i][j]!=NULL) { //calcola num. vocali in *A[i][j]
                                count1=0;
                                for(unsigned int c=0; c<A[i][j]->length(); c++)
                                        switch((*A[i][j])[c]) { // oppure un if con condizioni in OR
                                        case 'a':
                                        case 'e':
                                        case 'i':
                                        case 'o':
                                        case 'u':
                                                count1++;
                                                break;
                                        }//end switch
                                for(int k=i+1; k<N; k++)
                                        if(A[k][j]!=NULL) {
                                                count2=0;
                                                //calcola vocali in *A[k][j]
                                                for(unsigned int c=0; c<A[k][j]->length(); c++)
                                                        switch((*A[k][j])[c]) { // oppure un if con condizioni in OR
                                                        case 'a':
                                                        case 'e':
                                                        case 'i':
                                                        case 'o':
                                                        case 'u':
                                                                count2++;
                                                                break;
                                                        }//end switch
                                                if(count1==count2) {
                                                        cout << "metodo2(): Found " << *A[k][j] << " and " << *A[i][j] << endl << flush;
                                                        return true;
                                                }
                                        }//end if
                        }
                }
        }
        return false;
}

int main(){
        srand(time(0));
        bool M[N][N];
        int c=0;
        cout << "**Esercizio 1**" << endl;
        cout << "Regione: " << endl;
        for(int i=0; i<N; i++) {
                for(int j=0; j<K; j++) {
                        if(rand()%2==1) {
                                M[i][j]=true;
                                c++;
                        }
                        else
                                M[i][j]=false;
                        cout << M[i][j] << " ";
                }
                cout << endl;
        }

        int r = santone(M);
        cout << "santone(M)=" << r <<  endl;

        cout << endl << endl << "**Esercizio 2**" << endl;

//  srand(111222333);
        string *S[N][K];
        int l;
        for(int i=0; i<N; i++) {
                for(int j=0; j<K; j++) {
                        l=rand()%15+5;
                        S[i][j] = new string();
                        for(int r=0; r<l; r++)
                                *S[i][j]+=(char) (rand()%20+97);
                        cout << setw(21) << *S[i][j];
                }
                cout << endl;
        }

        bool ret = metodo1(S);
        cout << "metodo1(S)=" << ret << endl << flush;

        ret = metodo2(S);
        cout << "metodo2(S)=" << ret << endl << flush;
}

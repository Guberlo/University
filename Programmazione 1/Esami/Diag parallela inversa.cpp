/*
    Esercizio 1:
        Scrivere un metodo che prenda in input una matrice quadrata A (nxn) di short e
        restituisca un bool che indichi se esistono in A due diagonali della stessa
        lunghezza parallele alla diagonale principale tali che l'una sia l'inversa
        dell'altra.
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool diagpara(short int **A,int DIM){
        for(int x = 1, k = DIM-2; x < DIM; x++, k--) {
                int y = 0, c = DIM-1;
                bool notFound = false;
                for(int z = x, j = k; z < DIM && !notFound; z++, j--) {
                        if(A[z][y] == A[j][c]) {
                                if(z == DIM-1) return true;
                                y++, c--;
                        }else notFound = true;
                }
        }
        return false;
}

void random(short int **vett, int rig,int col){
        for(int i=0; i<rig; i++) {
                for(int j=0; j<col; j++) {
                        vett[i][j]=rand()%2;
                }
        }
}

void fill_array(short int **vett, int rig, int col){
        for(int i=0; i<rig; i++) {
                for(int j=0; j<col; j++) {
                        cout<<"Inserisci A["<<i<<"]["<<j<<"]: ";
                        cin >> vett[i][j];
                }
                cout<<endl;
        }
        cout<<endl;
}

void print_array(short int **vett, int rig,int col){
        for(int i=0; i<rig; i++) {
                cout << endl;
                for(int j=0; j<col; j++) {
                        cout <<vett[i][j]<<", ";
                }
        }
        cout << endl;
}

int main()
{
        srand(time(0));
        int DIM,col;
        cout<<"Inserisci n righe: ";
        cin >> DIM;
        cout <<"Inserisci n colonne: ";
        cin >> col;
        short int **matr=0;
        matr=new short int*[DIM];
        for(int i=0; i<DIM; i++) {
                matr[i]=new short int[col];
        }

        fill_array(matr,DIM,col);
        print_array(matr,DIM,col);
        //matr=matriceTrasp(matr,rig,col);
        if(diagpara(matr,DIM)) cout << "Trovato!";
        else cout << "Non trovato..";
        for (int h = 0; h<DIM; h++) {
                delete [] matr[h];
        }
        delete [] matr;
        matr = 0;
        return 0;
}

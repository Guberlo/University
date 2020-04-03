#include <iostream>

using namespace std;

/*int **matriceTrasp(int **A,int RIG,int COL){
    int **M=0;
    M=new int*[RIG];
    for(int i=0;i<RIG;i++){
        M[i]=new int [COL];
        for(int j=0;j<COL;j++){
            M[i][j]=A[j][i];
        }
    }
    return M;
}
*/

void random(int **vett, int rig,int col){
    for(int i=0;i<rig;i++){
        for(int j=0;j<col;j++){
            vett[i][j]=rand()%100;
        }
    }
}

void print_array(int **vett, int rig,int col){
    for(int i=0;i<rig;i++){
            cout << endl;
        for(int j=0;j<col;j++){
            cout <<vett[i][j]<<", ";
        }
    }
    cout << endl;
}

void print_trasposta(int **vett, int rig,int col){
    for(int j=0;j<col;j++){
            cout << endl;
        for(int i=0;i<rig;i++){
            cout <<vett[i][j]<<", ";
        }
    }
    cout << endl;
}

int main()
{
    int rig,col;
    cout<<"Inserisci n righe: ";
    cin >> rig;
    cout <<"Inserisci n colonne: ";
    cin >> col;
    int **matr=0;
    matr=new int*[rig];
    for(int i=0;i<rig;i++){
        matr[i]=new int[col];
    }

    random(matr,rig,col);
    print_array(matr,rig,col);
    //matr=matriceTrasp(matr,rig,col);
    print_trasposta(matr,rig,col);
    for (int h = 0;h<rig;h++){
            delete [] matr[h];
          }
          delete [] matr;
          matr = 0;
    return 0;
}

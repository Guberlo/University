#include <iostream>
#include <string>

const int n=3;

using namespace std;
/*
    Esercizio 1:
        Scrivere un metodo che prenda in input una matrice quadrata di stringhe nxn e restituisca
        true se esiste una stringa nella diagonale secondaria avente i primi tre caratteri
        coincidenti con gli ultimi tre di una qualunque s tringa nella diagonale principale,
        false altrimenti.
*/

bool strin(string A[][n]){
    for(int i=0,j=n-1;i<n;i++,j--){
        for(int k=0,l=0;k<n;k++,l++){
            if(A[i][j].length() > 2 && A[k][l].length() > 2){
                if(A[i][j].substr(0,3)==A[k][l].substr(A[k][l].length()-3,3))
                return true;
            }
        }
    }
    return false;
}

int main()
{
    string A[][n]={{"adsida","asdrea","aifgsd"},
                   {"adswa","asdaif","asjda"},
                   {"ashydg","asda","asudha"}};
    bool stroll=strin(A);
    cout << stroll;

    return 0;
}

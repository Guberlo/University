#include <iostream>

using namespace std;

const int N=5;

bool esestrano(int A[][N]){
        for(int i=0; i<N; i++) {
                bool trovato=false;
                for(int j=0; j<N-3; j++) {
                        int sum=A[i][j]+A[i][j+1]+A[i][j+2];
                        for(int k=0; k<N; k++) {
                                for(int l=k; l<N-2; l++) {
                                        int sum2=A[l][k]+A[l+1][k];
                                        if(sum==sum2) {
                                                cout << "Condizione soddisfatta!!"<<sum<<"=="<<sum2<<endl;
                                                cout << "i="<<i<<",j="<<j<<" ,k="<<k<<"l="<<l<<". "<<endl;
                                                trovato=true;
                                                return trovato;
                                        }
                                }
                        }
                }
        }
        return false;
}

int main(){
        int A[N][N]={{134,63,31,81,551},
                     {123,13,176,11,91},
                     {11,165,41,10,71},
                     {13,12,117,18,31},
                     {16,19,198,13,71}};
        if(esestrano(A))
                cout << "SUCCESSO!!"<<endl;
        else
                cout << "Fallimento"<<endl;
        return 0;
}

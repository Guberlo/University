#include <cstdlib>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

#define DIM 5

using namespace std;

float es2(string M[][4], int n, int m){
        short tot = n*m;
        short count=0;
        for(int i=0; i<n; i++)
                for(int j=0; j<m; j++)
                        if(M[i][j].substr(M[i][j].length()-3)=="are")
                                count++;
        return (float) count / tot * 100;
}

float *es1(int M[][DIM], int n){
        float *ret = new float[n];
        int min, count;
        float sum;
        for(int i=0; i<n; i++) {
                min=INT_MAX;
                if(i%2==0) { // se i e' pari...
                        for(int j=0; j<n; j++)
                                min=(min>M[j][i] ? M[j][i] : min);
                        ret[i] = min;;
                }
                else if(i%3!=0) { // i e' dispari e non e' divisibile per 3
                        sum=0;
                        count=0;
                        for(int j=0; j<n; j++)
                                if(M[i][j]%3 == 0) {
                                        sum+=M[i][j];
                                        count+=1;
                                }
                        if(sum!=0)
                                ret[i]=sum/(float) count;
                        else
                                ret[i] = 0;
                }else{ // altrimenti..
                        ret[i] = ret[i-2] + ret[i-1];
                } // end if
        } // end for
        return ret;
}

int main(){
        srand(time(0));
        int M[DIM][DIM];

        cout << "Es1:" << endl;
        cout << "M:" << endl;
        for(int i=0; i<DIM; i++) {
                for(int j=0; j<DIM; j++) {
                        M[i][j] = rand()%100;
                        cout << setw(3) << M[i][j];
                }
                cout << endl;
        }
        cout << endl;

        cout << "A:" << endl;
        float *r = es1(M, DIM);
        for(int k=0; k<DIM; k++)
                cout << setprecision(4) << setw(6) << r[k];
        cout << endl;

        string S[2][4];
        S[0][0] = "ballare";
        S[0][1] = "cantare";
        S[0][2] = "bere";
        S[0][3] = "tornire";

        S[1][0] = "scolpire";
        S[1][1] = "ordire";
        S[1][2] = "tramare";
        S[1][3] = "essere";

        cout << "Es2:" << endl;
        cout << "S:" << endl;
        for(int i=0; i<2; i++) {
                for(int j=0; j<4; j++)
                        cout << setw(10) << S[i][j];
                cout << endl;
        }


        cout << "\"-are\"/tot: " << es2(S,2,4) << endl;
}

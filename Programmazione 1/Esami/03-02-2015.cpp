#include <iostream>

using namespace std;

string* ese1(*A[][COL],int RIG){
        string bella="";
        string* str_ptr;
        str_ptr=bella;
        for(int i=0,j=n-1; i<n; i++,j--) {
                for(int k=0; k<A[i][j].length(); k++) {
                        if(A[i][j].length()%2!=0) {
                                int k=A[i][j].length()/2;
                                bella+=A[i][j][k];
                        }
                }
        }
        return str_ptr;
}

#include <iostream>
#include <string>
const int rig=5;
const int col=3;

using namespace std;

void matstr(string A[][col]){
        for(int j=0; j<col; j++) {
                for(int i=0; i<rig-1; i++) {
                        for(int l=i+1; l<rig; l++) {
                                if(A[i][j].length()>A[l][j].length()) {
                                        string temp=A[i][j];
                                        A[i][j]=A[l][j];
                                        A[l][j]=temp;
                                }
                        }
                }
        }
}


int main()
{
        srand(time(NULL));
        string matrix[rig][col];

        cout << "MATRICE NON RIORDINATA:" << endl;
        for(int x = 0; x < rig; x++) {
                for(int y = 0; y < col; y++) {
                        int k = rand()%5+3;
                        for(int i = 0; i < k; i++) {
                                matrix[x][y] += char(rand()%4+97);
                        }
                        cout << matrix[x][y] << " ";
                }
                cout << endl;
        }

        matstr(matrix);

        cout << "\nMATRICE RIORDINATA:" << endl;
        for(int x = 0; x < rig; x++) {
                for(int y = 0; y < col; y++) {
                        cout << matrix[x][y] << " ";
                }
                cout << endl;
        }
        return 0;
}

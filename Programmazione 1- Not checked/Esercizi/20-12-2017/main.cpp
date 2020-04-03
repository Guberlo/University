#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <limits>

using namespace std;
int INT_MAX = std::numeric_limits<int>::max();
const int N=5;

float *ese1(unsigned int M[][N]){
    float *A=new float [N];
    for(int j=0;j<N;j++){
        if(j%2==0){
            int minimo=INT_MAX;
            for(int i=0;i<N;i++){
                if(M[i][j]<minimo){
                  minimo=M[i][j];
                }
            }
            A[j]=minimo;
        }
        else if(j%2!=0 && j%3!=0){
            int count=0;
            float media=0.0;
            for(int i=0;i<N;i++){
                if(M[j][i]%3==0){
                    media+=M[i][j];
                    count ++;
                }
            }
            A[j]=media/count;
        }
        else {
            A[j]=A[j-2]+A[j-1];
        }
    }

    return A;

}//end func

//Metodo non richiesto dall'esame che riempie una matrice di interi positivi
void fillMatrix(unsigned M[][N], int rows, int columns, int min = 0, int max = 9) {
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			M[r][c] = static_cast<int>(rand() % (max - min)) + min;
}

//Metodo non richiesto dall'esame che stampa un array allocato dinamicamente.
template <class T>
void printArray(T *A, int length) {
	for (int i = 0; i < length; i++)
		std::cout << fixed << setprecision(3) << A[i] << std::setw(10); //setprecision and fixed are ignored if T is an integer type
	std::cout << std::endl;
}

//Metodo non richiesto dall'esame che stampa una matrice statica MxN
template <class T>
void printMatrix(T M[][N], int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			std::cout << M[r][c] << "  ";
		}
		std::cout << std::endl;
	}
}


//Main per testing
int main()
{
	srand(time(0));
	unsigned M[N][N];
	fillMatrix(M, N, N);
	printMatrix(M, N, N);
	float *A = ese1(M); //Richiamiamo il nostro metodo e stampiamo la matrice nella riga successiva.
	printArray<float>(A, N);
	cout << endl;
	system("pause");
    return 0;
}

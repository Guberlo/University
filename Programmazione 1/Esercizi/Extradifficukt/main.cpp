#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getrnumber(int min, int max){
    max=max-min-1;
    return int(rand()%max+min);
}

int *return_array_int(int size, int min, int max){
    int *new_array=new int[size];
    for(int i=0;i<size;i++){
        new_array[i]=getrnumber(min,max);
    }
    return new_array;
}

bool check_duplicates(int *array,int size){
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(*(array+i)==*(array+j))
                return true;
        }
    }
    return false;
}

int **matrix_identity(int size){
    int **matrix=new int*[size];
    for(int i=0;i<size;i++){
        matrix[i]=new int[size];
        for(int j=0;j<size;j++){
            matrix[i][j]=i==j ? 1:0;
        }
    }
    return matrix;
}

int **matrix_multiplication(int *matrix_1,int *matrix_2,int h, int w){
    int **matrix=new int*[h];
    for(int i=0;i<h;i++){
        matrix[i]=new int[w];
        for(int j=0;j<w;j++){
            matrix[i][j]= matrix_1[i] * matrix_2[j];
        }
    }
    return matrix;
}

void print_array(int *array, int size){
    for(int i=0;i<size;i++){
        if(!i) cout<<"[";
        cout<<array[i]<<(i==size-1 ? ']': '\t');
    }
    return;
}

void print_matrix(int **matrix, int h, int w){
    if(!w) w=h;
    for(int i=0; i<h;i++){
        for(int j=0;j<w;j++){
            cout << matrix[i][j]<< ", ";
        }
        cout << endl;
    }
    return;
}

int main()
{
    srand(time(0));

    int n= getrnumber(3,7);
    int m= getrnumber(3,7);
    int *A;
    int *B;

    cout << "Dimensione A: "<< n << endl;
    cout << "Dimensione B: "<< m << endl;

    A=return_array_int(n,3,7);
    cout<<"A: ";
    print_array(A,n);
    cout<<endl;
    B=return_array_int(m,3,7);
    cout<<"B: ";
    print_array(B,m);
    cout<<endl;

    if(check_duplicates(A,n)){
        cout<<"Sono stati trovati dei duplicati all'interno di A"<<endl;
        print_matrix(matrix_identity(m * n),n,m);
    }
    else{
        cout<<"Non è stato trovato alcun elemento che si ripete all'interno di A"<<endl;
        print_matrix(matrix_multiplication(A,B,n,m),n,m);
    }
    return 0;
}

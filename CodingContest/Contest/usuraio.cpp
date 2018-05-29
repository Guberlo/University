#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void swap(int *a, int* b){
    int aux=*a;
    *a=*b;
    *b=aux;
}

void selection(int A[], int size){
  int min;
  for(int i=0;i<size-1;i++){
      min=i;
    for(int j=i+1;j<size;j++)
      if(A[j]<A[min])
        min=j;

    swap(&A[min],&A[i]);
  }
}

int cperquisibili(int vett[], int dim, int nlocali_perq){
  int min_dif=2147483647;
  int dif;
  for(int i=0;i<dim-nlocali_perq;i++){
    for(int j=i+1;j<dim;j++){
      for(int k=0;k<nlocali_perq && j<dim;k++){
        first=vett[i];
        
        j++;
      }
      if(abs(dif)<min_dif){
        min_dif=abs(dif);
      }
    }
  }
  return min_dif;
}

void print(int vett[],int dim){
  for(int i=0;i<dim;i++)
      cout << vett[i]<<" ";
  cout<<endl;

}
int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  if(input.is_open()){
    while(!input.eof()){
      int nlocali;
      input >> nlocali;

      int nlocali_perq;
      input >> nlocali_perq;

      int civici[nlocali];
      for(int i=0;i<nlocali;i++)
          input >> civici[i];

      selection(civici,nlocali);
      print(civici,nlocali);
      int mindif=cperquisibili(civici,nlocali,nlocali_perq);
      output << mindif<<endl;
    }
  }


  input.close();
  output.close();
}

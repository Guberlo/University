#include <iostream>
#include <fstream>

using namespace std;

int check_if_contained(int a[], int dim){
  int count=0; //14 24 6    1 21 13    13 1 6   9 14 2    3 9 6
  for(int i=0,j=1,k=2;i<dim-3;i=i+3,j=j+3,k=k+3){
    for(int l=3,m=4,n=5;l<dim;l=l+3,m=m+3,n=n+3){
      if((a[i]>a[l]) && (a[j]>a[m]) && (a[k]>a[n]))
        count++;
      else if((a[l]>a[i]) && (a[m]>a[j]) && (a[n]>a[k]))
        count++;
    }
  }
  return count;
}

void stampa(int a[], int dim){
  for(int i=0;i<dim;i++){
    cout << a[i] << " ";
  }
  cout << endl;
}

int main(){
  ifstream input;
  ofstream output;

  input.open("input.txt");
  output.open("output.txt");

  if(input.is_open()){
    //while (!input.eof()) {
      int n;
      input >> n;

      int dim=3*n;

      int array[dim];
      for(int i=0;i<dim;i++){
        input >> array[i];
        cout << array[i] << " ";
      }
      cout << endl;
      output << check_if_contained(array, dim);
    }
  //}

  input.close();
  output.close();
}

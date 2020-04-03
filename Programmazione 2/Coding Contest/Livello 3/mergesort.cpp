#include <iostream>
#include <fstream>

using namespace std;

/*void merge(int* vett, int sx, int c, int dx){
  int i = sx;
  int j = c+1;
  int k = 0;
  int tmp[dx-sx+1];

  while(i<=c && j<=dx){
    if(vett[i] < vett[j]){
      tmp[k] = vett[i];
      i++;
    }
    else{
      tmp[k] = vett[j];
      j++;
    }
    k++;
  }

  while(i <= c){
    tmp[k] = vett[i];
    i++; k++;
  }

  while(j <= dx){
    tmp[k] = vett[j];
    j++; k++;
  }

  for(int i=sx; i<=dx; i++)
    vett[i] = tmp[i-sx];

}*/

void mergeSort(int* vett, int sx, int dx, int& counter){
  if(sx < dx){
    int c = (sx+dx)/2;

    counter += vett[sx];
    mergeSort(vett, sx, c, counter);
    mergeSort(vett, c+1, dx, counter);
    mergeSort(vett, sx, c, dx);
  }
}

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    int n; in >> n;
    int counter = 0;
    int vett[n];
    for(int i=0; i<n; i++) in >> vett[i];

    mergeSort(vett, 0, n-1, counter);

    out << counter << endl;
  }
}

#include <iostream>

using namespace std;

bool ese2(string* A,int size){
    for(int i=0;i<size-1;i++){
      if(A[i]==2*A[i+1] || 2*A[i]==A[i+1]) return true;
    }
    return false;
}

string* ese1(string* A,int size, int h){
  bool found = true;
  string* str_ptr;
  for(int i=0;i<size-1 && found;i++){
    int l=A[i].length()-h;
    int k=A[i+1].length()-h;
    if(A[i].substr(l,h)!=A[i+1].substr(k,h) found =false;
  }
  if (found)
    str_ptr=A;
  else
    str_ptr=NULL;

  return str_ptr;
}

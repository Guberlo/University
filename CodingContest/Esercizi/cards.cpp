#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string* get_bastoni_index(string a[],int n,int size){
  string* b=new string[size];
  for(int i=0;i<size;i++){
    for(int j=0;j<n;j++){
    if(a[j].substr(a[j].length()-1,1)=="B"|| a[j].substr(a[j].length()-1,1)=="b")
      b[i]=a[j];
    }
  }
  return b;
}

string* get_coppe_index(string a[],int n, int size){
  string* c=new string[size];
  for(int i=0;i<size;i++){
    for(int j=0;j<n;j++){
    if(a[j].substr(a[j].length()-1,1)=="C"|| a[j].substr(a[j].length()-1,1)=="c")
      c[i]=a[j];
    }
  }
  return c;
}



string* get_denari_index(string a[],int n, int size){
      string* d=new string[size];
      for(int i=0;i<size;i++){
        for(int j=0;j<n;j++){
        if(a[j].substr(a[j].length()-1,1)=="D"|| a[j].substr(a[j].length()-1,1)=="d")
          d[i]=a[j];
        }
      }
      return d;
    }


string* get_spade_index(string a[],int n,int size){
  string* s=new string[size];
  for(int i=0;i<size;i++){
    for(int j=0;j<n;j++){
    if(a[j].substr(a[j].length()-1,1)=="S"|| a[j].substr(a[j].length()-1,1)=="s")
      s[i]=a[j];
    }
  }
  return s;
}


void print(string a[],int n){
  for(int i=0;i<n;i++){
    cout <<a[i] <<", ";
  }
  cout << endl;
}

int main(){
    ifstream input;
    ofstream output;

    input.open("input.txt");
    output.open("output.txt");

    if(input.is_open()){
      while(!input.eof()){
        int cards=0;
        input >> cards;
        string cards_spec[cards];
        for(int i=0;i<cards;i++){
          input >> cards_spec[i];
        }
        int b,c,d,s=0;
        for(int i=0;i<cards;i++){
            int l=cards_spec[i].length();
            switch (cards_spec[i].substr(l-1,1)) {
              case 'B':
                b++;
              break;

              case 'C':
                c++;
              break;

              case 'D':
                d++;
              break;

              case 'S':
                s++;
              break;
            }
      }
    }

    input.close();
    output.close();

  return 0;
}

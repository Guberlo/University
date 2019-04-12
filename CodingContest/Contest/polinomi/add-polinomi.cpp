#include <iostream>
#include <fstream>
#include <string>
#include "monomio.h"
#include "polinomio.h"

using namespace std;

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    int n;
    in >> n;

    Polinomio* p =new Polinomio();
    for(int i=0; i<n; i++){
      string str;
      in >> str;
      if(str == "+" || str == "-"){
        p->setSegno(str[0]);
        i--;
      }
      else
        p->insert(str);
    }
    out << p->printSum() << endl;
  }

  return 0;
}

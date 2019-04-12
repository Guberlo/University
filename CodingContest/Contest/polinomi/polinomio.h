#ifndef POLINOMIO_H
#define POLINOMIO_H
#include "monomio.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Polinomio{
private:
  Monomio* testa;
  int count, maxG;
  char segno;

Monomio* insMon()
{
  Monomio* newm = new Monomio();
  newm->setNext(testa);
  testa = newm;
  count++;

  return newm;
}

public:
  Polinomio(){
    this->testa = NULL;
    this->count = 0;
    this->maxG = 0;
    this->segno = '+';
  }

  void setSegno(char s){
    this->segno = s;
  }

  Polinomio* insert(string str){
    string m="";

    for(int i=1; i<str.length(); i++){
      if((str[i]==')' || str[i] == '+' || str[i] == '-') && m.length()){
        Monomio* newm = insMon();
        newm->insert(m);

        if(segno == '-') newm->setBase(newm->getBase() * (-1));
        if(newm->getExp()>maxG)  maxG = newm->getExp();
        m = "";
      }
      m += str[i];
    }

    return this;
  }

  string fixExc(string s){
    if(s.substr(s.length()-3) == "x^0") s.erase(s.length()-3);
    if(s[0] == '+') s.erase(0,1);
    for(int i=0; i<s.length(); i++){
      if(s[i]=='^' && s[i+1]=='1' && ((s[i+2] == '+' || s[i+2] == '-') || i+2>=s.length())) s.erase(i,2);
      if((s[i] == '+' || s[i] == '-') && s[i+1] == '1' && s[i+2] == 'x')
        s.erase(i+1,1);
    }
    if(s[0] == '1' && s[1] == 'x')
      s.erase(0,1);

    return s;
  }

  string printSum()
  {
    stringstream ss;
    int sum;
    for(int i=maxG; i>=0; i--){
      Monomio* iter = testa;
      sum = 0;
      while(iter!=NULL){
        if(iter->getExp() == i)
          sum += iter->getBase();
        iter = iter->getNext();
      }
      if(sum)
        ss<<showpos<<sum<<"x^"<<noshowpos<<i;
    }
    string res = ss.str();
    res = fixExc(res);

    return res;
  }

};
#endif

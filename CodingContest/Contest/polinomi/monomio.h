#ifndef MONOMIO_H
#define MONOMIO_H
#include <iostream>
#include <string>

using namespace std;

class Monomio
{
private:
  Monomio *next;
  int exp;
  int base;

  char* sToc(string str){ //converts string to char array in order to use atoi
    char* newc = new char[str.length()];
    for(int i=0; i<str.length(); i++){
      newc[i] = str[i];
    }
    return newc;
  }
public:
  Monomio(){
    this->next = NULL;
    this->exp = 0;
    this->base = 0;
  }

  bool isNumber(char c){
    return (c>47 && c<58);
  }

  void setBase(int b){
    this->base = b;
  }

  void setBase(string b){
    int base;
    if(b =="+")
      this->base = 1;
    else if(b=="-")
      this->base = -1;
    else
      this->base = atoi(sToc(b));
  }

  void setExp(string e)
  {
    if(e.length())
      this->exp = atoi(sToc(e));
  }

  void insert(string str)
  {
    string str_b="", str_e="";
    bool flag = false;
    if(str[0]=='-')
      str_b+='-';
    if(isNumber(str[0]) || str[0]=='+' || str[0]=='x')
      str_b+='+';
    for(int i=0; i<str.length(); i++){
      if(isNumber(str[i]) && !flag)
        str_b+=str[i];
      if(str[i]=='x')
      {
        exp=base=1;
        flag = true;
        i+=2;
      }
      if(flag && i<str.length())
        str_e+=str[i];
    }
    setBase(str_b);
    setExp(str_e);
  }

  void setNext(Monomio* m){
    this->next = m;
  }

  Monomio* getNext(){
    return this->next;
  }

  int getBase(){
    return this->base;
  }

  int getExp(){
    return this->exp;
  }
};

#endif

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int passi = 0;
void hanoi(int n, int s, int d, int c, int ps, ofstream& out){

  if(n==1){
    passi++;
    if(passi == ps)
      out << s << " " << d << " " << endl;
  }
  else{
    hanoi(n-1, s, c, d, ps, out);
    passi++;
    if(passi == ps)
      out << s << " " << d << "" << endl;
    hanoi(n-1, c, d, s, ps, out);
  }
}

int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");

  while(!in.eof()){
    int n;
    in >> n;
    int p;
    in >> p;
    hanoi(n,1,3,2,p,out);
    passi = 0;
  }

  return 0;
}

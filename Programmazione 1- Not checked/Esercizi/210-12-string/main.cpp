#include <iostream>
#include <string>
using namespace std;

const int RIG = 5;
const int COL = 2;

double ese2(string V[][COL]){
    double count=0;
    for(int i=0;i<RIG;i++){
        for(int j=0;j<COL;j++){
            if(V[i][j].substr(V[i][j].length()-3,3)=="are")
                count++;
        }
    }
    double percentuale= (count/(RIG*COL))*100;

    return percentuale;
}

  int main(){
	string V[RIG][COL] = { "mangiaDre", "bereADS", "dormireS", "faSre", "dovere", "cagaDe", "smerciare", "commerciare", "dare", "dire" };
	cout << "Verbi alla prima coniugazione: " << ese2(V) << "%." << endl;
	return 0;
}


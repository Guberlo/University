#include <iostream>
#include <fstream>
using namespace std;

ofstream fout("output.txt");

int fibonacci(int n) {
	if (n<=1) return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int passo=0;

void hanoi(int n, int S, int D, int C, int passo_scelto) {
	if (n == 1) {
		passo++;
		if (passo==passo_scelto) {
			fout << S << " " << D << " " << endl;
		}
	}
	else {
		hanoi(n-1, S, C, D, passo_scelto);
		passo++;
		if(passo==passo_scelto)
			fout << S << " " << D <<  " " <<  endl;
			
		hanoi(n-1, C, D, S, passo_scelto);
	}
}
int main() {
	ifstream fin("input.txt");
	for (int y=0; y<100; y++) {
		int n;
		int passo_scelto;
		fin >> n;
		fin >> passo_scelto;
		hanoi(n,1,3,2, passo_scelto);
		passo=0;
	}
	return 0;
}



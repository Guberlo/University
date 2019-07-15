#include <iostream>
#include <fstream>

using namespace std;

int insertionSort(int *a, int n) {
	int k=0;
	int key;
	for (int i=1; i<n; i++) {
		int j=i-1;
		key = a[i];
		while (j>=0 && key<a[j]) {
			a[j+1] = a[j];
			k++;
			j--;
		} 
		a[j+1] = key;
		
	}
	return k;
	
}


int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		int n; input >> n; 
		int a[n];
		for (int i=0; i<n; i++) {
			input >> a[i];
		}
		output << insertionSort(a,n) << endl;
	}
}

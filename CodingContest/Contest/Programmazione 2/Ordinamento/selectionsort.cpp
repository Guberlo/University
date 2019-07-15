#include <iostream>
#include <fstream>

using namespace std;


int selectionSort(int *a, int n) {
	
	int distance; 
	
	for (int i=0; i<n-1; i++) {
		int min=i;
		int j;
		for (j=i+1; j<n; j++) {
			if (a[min]>a[j]) {
				min = j; 
			}
		}
		if (min != i) {
			swap(a[min],a[i]);
			distance += (min-i);
		}
		
	}
	
	return distance;
}


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		int n; input >> n;
		
		int a[n];
		
		for(int i=0; i<n; i++) {
			input >> a[i];
		}
		output << selectionSort(a,n) << endl;
	}
}

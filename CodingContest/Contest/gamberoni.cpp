#include <iostream>
#include <fstream>

using namespace std;

int index_of_min(double* a, int n) {
	int index_min = 0; 
	for (int i=0; i<n; i++) {
		if (a[i]<a[index_min]) {
			index_min = i;
		}
	}
	return index_min;
}

double max(double* a, int i, int n) {
	double max = a[i];
	for (; i<n; i++) {
		if (max<a[i]) {
			max = a[i];
		}
	}
	return max;
}


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	int k=0; 
	while (!input.eof()) {
		int n = 0; 
		input >> n; 
		double a[n]; 
		for (int i=0; i<n; i++) {
			input >> a[i];	
		}
		int index_min = 0;
		index_min = index_of_min(a,n);
		double guadagno = 0;
		double max_x = max(a,index_min+1,n);
		guadagno = max_x-a[index_min];
		output  << guadagno << endl;
		cout << "max=" << max_x << "\t min=" << a[index_min];
		cout << endl;

	}	
	
	input.close();
	output.close();
} 

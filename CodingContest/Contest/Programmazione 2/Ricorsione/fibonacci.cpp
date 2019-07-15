#include <iostream>
#include <fstream>

using namespace std;

int fibonacci(int n) {
	if (n<=1) return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		
		int n; input >> n;
		cout << n << endl;
		output << fibonacci(n) << endl; 
	}
}

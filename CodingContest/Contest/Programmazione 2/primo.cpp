#include <iostream>

using namespace std;

bool isPrimo(int n) {
	
	if (n == 1 || n == 2 || n == 3) {
		return true;
	}
	int mid = n/2;
	for (int i=2; i<mid; i++) {
		if (n%i == 0) return false;
	}
	return true;
}

int main() {
	cout << isPrimo(23);
}

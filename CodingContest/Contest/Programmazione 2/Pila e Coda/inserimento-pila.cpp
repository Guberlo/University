#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Pila {
	
	H **v;
	
	int top; 
	int n; 
	int length;
	public:
		Pila() {
			v = new H*[200];
			top = n = 0; 
			length = 200;
		}
		
		Pila<H> *push(H x) {
			if (n>=length) return this;
			v[top] = new H(x);
			top++;
			n++;
			return this;
		}
		
		
		void print(ofstream &output) {
			for (int i=n-1; i>=0; i--) {
				output << *v[i] << " ";
			}
			output << endl;
		}

};


int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		while (!input.eof()) {
		string type; input >> type;
		int n; input >> n; 
		if (type == "int" || type == "bool") {
			Pila<int> *c = new Pila<int>(); 
			int x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->push(x);
			}
			c->print(output);
		}
		if (type == "double") {
			Pila<double> *c = new Pila<double>(); 
			double x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->push(x);
			}
			c->print(output);
		}
		
		if (type == "char") {
			Pila<char> *c = new Pila<char>(); 
			char x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->push(x);
			}
			c->print(output);
		}
		
	}
	}
}

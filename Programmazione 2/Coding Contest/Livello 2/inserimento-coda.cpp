#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Coda {
	
	H **v; 
	int n; 
	int length;
	int head, tail;
	public:
		Coda() {
			v = new H*[200];
			n = 0; 
			length = 200; 
			head = tail = 0;
		}
		
		Coda<H> *enqueue(H x) {
			if (n >= length) return this;
			v[tail] = new H(x);
			tail = (tail+1)%length;
			n++; 
			return this;
		}
		
		void print(ofstream &output) {
			for (int i=0; i<n; i++) {
				output << *v[i] << " ";
			}
			output << endl;
		}
};

int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		string type; input >> type;
		int n; input >> n; 
		if (type == "int" || type == "bool") {
			Coda<int> *c = new Coda<int>(); 
			int x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->enqueue(x);
			}
			c->print(output);
		}
		if (type == "double") {
			Coda<double> *c = new Coda<double>(); 
			double x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->enqueue(x);
			}
			c->print(output);
		}
		
		if (type == "char") {
			Coda<char> *c = new Coda<char>(); 
			char x; 
			for (int i=0; i<n; i++) {
				input >> x; 
				c->enqueue(x);
			}
			c->print(output);
		}
		
	}
}

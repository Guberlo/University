#include <iostream>
#include <fstream>
#include  <sstream>

using namespace std;

template <class H> class Pila {
	
	H **v;
	int top, n; 
	int length;
	
	public:
		Pila() {
			v = new H*[200];
			length = 200; 
			n = top = 0; 
		}
		Pila<H> *push(H x) {
			if (top>=length) return this; 
			v[top] = new H(x);
			top++;
			n++;
			return this;
		}
		H *pop() {
			if(top<0) return NULL;
			H *x = v[top];
			top--;
			n--;
			return x; 
		}
		
		void print(ofstream &output) {
			for (int i=top-1; i>=0; i--) {
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
			Pila<int> *p = new Pila<int>();
			int x;
			string query; 
			for (int i=0; i<n; i++) {
				input >> query; 
				cout << query;
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->push(x);
				}
				else {
					p->pop();
				}
			}
			p->print(output);
		}
		if (type == "double") {
			Pila<double> *p = new Pila<double>();
			double x;
			string query; 
			for (int i=0; i<n; i++) {
				input >> query; 
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->push(x);
				}
				else {
					p->pop();
				}
			}
			p->print(output);
		}
		if (type == "char") {
			Pila<char> *p = new Pila<char>();
			char x;
			string query; 
			for (int i=0; i<n; i++) {
				input >> query; 
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->push(x);
				}
				else {
					p->pop();
				}
			}
			p->print(output);
		}
	}
	
}


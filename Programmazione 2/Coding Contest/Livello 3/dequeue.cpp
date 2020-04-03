#include <iostream>
#include <fstream>
#include  <sstream>

using namespace std;


template <class H> class Coda {
	H **v;
	int head,tail, n;
	int length;

	public:
		Coda() {
			v = new H*[200];
			head = tail = n = 0;
			length = 200;
		}

		Coda<H> *enqueue(H x) {
			if (n >= length) return this;
			v[tail] = new H(x);
			tail = (tail+1)%length;
			n++;
			return this;
		}

		H *dequeue() {
			if(n==0) return NULL;
			H *r = v[head];
			head = (head+1)%length;
			n--;
			return r;
		}

		void print(ofstream &output) {
			for (int i=head; i<tail; i++) {
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
			Coda<int> *p = new Coda<int>();
			int x;
			string query;
			for (int i=0; i<n; i++) {
				input >> query;
				cout << query;
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->enqueue(x);
				}
				else {
					p->dequeue();
				}
			}
			int *_x = p->dequeue();
			while (_x) {
				output << *_x  << " ";
				_x = p->dequeue();
			}
			output << endl;
		}
		if (type == "double") {
			Coda<double> *p = new Coda<double>();
			double x;
			string query;
			for (int i=0; i<n; i++) {
				input >> query;
				cout << query;
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->enqueue(x);
				}
				else {
					p->dequeue();
				}
			}
			double *_x = p->dequeue();
			while (_x) {
				output << *_x  << " ";
				_x = p->dequeue();
			}
			output << endl;
		}
		if (type == "char") {
			Coda<char> *p = new Coda<char>();
			char x;
			string query;
			for (int i=0; i<n; i++) {
				input >> query;
				cout << query;
				if (query[0] == 'i') {
					stringstream buffer (query.substr(1));
					buffer >> x;
					p->enqueue(x);
				}
				else {
					p->dequeue();
				}
			}
			char *_x = p->dequeue();
			while (_x) {
				output << *_x  << " ";
				_x = p->dequeue();
			}
			output << endl;
		}
	}

}

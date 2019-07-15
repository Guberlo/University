#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;




template <class H> class Queue {
	
	H **vector;
	int head, tail, n; 
	int len;
	
	public:
		Queue() {
			len = 200;
			head = tail = n = 0; 
			vector = new H*[len];
		}
		
		Queue<H> *enqueue(H x) {
			if (n > 200) return this; 
			vector[tail] = new H(x);
			tail = (tail+1)%len;
			n++;
			return this;
		}
		H *dequeue() {
			if (n==0) return  NULL;
			H *x = vector[head];
			head = (head+1)%len;
			n--;
			return x; 
		}
		void print(ofstream &output) {
			for (int i=head; i<tail; i++) {
				output << *vector[i] << " ";
			}
			output << endl;
		}
		void print() {
			for (int i=head; i<tail; i++) {
				cout << *vector[i] << " ";
			}
			cout << endl;
		}
		
		
};

template <class H> class Stack {
	H **vector; 
	int top, n;
	int len; 
	
	public:
		Stack() {
			len = 200; 
			top = n = 0; 
			vector = new H*[len];	
		}
		
		Stack<H> *push(H x) {
			if (n >= len) return this;
			vector[top] = new H(x);
			top++; 
			n++;
			return this;
		}
		H *pop() {
			if (n==0) return NULL; 
			//delete vector[top];
			top--;
			n--;
			H *x = vector[top];
				
			return x;
			//else return NULL;
		}
		
		int size() {
			return n; 
		}
		
		void print() {
			for (int i=top-1; i>=0; i--) {
				cout << *vector[i] << " ";
			}
			cout << endl;
		} 
		Queue<H> *travasa(Queue<H> *q) {
			H *x = pop();
			//cout << endl << "Indirizzo di Queue dentro la funzione:  " << q;
			while (x) {
				//cout << endl << "Inserisco " << *x << " in Q" << endl; 
				q->enqueue(*x);
				x = pop(); 
			}	
			return q;
		}
	
		
};


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		string type;
		input >> type;
		int n; 
		input >> n; 
		
		if (type == "int" || type == "bool") {
			Queue<int> *q = new Queue<int>();
			Stack<int> *s = new Stack<int>();
			int value;
			int *a;
			for (int i=0; i<n; i++) { // read N operations 
				
				string query; 
				input >> query;
				if (query[0] == 'e') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					q->enqueue(value); 
				}
				if (query == "pop") s->pop();
				
				if (query[0] == 'p' && query[1] == ':') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					s->push(value); 
				}
				
				if (query == "dequeue") q->dequeue();
				if (query == "travasa") {
					
					s->travasa(q);
				}
				
			}
			// Output
			q->print(output);
		}
		if (type == "double") {
			Queue<double> *q = new Queue<double>();
			Stack<double> *s = new Stack<double>();
			double value;
			double *a;
			for (int i=0; i<n; i++) { // read N operations 
				
				string query; 
				input >> query;
				if (query[0] == 'e') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					q->enqueue(value); 
				}
				if (query == "pop") s->pop();
				
				else if (query[0] == 'p') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					s->push(value); 
				}
				
				if (query == "dequeue") q->dequeue();
				if (query == "travasa") {
					
					s->travasa(q);
				}
				
			}
			// Output
			q->print(output);
		}
		if (type == "char") {
			Queue<char> *q = new Queue<char>();
			Stack<char> *s = new Stack<char>();
			char value;
			char *a;
			for (int i=0; i<n; i++) { // read N operations 
				
				string query; 
				input >> query;
				if (query[0] == 'e') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					q->enqueue(value); 
				}
				if (query == "pop") s->pop();
				
				else if (query[0] == 'p') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> value;
					s->push(value); 
				}
				
				if (query == "dequeue") q->dequeue();
				if (query == "travasa") {
					
					s->travasa(q);
				}
				
			}
			// Output
			q->print(output);
		}
	}	
}


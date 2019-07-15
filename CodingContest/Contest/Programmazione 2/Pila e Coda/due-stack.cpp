#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


template <class H> class Stack {
	
	H *vector;
	int n;
	int top; 
	
	public:
		
		Stack() {
			vector = new H[200];
			this->n = 0; 
			top = 0; 
		}
		
		void push(H x) {
			if (n >= 200) return;
			vector[top] = x;
			top++;
			n++;
		}
		H *pop() {
			if (top <= 0) {
				return NULL; 
			} 
			top--; 
			H *x = new H(vector[top]);
			n--;
			return x; 
		}
		int size() {
			return n; 
		}
		
};

template <class H> class Queue {
	// Coda implementata con due Stack
	Stack<H> *s1, *s2; 
	
	public:
		Queue() {
			s1 = new Stack<H>();
			s2 = new Stack<H>();	
		}
		
		Queue<H> *enqueue(H x) {
			s1->push(x);
			return this;	
		}
		Queue<H> *dequeue() {
			
			H *x = s1->pop();
			while (x) {
				s2->push(*x);
				x = s1->pop();
			}
			s2->pop();
			x = s2->pop();
			while (x) {
				s1->push(*x);
				x = s2->pop();
			}
			
			return this;
		}
		
		void print(ofstream &out) {
			
			H *x = s1->pop();
			while (x) {
				s2->push(*x);
				x = s1->pop();
			}
			
			x = s2->pop();
			while (x) {
				out << *x << " ";
				x = s2->pop();
			}
			out << endl;
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
		
		if (type == "int" || type =="bool") {
			Queue<int> *q = new Queue<int>(); 
			
			for (int i=0; i<n; i++) {
				string query; 
				input >> query;
				
				if (query[0] == 'i') {
					stringstream s(query.substr(1,query.size()));
					int x;
					s >> x; 
					q->enqueue(x);
				} 
				else q->dequeue();
				
			}
			q->print(output);
		}
		if (type == "double") {
			Queue<double> *q = new Queue<double>(); 
			
			for (int i=0; i<n; i++) {
				string query; 
				input >> query;
				
				if (query[0] == 'i') {
					stringstream s(query.substr(1,query.size()));
					double x;
					s >> x; 
					q->enqueue(x);
				} 
				else q->dequeue();
				
			}
			q->print(output);
			
		}
		if (type == "char") {
			Queue<char> *q = new Queue<char>(); 
			
			for (int i=0; i<n; i++) {
				string query; 
				input >> query;
				
				if (query[0] == 'i') {
					stringstream s(query.substr(1,query.size()));
					char x;
					s >> x; 
					q->enqueue(x);
				} 
				else q->dequeue();
				
			}
			q->print(output);
		}
	}	
}

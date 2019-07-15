#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H> class Stack {
	H *v;
	int n; 
	int top;
	int len;
	
	public:
		Stack() {
			len = 200;
			v = new H[len];
			n = top = 0; 
		}
		
		Stack<H> *push(H x) {
			v[top] = x; 
			top++; 
			n++; 
			return this; 
		}
		H pop()  {
			top--;
			n--;
			
			return v[top];
		}
		
		H getHead() {
			return v[top-1];
		}
		
		bool isEmpty() {
			return top<=0;
		}
		
		friend bool operator<(const Stack<H> x, const Stack<H> y) {
			
			Stack<H> obj1 = x;
			Stack<H> obj2 = y;
			
			if  (obj1.getHead() <= obj2.getHead() || obj1.getHead() == obj2.getHead()) return true;
			else return false;
		}
		friend ostream& operator<<(ostream &out, const Stack<H> &obj) {
			Stack<H> x = obj;
			
			for (int i=x.top-1; i>=0; i--) {
				out << x.v[i] << " ";
			}
			return out;	
		}
};

template <class H> class Nodo {
	Nodo<H> *next; 
	H *key; 
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			next = NULL; 
		}
		Nodo(H *key) {
			this->key = key;
			next = NULL; 
		}		
		
		void setNext(Nodo<H> *next) {
			this->next = next;
		}
		void setKey(H *key) {
			this->key = key;
		}
		
		Nodo<H> *getNext() {
			return next;
		}
		H *getPtrKey() {
			return key;	
		}
		H getKey() {
			return *key;
		}
};

template <class H> class List {
	// Order List
	Nodo<H> *header;
	
	public:
		List() {
			H *tmp = NULL;
			header = new Nodo<H>(tmp); 
		}
		
		List<H> *ins(H *key) {
			
			Nodo<H> *nodo =  new Nodo<H>(key);
			Nodo<H> *prev = header;
			Nodo<H> *tmp = header->getNext();
			
			while (tmp &&  tmp->getKey() < *key ) {
				prev = tmp;
				tmp = tmp->getNext();
			}
			
			prev->setNext(nodo);
			nodo->setNext(tmp);
			return this;			
		}
		
		List<H> *canc(H *key) {
			Nodo<H> *prev = header;
			Nodo<H> *tmp = header->getNext();
			
			while (tmp) {
				if (tmp->getPtrKey() == key) {
					prev->setNext(tmp->getNext());

					return this;
				}
				prev = tmp;
				tmp = tmp->getNext();
			}
			return this;
		}
		
		void print(ofstream &out) {
			Nodo<H> *tmp = header->getNext();
			
			while (tmp) {
				out << tmp->getKey() << " ";
				tmp = tmp->getNext();
			}
		}
		void print() {
			Nodo<H> *tmp = header->getNext();
			
			while (tmp) {
				cout << tmp->getKey() << " ";
				tmp = tmp->getNext();
			}
		}
		
		H *getHeader() {
			return header->getNext()->getPtrKey();
		}
	
};

template <class H> class MultiStack {
	List< Stack<H> > *ms;
	
	public:
		MultiStack() {
			ms = new List< Stack<H> >();
		}
		
		MultiStack<H> *newPush(H key) {
			Stack<H> *newStack =  new Stack<H>();
			
			newStack->push(key);
			
			ms->ins(newStack);
			return this;
		}
		
		MultiStack<H> *push(H key) {
			Stack<H> *s =  ms->getHeader();
			ms->canc(s);
			s->push(key);
			ms->ins(s);
			return this;
		}
		MultiStack<H> *pop() {
			Stack<H> *s =  ms->getHeader();
			
			ms->canc(s);
			s->pop();
			if (!s->isEmpty()) ms->ins(s);
			return this;
		}
		
		void print(ofstream &out) {
			ms->print(out);
			out << endl;
		}
		
		MultiStack<H> *print() {
			ms->print();
			cout << endl;
			return this;
		}
};


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		string type;
		int n; 
		
		input >> type;
		input >> n; 
		
		if (type == "int") {
			MultiStack<int> *ms = new MultiStack<int>();
			int x;
			for (int i=0; i<n; i++) {
				string query;
				input >> query;
				
				if (query[0] == 'n') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> x;
					ms->newPush(x);
				}
				if (query[0] == 'p' && query[1] ==':') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> x;
					ms->push(x);
				}
				if (query == "pop") {
					ms->pop();
				}
			}
			ms->print(output);
		}
		if (type == "double") {
			MultiStack<double> *ms = new MultiStack<double>();
			double x;
			for (int i=0; i<n; i++) {
				string query;
				input >> query;
				
				if (query[0] == 'n') {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> x;
					ms->newPush(x);
				}
				if (query[0] == 'p' && query !="pop") {
					stringstream buffer(query.substr(2,query.size()));
					buffer >> x;
					ms->push(x);
				}
				if (query == "pop") {
					ms->pop();
				}
			}
			ms->print(output);
		}
	}
}
 

#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;
// List
template <class H> class Nodo {
	
	H *key;
	Nodo<H> *next; 
	
	public:
		Nodo(H key) {
			next = NULL;
			this->key = new H(key);
		}
		
		// set
		void setNext(Nodo<H> *next) {
			this->next = next;
		}
		void setKey(H key) {
			
		}
		// getter
		Nodo<H> *getNext() {
			return next;
		}
		H getKey()  {
			return *key; 
		}
	
};

template <class H> class List {
	Nodo<H> *header, *current; 
	int n; 
	
	public:
		List() {
			current = header = NULL;
			n = 0; 
		}
		
		List<H> *ins(H key) {
			Nodo<H> *newNode = new Nodo<H>(key); 
			n++;
			
			if (!header) {
				header = newNode; 
				return this;
			}
			
			Nodo<H> *tmp = header;
			Nodo<H> *prev = NULL;
			while (tmp && tmp->getKey() < key ) { 
				prev = tmp;
				tmp = tmp->getNext();
			}
			if (!prev) {
				newNode->setNext(header);
				header = newNode;
				return this;
			}
			prev->setNext(newNode);
			newNode->setNext(tmp);
			
			
			return this; 
			
		}
		
		void print() {
			Nodo<H> *tmp = header; 
			
			while (tmp) {
				cout << tmp->getKey() << " ";
				tmp = tmp->getNext();
			}
		}
		
		// iterator
		void reset() {
			current = header; 
		}
		H *next() {
			if (!current) return NULL;
			H *x = new H(current->getKey());
			current = current->getNext();
			return x; 
		}
	
};

template <class H> class NodoG {
	H *key; 
	List<H> *edges;
	int numEdges;
	
	public:
		NodoG(H key) {
			this->key = new H(key);
			edges = new List<H>(); 
		}
		
		void addEdges(H key) {
			edges->ins(key);
			numEdges++;
		}	
		
		// getter
		H getKey() const {
			return *key;
		}
		List<H> *getEdges() {
			return edges;
		}
		
		friend bool operator<(const NodoG<H> x, const NodoG<H> y) {
			if (x.getKey() < y.getKey()) return true;
			else return false;
		} 
		friend bool operator<(const NodoG<H> x, const H y) {
			if (x.getKey() == y) return true;
			else return false;
		} 
		
		friend ostream& operator<<(ostream &out, const NodoG<H> obj) {
			NodoG<H> x = obj; 
			
			out << "(" << x.getKey();
			// (A
			
			List<H> *edges = x.getEdges(); 
			
			edges->reset();
			H *h = edges->next();
			while (h) {
				out << " " << *h;
				h = edges->next();
			}
			out << ")";
			return out;
		}
};

template <class H> class Graph {
	
	List< NodoG<H> > *nodes;
	
	public:
		Graph() {
			nodes = new List< NodoG<H> >();
		}
		
		Graph<H> *addNode(H key) {
			NodoG<H> *nodo = new NodoG<H>(key);
			nodes->ins(*nodo);
			return this;
		}
		Graph<H> *addEdge(H x, H y) {
			nodes->reset();
			NodoG<H>  *h = nodes->next();
			while (h) {
				//cout << "h->getKey(): " << h->getKey() << "\t x: " << x << "\t y: " << y << endl;
				if (h->getKey() == x) {
					h->addEdges(y);
				}
				h = nodes->next();
			}
			return this;
		}
		
		void print(ofstream &out) {
			nodes->reset();
			NodoG<H>  *h = nodes->next();
			while (h) {
				out << *(h)  << " ";
				h = nodes->next();
			}
		}
		
		
};

/*
int main() {
	/*
	List<int> *l = new List<int>();
	
	l->ins(13)->ins(13)->ins(42)->ins(23)->ins(15)->ins(11)->ins(8);
	l->reset();
	int *x = l->next();
	while (x) {
		cout << *x << " ";
		x = l->next();
	}
	
	Graph<char> *g = new Graph<char>(); 
	
	// 5 6 char A T H G B (T,A) (T,H) (T,B) (H,G) (H,B) (B,G) 
	
	g->addNode('A')->addNode('T')->addNode('H')->addNode('G')->addNode('B');
	g->addEdge('T','A')->addEdge('T','H')->addEdge('T','B')->addEdge('H','G')->addEdge('H','B')->addEdge('B','G');
	g->print();
	
	
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	
	
}*/


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		
		int n; input >> n; // number of nodes
		int m; input >> m; // number of edge
		
		
		string type; input >> type; 
		if (type == "int") {
			Graph<int> *g = new Graph<int>();
			int node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->addNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				g->addEdge(x,y);
				
			}
			g->print(output);
			output << endl;
		}
		if (type == "char") {
			Graph<char> *g = new Graph<char>();
			char node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->addNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				
				g->addEdge(x,y);
				
			}
			g->print(output);
			output << endl;
		}
		if (type == "double") {
			Graph<double> *g = new Graph<double>();
			double node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->addNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				g->addEdge(x,y);
				
			}
			g->print(output);
			output << endl;
		}

	}
}

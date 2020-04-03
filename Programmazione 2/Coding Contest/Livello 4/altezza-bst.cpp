#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


template <class H> class Nodo  {
	Nodo<H> *left, *right, *p;
	H *key;
	
	public: 
		Nodo(H key) {
			this->key = new H(key);
			left = right = p = NULL;
			
		}
		
		// setter
		void setLeft(Nodo<H> *left) {
			this->left = left;
		}
		void setP(Nodo<H> *p) {
			this->p = p;
		}
		void setRight(Nodo<H> *right) {
			this->right = right;
		}
		void setKey(H key) {
			this->key = new H(key);
		}
	
		// getter
		Nodo<H> *getLeft() {
			return left;
		}
		Nodo<H> *getRight() {
			return right;
		}
		Nodo<H> *getP() {
			return p;
		}
		H getKey() {
			return *key;
		}
		
		
};

int max(int a, int b) {
	return a>b? a:b; 
}

template <class H> class BST {
	Nodo<H> *root;
	
	Nodo<H> *_search(Nodo<H> *x, H key) {
		if (x) {
			if (x->getKey() == key) return x;
			else if (x->getKey() < key) return _search(x->getRight(),key);
			else return _search(x->getLeft(),key);
		}
		return NULL;
	}
	
	Nodo<H> *_succ(Nodo<H> *x) {
		if (x->getRight()) return _min(x->getRight());
		
		Nodo<H> *p =  x->getP();
		
		while (p && p->getKey() < x->getKey()) {
			p = p->getP();
		}
		return p; 
	}
	
	void _canc(Nodo<H> *x, H key) {
		Nodo<H> *tmp = _search(x,key);
		if(!tmp) return;
		
		// Devo cancellare nodo tmp
		Nodo<H> *p = tmp->getP();
		
		if (!tmp->getLeft() || !tmp->getRight()) { // 1° 2° caso
			Nodo<H> *figlio = tmp->getLeft();
			if (tmp->getRight()) figlio = tmp->getRight();
			
			if (!p) {
				root = figlio;
			}
			else {
				if (tmp == p->getLeft()) p->setLeft(figlio);
				else p->setRight(figlio);
			}
			
			if (figlio) figlio->setP(p);
			
		}
		else {
			Nodo<H> *succ = _succ(tmp);
			tmp->setKey(succ->getKey());
			_canc(tmp->getRight(),succ->getKey());
		}
		return;
	}
	
	Nodo<H> *_min(Nodo<H> *x) {
		while  (x->getLeft())
			x = x->getLeft();
		return x;
	}
	
	int _altezza(Nodo<H> *tmp) {
			if(!tmp) return 0;
			return max(_altezza(tmp->getLeft()),
					   _altezza(tmp->getRight())
					) + 1;
	}
	public:
		BST() {
			root = NULL;
		}
		
		BST<H> *ins(H key) {
			Nodo<H> *nodo = new Nodo<H>(key);
			
			if (!root) {
				root = nodo;
				return this;
			}
			
			Nodo<H> *tmp =  root;
			Nodo<H> *p = NULL;
			
			while (tmp) {
				p = tmp; 
				if (tmp->getKey() < key) tmp = tmp->getRight();
				else tmp = tmp->getLeft();
			}
			nodo->setP(p);
			if (p->getKey() < key) p->setRight(nodo);
			else p->setLeft(nodo);
			return this;
		}
		
		BST<H> *canc(H key) {
			_canc(root,key);
		}
		
		int altezza() {
			return _altezza(root);
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
		
		if (type == "int") {
			BST<int> *t = new BST<int>();
			int val; 
			
			for (int i=0; i<n; i++) {
				string query; 
				input >> query;
				
				if (query[0] == 'i') {
					stringstream buffer(query.substr(4,query.size()));
					buffer >> val;
					t->ins(val);
				}
				if (query[0] == 'c') {
					stringstream buffer(query.substr(5,query.size()));
					buffer >> val;
					t->canc(val);
				}
				
			}
			output << t->altezza() << endl; 
		}
		if (type == "double") {
			BST<double> *t = new BST<double>();
			double val; 
			
			for (int i=0; i<n; i++) {
				string query; 
				input >> query;
				
				if (query[0] == 'i') {
					stringstream buffer(query.substr(4,query.size()));
					buffer >> val;
					t->ins(val);
				}
				if (query[0] == 'c') {
					stringstream buffer(query.substr(5,query.size()));
					buffer >> val;
					t->canc(val);
				}
				
			}
			output << t->altezza() << endl; 
		}
		
	}
}

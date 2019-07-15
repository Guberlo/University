#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Start 16:12

template <class H>  class Nodo {
	
	H *key;
	Nodo<H> *right, *left, *p;
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			right = left = p = NULL;
		}	
		
		// setter
		void setRight(Nodo<H> *right) {
			this->right = right;
		}
		void setLeft(Nodo<H> *left) {
			this->left = left;
		}
		void setP(Nodo<H> *p) {
			this->p = p;
		}
		void setKey(H key) {
			this->key = new H(key);
		}
		
		// getter
		Nodo<H> *getP() {
			return p;
		}
		Nodo<H> *getRight() {
			return right;
		}
		Nodo<H> *getLeft() {
			return left;
		}
		H getKey() {
			return *key;
		}
};

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
	
	Nodo<H> *_min(Nodo<H> *x) {
		while (x->getLeft())
			x = x->getLeft();
		return x;
	}
	
	Nodo<H> *_succ(Nodo<H> *x) {
		if (x->getRight()) return _min(x->getRight());
		
		Nodo<H> *p = x->getP();
		
		while (p && p->getKey() < x->getKey()) {
			p = p->getP();
		}
		return p; 
	}
	

		
	void _canc(Nodo<H> *x, H key) {
		Nodo<H> *tmp = _search(x,key);
		
		if (!tmp) return;
		
		Nodo<H> *p = tmp->getP();
		
		if (!tmp->getLeft() || !tmp->getRight()) {
			Nodo<H> *figlio = tmp->getLeft();
			if (!figlio) figlio = tmp->getRight();
			
			if (!p) {
				root = figlio;
			}
			else {
				if (p->getLeft() == tmp) p->setLeft(figlio);
				else p->setRight(figlio);	
			}
			if (figlio) figlio->setP(p);
				
		}
		else {
			Nodo<H> *succ = _succ(tmp);
			tmp->setKey(succ->getKey());
			_canc(tmp->getRight(), succ->getKey()); 
		}
		
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
			
			Nodo<H> *tmp = root;
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
		
		int prof(H key) {
			Nodo<H> *tmp = _search(root,key);
			if (tmp) {
				Nodo<H> *p = tmp->getP();
				int count = 0; 
				while (p) {
					p = p->getP();
					count++;
				}
				return count;

			}
			else return -1;
		}
};

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		string type;
		input >> type;
		int n, m; 
		input >> n; 
		input >> m; 
		
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
			for (int i=0; i<m; i++) {
				input >> val; 
				output << t->prof(val) << " ";
			}
			output << endl; 
		
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
			
			for (int i=0; i<m; i++) {
				input >> val; 
				output << t->prof(val) << " ";
			}
			output << endl; 
		
		}
	}
}

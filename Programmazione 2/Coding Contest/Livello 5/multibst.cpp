#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H> class Nodo {
	Nodo<H> *left, *right, *p;
	H *key;
	int mul;
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			left = right = p = NULL;
			mul = 1;
		}	
		
		// setter
		void setLeft(Nodo<H> *left) {
			this->left = left;
		}
		void setRight(Nodo<H> *right) {
			this->right = right;
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
		Nodo<H> *getLeft() {
			return left;
		}
		Nodo<H> *getRight() {
			return right;
		}
		H getKey() {
			return *key;
		}
		int getMul() {
			return mul;
		}
		
		void mul_ins() {
			mul++;
		}
		void mul_canc() {
			mul--;
		}
		void setMul(int mul) {
			this->mul = mul;
		}
	
};

template <class H> class MultiBST {
	
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
		tmp->mul_canc();
		if (tmp->getMul() == 0) {
			_cancNodo(x,key);
		}
		
		
	}
	
	void _cancNodo(Nodo<H> *x, H key) {
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
				if (tmp == p->getLeft()) p->setLeft(figlio);
				else p->setRight(figlio);
			}
			if (figlio) figlio->setP(p);
		}
		else {
			Nodo<H> *succ = _succ(tmp);
			tmp->setKey(succ->getKey());
			tmp->setMul(succ->getMul());
			_cancNodo(tmp->getRight(), succ->getKey());	
		}
		
	}
	
	void _inorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			_inorder(x->getLeft(),out); 
			for (int i=0; i<x->getMul(); i++) {
				out << x->getKey() << " "; 
			}
			_inorder(x->getRight(),out); 
		}
	}
	void _postorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			_postorder(x->getLeft(),out); 
			_postorder(x->getRight(),out); 
			for (int i=0; i<x->getMul(); i++) {
				out << x->getKey() << " "; 
			}
			
		}
	}
	void _preorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			for (int i=0; i<x->getMul(); i++) {
				out << x->getKey() << " "; 
			}
			_preorder(x->getLeft(),out); 
			_preorder(x->getRight(),out); 
		}
	}

	public:
		MultiBST() {
			root = NULL;
		}
		
		MultiBST<H> *ins(H key) {
			
			Nodo<H> *nodo = _search(root,key);
			if(nodo) {
				nodo->mul_ins();
				return this;
			}
			nodo = new Nodo<H>(key);
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
		MultiBST<H> *canc(H key) {
			_canc(root,key);
		}
		void print(string query, ofstream &out) {
			if (query == "inorder") {
				_inorder(root,out);
			}
			else if (query == "postorder") _postorder(root,out);
			else _preorder(root,out);
			
			out << endl; 
		}
		
};

int main() {
	ifstream input("input.txt");
	ofstream out("output.txt");
	
	while (!input.eof()) {
		
		string type; 
		input >> type; 
		int n; 
		input >> n; 
		string query;
		input >> query;
		
		if (type == "int" || type == "bool") {
			MultiBST<int> *t = new MultiBST<int>();
			int val;
			for (int i=0; i<n; i++) {
				string x;
				input >> x;
				
				if (x[0] == 'i') {
					stringstream buffer(x.substr(4,x.size()));
					buffer >> val;
					t->ins(val);
					
				}
				if (x[0] == 'c') {
					stringstream buffer(x.substr(5,x.size()));
					buffer >> val;
					t->canc(val);
				}	
			}
			t->print(query,out);
			
			
		}
		if (type == "double") {
			MultiBST<double> *t = new MultiBST<double>();
			double val;
			for (int i=0; i<n; i++) {
				string x;
				input >> x;
				
				if (x[0] == 'i') {
					stringstream buffer(x.substr(4,x.size()));
					buffer >> val;
					t->ins(val);
				}
				if (x[0] == 'c') {
					stringstream buffer(x.substr(5,x.size()));
					buffer >> val;
					t->canc(val);
				}	
			}
			t->print(query,out);
			
			
		}
		if (type == "char") {
			MultiBST<char> *t = new MultiBST<char>();
			char val;
			for (int i=0; i<n; i++) {
				string x;
				input >> x;
				
				if (x[0] == 'i') {
					stringstream buffer(x.substr(4,x.size()));
					buffer >> val;
					t->ins(val);
				}
				if (x[0] == 'c') {
					stringstream buffer(x.substr(5,x.size()));
					buffer >> val;
					t->canc(val);
				}	
			}
			t->print(query,out);
			
			
		}
	}
}

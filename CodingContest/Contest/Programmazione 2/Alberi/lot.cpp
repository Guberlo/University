#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class H> class Nodo {
	
	Nodo<H> *right, *left, *p; 
	H *key;
	
	public:
		
		Nodo(H key) {
			this->key = new H(key); 
			right = left = p = NULL; 
		}
		
		// setter
		void setP(Nodo<H> *p) {
			this->p = p;
		}
		void setLeft(Nodo<H> *left) {
			this->left = left;
		}
		void setRight(Nodo<H> *right) {
			this->right = right; 
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
};

template <class H> class BST {
	
	Nodo<H> *root;
	int n; 
	
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

	void _preorder(Nodo<H> *x, ostream& out) {
		if (x) {
			out << x->getKey() << " ";
			_preorder(x->getLeft(),out);
			_preorder(x->getRight(),out);
		}
	}

	public: 
		BST() {
			n = 0;
			root = NULL; 
		}	
		
		BST<H> *ins(H key) {
			Nodo<H> *nodo = new Nodo<H>(key);
			n++;
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
			n--;
			return this;
		}
		bool isEmpty() {
			return root == NULL; 
		}
		friend ostream& operator<<(ostream& out, const BST<H> &x) {
			BST<H> obj = x;
			obj._preorder(obj.root,out);
			return out;
		}
		int size() {
			return n; 
		}
};

// FINE ALBERO



template <class H> class NodoL {
	NodoL<H> *next;
	H *key;
	
	public:
		NodoL(H *key) {
			this->key = key;
			next = NULL;
		}
		
		NodoL<H> *getNext() {
			return next;
		}
		H *getPtrKey() {
			return key;
		}
		
		// setter
		void setNext(NodoL<H> *next) {
			this->next = next;
		}
		void setPtrKey(H *key) {
			this->key = key;
		}
};

template <class H> class List {
	
	NodoL< BST<H> > *header; 
	int k; 
	
	public:
		List(int k) {
			this->k = k; 
			header = NULL; 
		}
		
		List<H> *ins(H key) {
			// 1. Se l'header è null, creo nuovo albero e inserisco elemento, successivamente header = nuovoNodo;
			if (!header) {
				BST<H> *t = new BST<H>();
				t->ins(key);
				NodoL< BST<H> > *nuovoNodo = new NodoL< BST<H> >(t);
				header = nuovoNodo; 
				return this;	
			}
			
			BST<H> *t = header->getPtrKey();
			
			if (t->size() < k) {
				t->ins(key);
				header->setPtrKey(t);
			} 
			
			else {
				BST<H> *nuovoAlbero = new BST<H>();
				nuovoAlbero->ins(key);
				NodoL< BST<H> > *nodo = new NodoL< BST<H> >(nuovoAlbero);
				
				NodoL< BST<H> > *tmp = header;
				header = nodo;
				nodo->setNext(tmp);
			}			
			return this;	
		}
		
		void print(ofstream &out) {
			NodoL< BST<H> > *tmp = header;
			while (tmp) {
				out << *(tmp->getPtrKey()) << ""; 
				tmp = tmp->getNext();
			}
		}
		
		
		void canc(H key) {
			NodoL< BST<H> > *prev = NULL;
			NodoL< BST<H> > *tmp = header;
			while (tmp) {
				prev = tmp;
				BST<H> *t = tmp->getPtrKey();
				t->canc(key);
				if (t->isEmpty()) {
					prev->setNext(tmp->getNext());	
				}
				else {
					tmp->setPtrKey(t);
				}
				
				tmp = tmp->getNext();
			}
		}
};


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while(!input.eof()) {
		string type;
		input >> type;
		int n;
		input >> n;
		
		if (type == "int") {
			List<int> *l = new List<int>(n);
			string query; 
		
			do {
				input >> query; 
				int val;
				if (query == "ins") {
					input >> val; 
					l->ins(val);
				}
				if (query == "canc") {
					input >> val; 
					l->canc(val);
				}
			} while  (query != "#");
			l->print(output);
			output << endl;
		}
		if (type == "double") {
			List<double> *l = new List<double>(n);
			string query; 
		
			do {
				input >> query; 
				double val;
				if (query == "ins") {
					input >> val; 
					l->ins(val);
				}
				if (query == "canc") {
					input >> val; 
					l->canc(val);
				}
			} while  (query != "#");
			l->print(output);
			output << endl;
		}
	}
}

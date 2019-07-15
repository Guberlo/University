#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


template <class H> class Nodo {
	H *key;
	Nodo<H> *p, *left,*right; 
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			p = left = right = NULL;
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
	int n,k; 
	
	Nodo<H> *_search(Nodo<H> *x, H key) {
		if (x) {
			if (x->getKey() == key) return x;
			if (x->getKey() < key) return _search(x->getRight(), key);
			else return _search(x->getLeft(), key);
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
		
	}
	
	void preorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			cout << x->getKey() << " ";
			preorder(x->getLeft(),out);
			preorder(x->getRight(),out);
		}
	}
	
	public:
		BST(int k) {
			root = NULL; 
			this->k = k; 
			n=0;
		}
		
		bool ins(H key) {
			if (n>=k) return false;
			
			Nodo<H> *nodo = new Nodo<H>(key);
			n++;
			
			if (!root) {
				root = nodo;
				return true;
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
			return true;
		}
		
		BST<H> *canc(H key) {
			_canc(root,key);
			n--; 
		}
		
		bool isEmpty() {
			return root == NULL; 
		}
		
		void print(ofstream &out) {
			preorder(root,out);
		}
		
};


template <class H> class NodoL {
	H *key;
	NodoL<H> *next;
	
	public:
		NodoL(H key) {
			next = NULL;
			this->key = new H(key);
		}
		
		void setNext(NodoL<H> *next) {
			this->next = next;
		}
		NodoL<H> *getNext() {
			return next;
		}
		void setPtrKey(H *key) {
			this->key = key;
		}
		H *getPtrKey() {
			return key;
		}
};

template <class H> class List {
	
	NodoL< BST<H> > *header;
	int n;
	public: 
		List(int n) {
			header = NULL; 
			this->n = n; 
		}
		
		List< BST<H> > *ins(H key) {
			if (!header) {
				BST<H> a;
				a.ins(key);
				header = new NodoL<BST<H> >(a);
			}	 
		}
		
		
		
		void print() {
			NodoL<H> *tmp = header;
			
			while (tmp) {
				cout << *(tmp->getPtrKey()) << " ";
				tmp = tmp->getNext();
			}
		}
		
		
}; 


int main() {
	BST<int> *t  = new BST<int>(4);
	ofstream output("output.txt");
	t->ins(12); t->ins(1); t->ins(8); t->ins(2); t->ins(99);
	t->print(output);
	cout << endl;
	cout << t->isEmpty();
	t->canc(1)->canc(8)->canc(12)->canc(2);
	t->print(output);
	t->ins(12);
	t->canc(12);
	cout << t->isEmpty();
}

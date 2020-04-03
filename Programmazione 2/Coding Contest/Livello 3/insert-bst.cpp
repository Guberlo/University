#include <iostream>
#include <sstream>
#include <fstream>


using namespace std;

template <class H> class Nodo {	
	H *key;
	Nodo<H> *left,*right,*p;
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			left = right = p = NULL;
		}
		Nodo(H *key) {
			this->key = key;
			left = right = p = NULL;
		}
		
		void setP(Nodo<H> *p) {
			this->p = p;
		}
		void setLeft(Nodo<H> *left) {
			this->left = left;
		}
		void setRight(Nodo<H> *right) {
			this->right = right;
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
	
	void _inorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			_inorder(x->getLeft(),out);
			out << x->getKey() << " ";
			_inorder(x->getRight(),out);
		}
	}
	
	void _postorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			_postorder(x->getLeft(),out);
			_postorder(x->getRight(),out);
			out << x->getKey() << " ";
		}
	}
	
	void _preorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			out << x->getKey() << " ";
			_preorder(x->getLeft(),out);
			_preorder(x->getRight(), out);
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
		
		void print(string query, ofstream &out) {
			if (query == "preorder") 
				_preorder(root,out);
			
			else if (query == "postorder") 
				_postorder(root, out);
			
			else 
				_inorder(root,out);
			
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
		string query;
		input >> query;
		
		if (type == "int" || type == "bool") {
			BST<int> *t = new BST<int>();
			int x;
			
			for (int i=0; i<n; i++) {
				input >> x;
				t->ins(x);
			}
			t->print(query,output);
		}
		
		if (type == "double") {
			BST<double> *t = new BST<double>();
			double x;
			
			for (int i=0; i<n; i++) {
				input >> x;
				t->ins(x);
			}
			t->print(query,output);
		}
		if (type == "char") {
			BST<char> *t = new BST<char>();
			char x;
			
			for (int i=0; i<n; i++) {
				input >> x;
				t->ins(x);
			}
			t->print(query,output);
		}
	}
}

#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Nodo {
	H *key;
	Nodo<H> *right, *left, *p;
	
	public:
		Nodo(H key) {
			this->key = new H(key);
			right = left = p = NULL;
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
		
};

template <class H> class BST {
	
	Nodo<H> *root;
	H *array; 
	int n; 
	int index; 
	
	void naturalFill(Nodo<H> *x) {
		if (x) {
			
			naturalFill(x->getLeft());
			x->setKey(array[index]);
			index++;
			naturalFill(x->getRight());
			
		}
	}
	
	
	
	Nodo<H> *min(Nodo<H> *x) {
		while (x->getLeft())
			x = x->getLeft();
		return x;
	}
	
	Nodo<H> *_succ(Nodo<H> *x) {
		if (x->getRight()) return min(x->getRight()); 
		Nodo<H> *p = x->getP();
		
		while (p && p->getKey() < x->getKey()) {
			p = p->getP();
		}
		return p; 
	}/*
	Nodo<H>* _successore(Nodo<H>* tmp) {
			if(tmp->getRight()) 
				return min(tmp->getRight());
			Nodo<H> *p = tmp->getP();
			while(p!=NULL && p->getKey()<tmp->getKey())
				p = p->getP();
			return p;
		}
	*/
	void postorder(Nodo<H> *x, ofstream &out) {
		if (x) {
			postorder(x->getLeft(),out);
			postorder(x->getRight(),out);
			out << x->getKey() << " ";
		}
	}
	
	public:
		BST(int n) {
			root = NULL;
			this->n = n; 
			index = 0; 
			array = NULL; 
		}
		
		void setArray(H *arr) {
			this->array = arr;
			
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
		void print(ofstream &output) {
			//naturalFill(root);
			postorder(root,output);
			output << endl;
		}
		
		void natural_fill(H *arr) {
			Nodo<H> *x = min(root);
			int i = 0; 
			cout << x->getKey() << " ";
			while (x) {
				x->setKey(arr[i]);
				x = _succ(x);
				i++;
			}
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
			BST<int> *t = new BST<int>(n);
			int *arr = new int[n];
			int x;
			for (int i=0; i<n; i++) {
				input >> x;
				t->ins(x);
			}
			for (int i=0; i<n; i++) {
				input >> arr[i];
			}	
			t->natural_fill(arr);
			t->print(output);
		}
		if (type == "double") {
			BST<double> *t = new BST<double>(n);
			double *arr = new double[n];
			double x;
			for (int i=0; i<n; i++) {
				input >> x;
				t->ins(x);
			}
			for (int i=0; i<n; i++) {
				input >> arr[i];
			}	
			t->natural_fill(arr);
			t->print(output);
		}
	}
}


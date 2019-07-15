#include <iostream>
#include <fstream>


using namespace std;


template <class H> class Nodo {
	
	Nodo<H> *prev, *next;
	
	H *key;
	
	public:
		Nodo(H key) {
			this->key = new H(key);  
			prev = next = NULL;
		}
		Nodo(H *key) {
			this->key = key; 
			prev = next = NULL;
		}
		// void 
		void setPrev(Nodo<H> *prev) {
			this->prev = prev;
		}
		void setNext(Nodo<H> *next) {
			this->next = next;
		}
		void setKey(H key) {
			this->key = new H(key);
		}
		
		
		// getter 
		Nodo<H> *getPrev() {
			return prev;
		}
		Nodo<H> *getNext() {
			return next;
		}
		H *getPtrKey() {
			return key;
		}
};


template <class H> class List {
	
	Nodo<H> *header, *current;
	int count;
	int n; 
	
	public:
		
		List(int n) {
			H *tmp = NULL; 
			header = new Nodo<H>(tmp);
			current = header;
			this->n = n; 
			this->count=0; 
		}
		
		List<H> *ins(H key) {
			Nodo<H> *nodo = new Nodo<H>(key);
			count++;
			
			Nodo<H> *tmp = header->getNext();
			Nodo<H> *prev = header;
			
			while (tmp) {
				prev = tmp;
				tmp = tmp->getNext();
			}		
			prev->setNext(nodo);
			nodo->setPrev(prev);
			return this;
		}
		List<H> *ins(H *key) {
			Nodo<H> *nodo = new Nodo<H>(key);
			
			
			Nodo<H> *tmp = header->getNext();
			Nodo<H> *prev = header;
			
			while (tmp) {
				prev = tmp;
				tmp = tmp->getNext();
			}		
			prev->setNext(nodo);
			nodo->setPrev(prev);
			return this;
		}
		
		H *get(int n) {
			int i=0;
			Nodo<H> *tmp = header->getNext();
			while (tmp) {

				if (i==n) return tmp->getPtrKey();
				tmp = tmp->getNext();
				i++;		
			} 
			return NULL;
		}
		
		
		void print() {
			Nodo<H> *tmp = header->getNext();
			while (tmp) {
				cout << *(tmp->getPtrKey()) << " ";
				tmp = tmp->getNext();
			}
		}
		
		// Iterator
		void reset() {
			current = header; 
		}
		H *next() {
			current = current->getNext();
			return current->getPtrKey();
		}
		bool has_next() {
			return current->getNext() != NULL;
		}
		
		int size() {
			return count;
		}
		
		

};


template <class H> class LMatrix {
	
	int n, m; 
	List< List<H> > *mat;
	
	
	public: 
		LMatrix(int n, int m) {
			this->n = n; 
			this->m = m; 
			mat = new List< List<H> >(n);
		}
		
		LMatrix(List<List<int> > *mat,int n, int m) {
			this->n = n; 
			this->m = m; 
			this->mat = mat;
		}
		
		LMatrix<H> *insRiga(List<H> *riga) {
			mat->ins(riga);
			return this;
		}
		
		void print(ofstream &out) {
			
			while (mat->has_next()) {
				List<H> *rigaX = mat->next(); 
				while (rigaX->has_next()) {
					H *x = rigaX->next();
					out << *x << " ";
				} 
			}
			out << endl; 
		}
		
		friend LMatrix<H>* operator*(const LMatrix<H> m1, const LMatrix<H> m2) {
			LMatrix<H> A = m1;
			LMatrix<H> B = m2;
			
			
			
			
			List<H> *rigaA;
			List<H> *rigaB;
			
			
			int n = A.n;
			int m = A.m;
			int p = B.m;
			
			LMatrix<H> *C = new LMatrix<H>(n,p);
			
			int *x;
			int *y;
			
			
			for (int i=0; i<n; i++) {
				List<H> *newList = new List<H>(p);
				
				for (int j=0; j<p; j++) {
					H c = 0; 
					for (int k=0; k<m; k++) {
						
						rigaA = A.mat->get(i);
						H *x = rigaA->get(k);
						rigaB = B.mat->get(k);
						H *y = rigaB->get(j);
						c += *(x) * *(y);
						
						
					}
					newList->ins(c);
			
				}
				C->mat->ins(newList);
			
			}
			
			return C;
		}
	
	

};



int main() {
	/*
	List< List<int> > *mat = new List< List<int> >(3);
	// 3 righe.
	
	
	List<int> *riga1 = new List<int>(2);
	List<int> *riga2 = new List<int>(2);
	List<int> *riga3 = new List<int>(2);
	
	riga1->ins(1)->ins(2);
	riga2->ins(3)->ins(4);
	riga3->ins(5)->ins(6);
	
	mat->ins(riga1)->ins(riga2)->ins(riga3);
	
	
	List<int> *riga4 = new List<int>(2);
	List<int> *riga5 = new List<int>(2);
	List<int> *riga6 = new List<int>(2);
	
	List< List<int> > *mat2 = new List< List<int> >(2);
	
	riga4->ins(5)->ins(7)->ins(12);
	riga5->ins(3)->ins(4)->ins(14);
	
	
	mat2->ins(riga4)->ins(riga5);
	
	
	while (mat->has_next()) {
		List<int> *rigaX = mat->next();
		List<int> *rigaY;
		if (mat2->has_next()) rigaY = mat2->next();
		while (rigaX->has_next()) {
			int *x = rigaX->next();
			
			cout << *x << " ";	
		}
		cout << endl; 
	}
	
	
	*/
	/*
	
	List<  List<int> > *A = new List < List<int> >(4);
	
	List<int> *riga1 = new List<int>(2); 
	List<int> *riga2 = new List<int>(2);
	List<int> *riga3 = new List<int>(2);
	List<int> *riga4 = new List<int>(2);
	
	riga1->ins(8)->ins(0);
	riga2->ins(2)->ins(4);
	riga3->ins(8)->ins(3);
	riga4->ins(9)->ins(0);
	A->ins(riga1)->ins(riga2)->ins(riga3)->ins(riga4);
	
	
	
	List<  List<int> > *B = new List < List<int> >(2);
	
	List<int> *riga5 = new List<int>(2); 
	List<int> *riga6 = new List<int>(2);
	
	riga5->ins(5)->ins(2);
	riga6->ins(2)->ins(7);

	B->ins(riga5)->ins(riga6);
	
	LMatrix<int> lm1(A,4,2);
	LMatrix<int> lm2(B,2,2);
	
	LMatrix<int> *lm3 = lm1*lm2;
	
	lm3->print();
	*/
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		
		int n,m,p;
		
		input >> n;
		input >> m;
		input >> p; 
		cout << n << " " << m << " " << p << endl;
		LMatrix<int> *a = new LMatrix<int>(n,m);
		// A di dimensioni nxm
		for (int i=0; i<n; i++) {
			List<int> *riga = new List<int>(m); 
			for (int j=0; j<m; j++) {
				int x; input >> x;
				riga->ins(x);
			}
			a->insRiga(riga);
		}
		
		LMatrix<int> *b = new LMatrix<int>(m,p);
		for (int i=0; i<m; i++) {
			List<int> *riga = new List<int>(p); 
			for (int j=0; j<p; j++) {
				int x; input >> x;
				riga->ins(x);
			}
			b->insRiga(riga);
		}
		LMatrix<int> x = *a;
		LMatrix<int> y = *b; 
		LMatrix<int> *c = x*y;
		c->print(output);
		 
		
	}
	
	
	
}


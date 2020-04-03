#include <iostream>
#include <sstream>
#include <fstream>


#define BIANCO 0
#define GRIGIO 1
#define NERO 2

using namespace std;

template <class H> class Vector {
	H *nodes;
	int index, n;

	public:
		Vector(int n) {
			this->n = n; 
			nodes = new H[n];
			index = 0; 
		}
		
		int size() {
			return n; 
		}
		
		int findIndex(H key) {
			for (int i=0; i<n; i++)
				if (nodes[i] == key) return i; 
			return -1;
 		}
 		H findKey(int i) {
 			return nodes[i];
		}
		
		int addNode(H key) {
			if (index > n) return 0;
			nodes[index] = key;
			index++;
			//_sort(*nodes,*nodes+index);
			return 1; 
		}	 
};

template <class H> class Graph {
	
	Vector<H> *nodes; 
	int **mat;
	int n; 
	int *d, *f, *color;
	int time;
	
	void _sort(int *s, int *f, int n) {
		for (int i=0; i<n-1; i++) {
			for (int j=i+1; j<n; j++) {
				int min; 
				if (f[s[i]] > f[s[j]]) {
					int tmp = s[i];
					s[i] = s[j];
					s[j] = tmp;
				} 
			}
		}
	}
	void sort(int *f, int *s, int n) {
			for(int i=1; i<n; i++) {
				int j = i-1;
				while(j>=0 && f[s[j]]<f[s[j+1]]) {
					int t = s[j];
					s[j] = s[j+1];
					s[j+1] = t;
					j--;
				}
			}
		}
	
	public:
		Graph(int n) {
			nodes = new Vector<H>(n);
			this->n = n;
			mat = new int*[n];
			for (int i=0; i<n; i++) {
				mat[i] = new int[n];
			}
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++) 
				mat[i][j] = 0;
			}
			d = new int[n];
			for (int i=0; i<n; i++) d[i] = 200;
			f = new int[n];
			for (int i=0; i<n; i++) f[i] = 200;
			color = new int[n];
		}	
		
		Graph<H> *insertEdge(H x, H y) {
			int i = nodes->findIndex(x);
			int j = nodes->findIndex(y);
			
			mat[i][j] = 1;
			return this;
		}
		
		Graph<H> *insertNode(H x) {
			nodes->addNode(x);
			return this;
		}
		
		void print() {
			
			for (int i=0; i<n; i++) {
				cout << "(";
				H prova = nodes->findKey(i);
				cout << prova;
				for (int j=0; j<n; j++) {
					if (mat[i][j]==1) cout << " " << nodes->findKey(j);
				}
				cout << ") ";
			}
		}
		
		void  DFS() {
			time = 0;
			for (int i=0; i<n; i++) {
				color[i] = BIANCO;
			}	
			for (int i=0; i<n; i++) {
				if(color[i] == BIANCO) 
					DFSVisit(i);
			}
		}
		
		void DFSVisit(int i) {
			color[i] = GRIGIO; 
			d[i] = time++;
			for (int j=0; j<n; j++) {
				if (mat[i][j]) {
					if (!color[j]) DFSVisit(j);
				}
			}
			f[i] = time++;
			color[i] = NERO; 
			
		}
		
		void topologicalsort(ofstream &out) {
			//Visto che i grafi sono sempre DAG (grafo aciclico diretto), non serve fare controlli.
			DFS();
			int *s = new int[n];
			for (int i=0; i<n; i++) s[i] = i;
			sort(f,s,n); 
			for(int i=0; i<n; i++) {
				out << nodes->findKey(s[i]) << " ";
			}
			out << endl;
		}
	
		
};

/*
int main() {
	Graph<char> *g = new Graph<char>(6);
	// 25 38 49 71 74
	g->insertNode('E')->insertNode('F')->insertNode('Q')->insertNode('R')->insertNode('U')->insertNode('W');
	//E F Q R U W (E,U) (F,E) (F,Q) (F,R) (F,U) (R,U) (W,E) (W,F) (W,Q) (W,U)
	g->insertEdge('E','U')->insertEdge('F','E')->insertEdge('F','Q')->insertEdge('F','R')->insertEdge('R','U')->insertEdge('W','E')->insertEdge('W','F')->insertEdge('W','Q')->insertEdge('W','U');
//	g->print();
	//g->DFS();
	g->topologicalsort();
}*/


int main() {
	
	ifstream input("input.txt");
	ofstream output("output.txt");
	
	while (!input.eof()) {
		
		int n; input >> n; // number of nodes
		int m; input >> m; // number of edge
		
		
		string type; input >> type; 
		if (type == "int") {
			Graph<int> *g = new Graph<int>(n);
			int node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->insertNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				g->insertEdge(x,y);
				
			}
			g->topologicalsort(output);
		}
		if (type == "char") {
			Graph<char> *g = new Graph<char>(n);
			char node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->insertNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				
				g->insertEdge(x,y);
				
			}
			g->topologicalsort(output);

		}
		if (type == "double") {
			Graph<double> *g = new Graph<double>(n);
			double node, x, y;
			for (int i=0; i<n; i++) {
				input >> node;
				g->insertNode(node);
			}
			
			for (int i=0; i<m; i++) {
				string _x; input >> _x;
				string _y; input >> _y;
				//replace '(' and ')'
				stringstream buffer1(_x.substr(1));
				stringstream buffer2(_y.substr(0,_y.size()-1));
				buffer1 >> x;
				buffer2 >> y;
				g->insertEdge(x,y);
				
			}
			g->topologicalsort(output);
		}

	}
}

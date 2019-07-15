#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#define BIANCO 0
#define GRIGIO 1
#define NERO 2
#define INF 101; 
using namespace std;


template <class H> class Vector {
	
	H *nodes; 
	int n; 
	int length; 
	
     public:
		Vector(int length) {
			this->length = length;
			nodes = new H[length];
			n = 0;
		}
		
		void addNode(H node) {
			nodes[n] = node;
			n++;
			//sort(nodes,nodes+n);
		}
		
		
		H findKey(int i) {
			return nodes[i];
		}
		int findIndex(H node) {
			for (int i=0; i<n; i++) 
				if (nodes[i] == node) 
					return i; 
					
			return -1;
		}
	
};

template <class H> class Graph {
	Vector<H> *nodes;
	int n; // number of nodes 
	int **mat;
	
	int *color, *p, *d, *f, *r;
	int time;
	
	public:
		Graph(int n) {
			nodes = new Vector<H>(n);
			mat = new int*[n]; 
			for (int i=0; i<n; i++) {
				mat[i] = new int[n];
			}
			
			// Initialize b-array to 0
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++) {
					mat[i][j] = 0; 
				}
			}
			this->n = n; 
			
			color = new int[n];
			d = new int[n];
			for(int i=0; i<n; i++) d[i]=INF;
			f = new int[n];
			for(int i=0; i<n; i++) f[i]=INF;
			p = new int[n];
			r = new int[n];
			time = 0;
		     
		}
		
		Graph<H> *addNode(H key) {
			nodes->addNode(key);
			return this;
		}
		Graph<H> *addEdge(H x, H y) { // connect node x to node y
		
			int i = nodes->findIndex(x);
			int j = nodes->findIndex(y);
			
			mat[i][j] = 1; 
			return this;
		}
		
		void print(ofstream &out) {
			
			for (int i=0; i<n; i++) {
				out << "("; 
				H key = nodes->findKey(i);
				out << key;
				for (int j=0; j<n; j++) {
					if (mat[i][j] == 1) {
						H y = nodes->findKey(j);
						out << " " << y;
					}
				}
				out << ") ";
			}
		}
		
		void printMat() {
			for (int i=0; i<n; i++) {
				for (int j=0; j<n; j++) {
					cout << mat[i][j] << " ";
				}
				cout << "\n";
			}
		}
		
		void DFSVisit(int i) {
			color[i] = GRIGIO;
			d[i] = time++;
			for (int j=0; j<n; j++) {
				if (mat[i][j]) {
					if(!color[j]) 
						DFSVisit(j);
				}
			}
			f[i] = time++; 
			color[i] = NERO; 
 		}
 		
 		void DFS(ofstream &output) {
			time = 0;
			for(int i=0; i<n; i++){
				color[i] = BIANCO;
			}
			for(int i=0; i<n; i++)
				if(color[i]==BIANCO) 			
					DFSVisit(i);	
			
			for (int i=0; i<n; i++) {
				output << "(" << nodes->findKey(i) << " " << d[i] << " " << f[i] << ") ";
			}

		}
 		
	
	
};


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
			g->DFS(output);
			output << endl;
		}
		if (type == "char") {
			Graph<char> *g = new Graph<char>(n);
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
			g->DFS(output);
			output << endl;
		}
		if (type == "double") {
			Graph<double> *g = new Graph<double>(n);
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
			g->DFS(output);
			output << endl;
		}

	}
}

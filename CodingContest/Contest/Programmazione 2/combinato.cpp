#include <iostream>
#include <fstream>

using namespace std;

class Combinato {
	int *K; 
	int *N;
	
	int n; 
	int current;
	public:
		Combinato(int n) {
			K = new int[n];
			N = new int[n];
			this->n = n; 
			this->current = 0; 
		}
		
		
		void addElement(int x) {
			if (current == 0) {
				K[current] = x;
				N[current] = -1;
				current++; 
				return; 
			}
			for (int i=current-1; i>=0; i--) {
				if (K[i] >= x) {
					K[current] = x;
					N[current] = i; 
				}
				else 
			}
			 
			
			
		}
};

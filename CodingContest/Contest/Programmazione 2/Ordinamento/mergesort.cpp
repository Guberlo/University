#include <iostream>

using namespace std;


template <class T>
void merge(T v[], int low, int mid, int high) {
	T b[1001];
	int h = low;
	int i = low;	
	int j = mid+1;

	while( (h<=mid) && (j<=high) ) {
		if( v[h] <= v[j] ) b[i] = v[h++];
		else b[i] = v[j++];
		
		
  		i++;
	}
 	if(h>mid)
  		for(int k=j; k<=high; k++) b[i++]=v[k];
 	else
		for(int k=h; k<=mid; k++) b[i++]=v[k];
		
 	for(int k=low; k<=high; k++) v[k]=b[k];	
}
template <class T>
void mergesort(T v[], int low, int high) {
	if( low<high) {
	
		int mid = (low+high)/2; 
		mergesort( v, low, mid);	
		mergesort( v, mid+1, high );	
		merge( v, low, mid, high);
		
 	}
 	
}




int main() {
	int v[9] = {73 ,658, 930, 272, 544, 878, 923, 709,440};
	mergesort(v,0,8);
	for (int i=0; i<9; i++) {
		cout << v[i] << " ";
	}
}

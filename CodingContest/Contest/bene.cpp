#include <iostream>
#include <fstream>

using namespace std;

void swap(double *a, double *b) {
    double aux = *a;
    *a = *b;
    *b = aux;
}
 
void selection(double A[], int size) {
    int min;

    for (int i = 0; i < size-1; i++) {

        min = i;
        for (int j = i+1; j < size; j++)
          if (A[j] < A[min])
            min = j;

        swap(&A[min], &A[i]);
    }
}
void print(double A[], int size) {
	for (int i=0; i<size; i++) {
		cout << A[i]  << " ";
	}
	cout << endl;
}

void carry_boxes(double A[], int size, double max_weight, int& n_boxes, double& weight) {
	selection(A,size);
	print(A,size);
	int i=0;
	double tmp=0;
	while(tmp<=max_weight && i<size) {
		tmp += A[i];
		if (tmp<=max_weight) {
			weight = tmp;
			n_boxes++;
		}
		i++;

	}

}

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	while (!input.eof()) {
		double max_weight = 0;
		input >> max_weight; // massimo peso trasportabile

		int size;
		input >> size;

		double boxes[size];
		for (int i=0; i<size; i++) {
			input >> boxes[i];
		}
		print(boxes,size);
    int n_boxes = 0;
    double weight=0;

		carry_boxes(boxes,size,max_weight,n_boxes,weight);

		output << n_boxes << " " << max_weight << endl;
	}

	input.close();
	output.close();

  return 0;
}

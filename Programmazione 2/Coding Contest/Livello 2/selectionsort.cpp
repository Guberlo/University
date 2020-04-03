#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int selectionsort(int* vett, int n){
    int min;
    int sum = 0;
    for(int i = 0; i < n; i++){
        min = i;
        for(int j = i+1; j < n; j++)
            if(vett[j] < vett[min])
                min = j;
        sum += min -i;
        swap(vett[i], vett[min]);
        
    }

    return sum;
}


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n;
        in >> n;
        int* vett = new int[n];
        for(int j = 0; j < n; j++)
            in >> vett[j];
        out << selectionsort(vett, n) << endl;
        
        delete [] vett;
    }



    return 0;
}

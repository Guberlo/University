#include <iostream>
#include <fstream>

using namespace std;

int Fibonacci(int n){
    if(n==1 || n==2) return 1;
    else return Fibonacci(n-1)+Fibonacci(n-2);
}

int main()
{
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");

    int n;

    if(input.is_open() && output.is_open()){
        while(input >> n)
            output << Fibonacci(n) << endl;
    }
    else
        cout << "Error opening file!"<< endl;

    input.close();
    output.close();

    return 0;
}

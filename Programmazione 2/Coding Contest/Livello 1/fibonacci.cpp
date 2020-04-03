#include <iostream>
#include <fstream>

using namespace std;
typedef uint64_t u64_t;

u64_t fibonacci(unsigned int n)
{
    //n_minus_1 represents what's supposed to be F(n-1)
    //n_minus_2 represents what's supposed to be F(n-2)
    //sum represents F(n) which equals F(n-1)+F(n-2)
    double n_minus_1=0,n_minus_2=1,sum;

switch(n)
    {
    //if n=0 then F(n)=0
    case 0:
        return 0;

    //if n=1 then F(n)=1
    case 1:
        return 1;

    //otherwise the sum (i.e F(n)) is equal to (n_minus_1)+(n_minus_2) (i.e F(n-1)+F(n-2)
    //the counter keeps on moving the variables areound 'n' times
    //so that on each time F(n-2) becomes equal to F(n-1) and F(n-1) becomes equal to F(n)
    //and F(n) is reevaluated each time in the loop
    default:
        for(int counter=0;counter<n;counter++)
        {
            sum=n_minus_1+n_minus_2;
            n_minus_2=n_minus_1;
            n_minus_1=sum ;
        }
    }
    return sum;
}

int main(){
    ifstream input("input.txt");
	ofstream output("output.txt");

	while (!input.eof()) {

		int n; input >> n;
		cout << n << endl;
		output << fibonacci(n) << endl;
	}
}

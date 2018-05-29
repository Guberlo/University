#include <iostream>
#include <fstream>

using namespace std;

int fibonacci(int n)
{
        if(n==1 || n==0)
                return 1;
        else
                return fibonacci(n-2)+fibonacci(n-1);
}
int main()
{
        ifstream input;
        ofstream output;
        input.open("input.txt");
        output.open("output.txt");


        if(input.is_open())
        {
                while(!input.eof())
                {
                        int n;
                        input >> n;

                        int k=fibonacci(n);
                        cout << " k= " << k << "... \n";
                        output << k << endl;
                }
        }

        input.close();
        output.close();

        return 0;
}

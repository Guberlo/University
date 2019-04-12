#include <iostream>
#include <fstream>

using namespace std;

int fibonacci(int n, int i)
{
  if(n <= 0) return 0;
  else if(n == 1) return 1;
  else return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
  ifstream input("input.txt");
  ofstream output("output.txt");

  while(!input.eof())
  {
    int n = 0;
    input >> n;


  }
}

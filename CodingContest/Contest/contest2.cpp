#include <iostream>
#include <fstream>

using namespace std;

float sum(float* a, int n)
{
  float somma;
  for(int i=0; i<n; i++)
    somma+=a[i];
  return somma;
}

int main()
{
  ifstream input("input.txt");
  ofstream output("output.txt");

  while(!input.eof())
  {
    int n = 0;
    input >> n;

    float a[n];
    for(int i=0; i<n; i++)
      input >> a[i];
    output << sum(a, n) << endl;
  }
  input.close();
  output.close();

  return 0;
}

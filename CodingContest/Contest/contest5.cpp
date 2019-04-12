#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream input("input.txt");
  ofstream output("output.txt");

  while(!input.eof())
  {
    int n = 0;
    input >> n;

    double a[n];
    for(int i=0; i<n; i++)
    {
      input >> a[i];
      output << a[i] - (int) a[i] << " ";
    }
    output << endl;
  }

  input.close();
  output.close();
  return 0;
}

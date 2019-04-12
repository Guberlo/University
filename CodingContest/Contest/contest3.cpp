#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream input("input.txt");
  ofstream output("output.txt");

  while(!input.eof())
  {
    int count = 0;
    int n = 0;
    input >> n;

    int a[n];
    for(int i=0; i<n; i++)
    {
      input >> a[i];
      if(a[i]%2 != 0) count++;
    }

    int j = 0;
    int b[count];
    for(int i=0; i<n; i++)
    {
      if(a[i]%2 != 0) b[j++] = a[i];
    }

    for(int i=0; i<count; i++)
      output << b[i] << " ";
    output << endl;
  }

  input.close();
  output.close();
  return 0;
}

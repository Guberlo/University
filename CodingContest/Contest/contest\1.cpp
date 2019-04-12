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
    input >> n;//numero di elementi

    int X = 0; //elemento da confrontare
    input >> X;

    int a[n];
    for(int i=0; i<n; i++)
    {
      input >> a[i];
      if(a[i] > X) count++;
    }

    int b[count];
    int j=0;
    for(int i=0;i<n; i++)
    {
      if(a[i] > X)
      {
        b[j++] = a[i];
      }
    }

    output << count << " ";
    for(int i=0; i<count; i++)
      output << b[i] << " ";
    output << endl;
  }



  input.close();
  output.close();
  return 0;
}

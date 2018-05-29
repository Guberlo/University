#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void eliZero(string a[], int n)
{
  for(int i=0;i<n;i++)
  {
    if(a[i][0]=='0')
    {
      int l=a[i].length();
      int j,count=0;
      while(a[i][j]!=0)
        count++;  j++;
      a[i]=a[i].substr(count-1, l-count-1);
    }
  }
}

string maximum(string a[], int n)
{
    int max=a[0];
    for(int i=0;i<n-1;i++)
    {
      int l1=a[i].length();
      int l2=a[i+1].length();
      if(l1>l2) max=a[i];
      else if(l1<l2) max=a[i+1];
      else
      {
        if(a[i][0]>a[i+1][0]) max=a[i];
        else if(a[i][0]<a[i+1][0]) max=a[i+1];
        else
        {
          for(int j,k=1;j<l1 &6 k<l2; j++,k++){
            if(a[i][j]>a[i][k])
          }
        }
      }
    }
}

void print(string a[], int n)
{
  for(int i=0;i<n;i++)
    cout << a[i] << " ";
  cout << endl;
}

int main()
{
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");


  while(!input.eof())
  {
      int n;
      input >> n;

      string diametro[n];
      for(int i=0;i<n;i++)
      {
        input >> diametro[i];
      }

      eliZero(diametro, n);


 }
  input.close();
  output.close();
*/
  return 0;
}

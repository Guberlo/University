#include <iostream>
#include <string>

using namespace std;

string togli(string s)
{
    string g="";
    int l=s.length();
    for(int i=0;i<l;i=i+6)
    {
      g+=s.substr(i,3);
    }
    return g;
}

int main()
{
  string b="abcdefghilmno";
  string z=togli(b);
  cout << z << endl;
  return 0;
}

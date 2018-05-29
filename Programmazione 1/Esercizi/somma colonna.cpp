#include <iostream>

using namespace std;

const int col=3;
const int rig=3;

bool somma(int A[][col], int rig)
{
  int s1,s2;
  for(int k=0;k<col;k++)
  {
    for (int j=k+1; j<col; j++)
       {
        for (int i=0, s1=0, s2=0; i<rig; i++)
         {
             s1 += A[i][k];
             s2 += A[i][j];
         }
         cout << s1 << " " << s2 <<" \n";
          if (s1 == s2){
                  cout <<" Esistono due colonne le cui somme sono uguali"<<endl;
                  cout << " che sono " << k << " e " << j << endl << endl;
                  cout << " poiche' le loro somme sono rispettivamente ";
                  cout << s1 << " e " << s2 << endl << endl;
                  j = col;
                  k = col;
              }
        }
      }

  //return false;
}


int main()
{
  int a[rig][col]={{1,1,1},
                   {1,1,1},
                   {1,1,1}};
  somma(a, rig);
  return 0;
}

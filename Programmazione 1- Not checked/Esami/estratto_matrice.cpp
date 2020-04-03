#include <iostream>

using namespace std;

float Media(int A[][COL], int RIG, int x, int y)
{
  return (A[x][y]+A[x][y+1]+A[x+1][y]+A[x+1][y+1])/4.0;
}

bool Estratto(int A[][COL], int RIG)
{
  for(int i=0; i<RIG; i++)
  {
    for(int j=0; j<COL; j++)
    {
      float mediaTemp = Media(A, i, j);
      for(int x=i; x< RIG; x++)
      {
        for(int y=j+1; y<COL; y++)
        {
          
        }
      }
    }
  }
}

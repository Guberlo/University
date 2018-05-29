#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand(time(0));
   int a[40]={1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
   int b[40];
   int j=0;
   int temp;

   for(int i=0;i<40;i++){
    j=rand()%40+1;
    b[j]=a[i];
    cout << b[j]<<", ";

   }




    return 0;
}

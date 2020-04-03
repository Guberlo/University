#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand(time(0));
    int x=rand()%2+1;

    if(x==1) cout << "Campisano è gay!!";
    else cout << "Dario è gay!!";
    return 0;
}

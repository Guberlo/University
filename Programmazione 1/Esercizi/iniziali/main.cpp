#include <iostream>
#include <string>

using namespace std;

int main()
{
    string primo;
    string secondo;

    cout << "Inserisci il primo nome: ";
    cin >> primo;
    cout << "Inserisci il secondo nome: ";
    cin >> secondo;
    cout << primo.substr(0,1)<< "&"<< secondo.substr(0,1);
    return 0;
}

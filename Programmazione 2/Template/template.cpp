#include <iostream>

using namespace std;

template <class T> void scambia(T& a, T&b)
{
		T aux=a;
		a=b;
		b=aux;
}

template <class T> int ricerca(T dato, T a[], int dimensione)
{
		int flag=-1, i=0;
		while(flag==-1 && i< dimensione)
		{
				if(dato==a[i])
					flag=i;
				i++;
		}
		return flag;
}

int main()
{
		/*int a=6, b=16;
		float c=3.7, d=4.8;
		char e='a', f='b';

		cout << "Valori originali " << a << " " << b << endl;
		scambia(a,b);
		cout << "Valori scambiati " << a << " " << b << endl;
*/

int d, v[12]={2,34,5,6,7,32,11,12,34,32,2,12};

cout << "Inserire un intero: "; cin >> d;
int ris=ricerca(d,v,12);
if(ris==-1) cout << "Elemento non trovato\n";
else cout << "Elemento trovato in posizione: " << ris << endl;
	return 0;
}

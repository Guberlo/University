#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void fillZstring(string z[], int size, string y) //works!!
{
        int l=y.length();
        int i,j=0;

        while(j<size && i<l)
        {
                if(y[i]!='_')
                        z[j]+=y[i];
                if(y[i]=='_')
                        j++;
                i++;
        }
}

int get_underscore(string y) //works!
{
        int c=0;
        int l=y.length();
        for(int i=0; i<l; i++)
                if(y[i]=='_')
                        c++;
        return c;
}

void anagram(string x, string y[], int size,int len)
{
        int n1=x.length();
        int k=0;
        for(int j=0; j<size; j++)
        {
                int c=0;
                for(int i=0; i<n1; i++)
                {
                        int l=y[j].length();
                        for(k=0; k<l; k++)
                        {
                                if(x[i]==y[j][k])
                                        c++;
                        }
                        if(c==n1) cout << "Giusto! " << j << y[j].length()-k+1 << endl;
                }
        }
}

int anagram(string x, string y)
{
        int n1=x.length();
        int n2=y.length();
        int c=0;

        while(j<n2 && i<n1)
        {
                if(x[i]==y[j])
                        c++; i++;
                if(y[j]=='_')
                        c=0; i=0;
                j++;
                if(c==n1) cout << "Trovato!" << j << endl;
        }

}

int main()
{
        ifstream input;
        ofstream output;
        input.open("input.txt");
        output.open("output.txt");

        string x="questore";
        string z="il_uqetsore_di_Montelusa_riceve_la_lettera_del_vicequsetoer_e_avvisa_il_vicequestore_stesso_della_presenza_di_alcuni_criminali_operanti_nel_comune";
        int len1=z.length();
        string y[3]={"quetsore","vicequestore","quetsore"};
        anagram(x,z);


        if(input.is_open())
        {
                while(!input.eof())
                {
                        string x;
                        input >> x; //takes the word to search for
                        string y;
                        input >> y; //takes the string to look for
                        int len=y.length();
                        int m=get_underscore(y);
                        string z[m+1];
                        fillZstring(z,m+1,y);
                }
        }
        return 0;
}

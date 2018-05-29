#include <iostream>
#include <fstream>

using namespace std;

int search_volume(int A[], int n, int search)
{
        for(int i=0; i<n; i++)
                if(A[i]==search)
                        return i+1;

        return 0;
}

int main(){
        ifstream input;
        ofstream output;

        input.open("input.txt");
        output.open("output.txt");

        if(input.is_open())
        {
                while(!input.eof())
                {
                        int n;
                        input >> n;

                        int search;
                        input >> search;

                        int collezione[n];

                        for(int i=0; i<n; i++)
                                input >> collezione[i];

                        output << search_volume(collezione, n, search) << endl;

                }
        }
        input.close();
        output.close();

        return 0;
}

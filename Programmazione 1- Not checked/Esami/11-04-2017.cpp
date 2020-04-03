#include <iostream>
#include <string>

using namespace std;

const int RIG=2;
const int COL=2;
const int size=4;
const int DIM1=2;
const int DIM2=2;

bool ese1(float A[][COL], int RIG, float B[size])
{
        float sum1=0;
        float sum2=0;
        for(int j=0; j<COL; j++)
        {
                for(int i=0; i<RIG; i++)
                {
                        for(int k=0; k<size-1; k++)
                        {
                                for(int m=k+1; m<size; m++)
                                {
                                        sum1=A[i][j]+A[i+1][j];
                                        sum2=B[k]+B[m];
                                        if(sum1==sum2) return true;
                                }
                        }
                }
        }
        return false;
}

bool ese2(string M[][DIM2], int DIM1, string S)
{
        int count=0;
        int l=S.length();
        bool found=false;
        for(int j=0; j<DIM2; j++)
        {
                bool notTrovato=false;
                for(int i=0; i<DIM1 && !notTrovato; i++)
                {
                        int len=M[i][j].length();
                        //if(M[i][j].find(S)!= string::npos)  return true;
                        int k,m=0;
                        string g="";
                        while(m<l)
                        {
                                if(M[i][j][k]==S[m])
                                {
                                        g+=M[i][j][k];
                                        k++; m++;
                                }
                                else break;
                        }
                        if(g==S) return true;
                }
        }
        return false;
}

int main()
{
        float A[RIG][COL]= {{1.5,2.4,},
                            {2.3,1.7}};
        float B[size]={1.5,2.4,1.7,2.89};

        string M[DIM1][DIM2]={{"panini","mangiare"},
                              {"power","sveglia"}};
        string s="are";

        if(ese1(A,RIG,B)) cout << "\t\tTrovato!\n";
        else cout << "\t\tNon trovato :(\n";

        if(ese2(M,DIM1,s)) cout << "\t\tTrovato!\n";
        else cout << "\t\tNon trovato :(\n";

        return 0;
}

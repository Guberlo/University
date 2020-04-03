#include <iostream>
#include <cstdlib>
using namespace std;

void random(int *vett, int dim){
    for(int i=0;i<dim;i++){
            vett[i]=rand()%100;
    }
}

void swap(int &a,int &b){
    int temp=a;
    a=b,
    b=temp;
}

bool ordinato(int *vett, int dim){
    if(dim < 2)
       return true;
    if(vett[dim-1]>=vett[dim-2])
        return ordinato(vett, dim-1);
    return false;
    }


void bubble(int *vett, int dim){
    while(dim>0){
        dim=dim-1;
        for(int i=0;i<dim;i++){
            if(vett[i]>vett[i+1]){
                swap(vett[i], vett[i+1]);
            }
        }
    }
}

void print_array(int *vett, int dim){
    for(int i=0;i<dim;i++){
        cout <<vett[i]<<", ";
    }

}

int main()
{
    int n=5;
    int *a=new int[n];

    random(a,n);
    print_array(a,n);
    cout<<endl;
    bubble(a,n);
    print_array(a,n);
    cout<<endl;


    return 0;
}
